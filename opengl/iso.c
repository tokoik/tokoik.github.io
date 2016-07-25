#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define PORTSPEED B9600
#define READCOUNT 47
#define TIMEOUT   0
#define THREAD

static struct termios ttySaved;		/* 最初の端末モード		*/
static float data[4][6];		/* 入力されたデータ	       	*/
static int errCode = 0;			/* エラーフラグ			*/

#ifdef THREAD
#include <pthread.h>
static pthread_t thr;			/* スレッド記述子		*/
#endif

static void readIsoTrak(int fd) {
  for (;;) {
    char buf[READCOUNT + 1], *ptr = buf;
    int count = READCOUNT;

    do {
      int length = read(fd, ptr, count);
      if (length <= 0) {
	errCode = -1;
	buf[0] = 'X';
	break;
      }
      ptr += length;
      count -= length;
    }
    while (count > 0);

    if (buf[0] == '0') {		/* データブロック（エラーなし）	*/
      int receiver = buf[1] - '1';	/* レシーバ番号			*/
      float *p = data[receiver];
      buf[READCOUNT] = '\0';
      sscanf(buf + 3, "%7f%7f%7f%7f%7f%7f",
	     p, p + 1, p + 2, p + 3, p + 4, p + 5);
    }
    else {
      if (strncmp(buf + 3, "ERROR", 5) == 0) {
	sscanf(buf + 9, "%d", &errCode);
      }
      break;
    }
  }
}

int startIsoTrak(char *port) {
  struct termios ttyStatus;
  int fd;

  if ((fd = open(port, O_RDWR)) < 0) return fd;
  tcgetattr(fd, &ttyStatus);
  ttySaved = ttyStatus;
  cfsetispeed(&ttyStatus, PORTSPEED);
  cfsetospeed(&ttyStatus, PORTSPEED);
  ttyStatus.c_cflag |= CS8 | CREAD /* | CNEW_RTSCTS */;
  ttyStatus.c_cflag &= ~(CSTOPB | PARENB);
  ttyStatus.c_iflag &= ~(BRKINT | INPCK | ISTRIP | INLCR | IGNCR | ICRNL |
			 IUCLC | IXON | IXOFF | IMAXBEL);
  ttyStatus.c_oflag &= ~OPOST;
  ttyStatus.c_lflag &= ~(ISIG | ICANON | XCASE | ECHO);
  ttyStatus.c_cc[VMIN] = READCOUNT;
  ttyStatus.c_cc[VTIME] = TIMEOUT;
  tcsetattr(fd, TCSANOW, &ttyStatus);

  write(fd, "uFC", 3);

#ifdef THREAD
  pthread_create(&thr, NULL, (void *(*)())readIsoTrak, (void *)fd);
#endif

  return fd;
}

void stopIsoTrak(int fd) {
  write(fd, "c", 1);
  tcsetattr(fd, TCSAFLUSH, &ttySaved);
  close(fd);
#ifdef THREAD
  pthread_cancel(thr);
  pthread_detach(thr);
#endif
}

float *getIsoTrak(int receiver) {
  if (errCode)
    return 0;
  else
    return data[receiver];
}

int main()
{
  int i, fd;

  fd = startIsoTrak("/dev/ttyd1");

  for (i = 0; i < 100; i++) {

#ifdef THREAD
    float *p;

    sleep(1);
    if (p = getIsoTrak(0)) {
      printf("%f,%f,%f,%f,%f,%f\n",
	     p[0], p[1], p[2], p[3], p[4], p[5]);
    }
#else
    char buf[READCOUNT + 1], *ptr = buf;
    int count = READCOUNT;

    do {
      int length = read(fd, ptr, count);
      if (length <= 0) {
	errCode = -1;
	buf[0] = 'X';
	break;
      }
      ptr += length;
      count -= length;
    }
    while (count > 0);

    if (buf[0] == '0') {		/* データブロック（エラーなし）	*/
      int receiver = buf[1] - '1';	/* レシーバ番号			*/
      float *p = data[receiver];
      buf[READCOUNT] = '\0';
      sscanf(buf + 3, "%7f%7f%7f%7f%7f%7f",
	     p, p + 1, p + 2, p + 3, p + 4, p + 5);
      printf("%f,%f,%f,%f,%f,%f\n",
	     p[0], p[1], p[2], p[3], p[4], p[5]);
    }
    else {
      if (strncmp(buf + 3, "ERROR", 5) == 0) {
	sscanf(buf + 9, "%d", &errCode);
      }
      break;
    }
#endif
  }

  stopIsoTrak(fd);

  return 0;
}
