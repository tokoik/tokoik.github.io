#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define PORTSPEED B9600
#define READCOUNT 33
#define TIMEOUT   0
#define THREAD

static struct termios ttySaved;		/* 最初の端末モード		*/
static float data[10];			/* 入力されたデータ	       	*/
static int errCode = 0;			/* エラーフラグ			*/

#ifdef THREAD
#include <pthread.h>
static pthread_t thr;			/* スレッド記述子		*/
#endif

static void readSuperGlobe(int fd) {
  for (;;) {
    char buf[READCOUNT + 1], *ptr = buf;
    int count = READCOUNT;

    do {
      int length = read(fd, ptr, count);
      if (length <= 0) {
	buf[0] = 'E';
	break;
      }
      ptr += length;
      count -= length;
    }
    while (count > 0);

    if (buf[0] == 'C') {		/* データブロック（連続モード）	*/
      buf[READCOUNT] = '\0';
      sscanf(buf + 1, "%3f%3f%3f%3f%3f%3f%3f%3f%3f%3f",
	     data, data + 1, data + 2, data + 3, data + 4, data + 5,
	     data + 6, data + 7, data + 8, data + 9);
    }
    else {
      break;
    }
  }
}

int startSuperGlobe(char *port) {
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

  write(fd, "AC", 2);

#ifdef THREAD
  pthread_create(&thr, NULL, (void *(*)())readSuperGlobe, (void *)fd);
#endif

  return fd;
}

void stopSuperGlobe(int fd) {
  write(fd, "S", 1);
  tcsetattr(fd, TCSAFLUSH, &ttySaved);
  close(fd);
#ifdef THREAD
  pthread_cancel(thr);
  pthread_detach(thr);
#endif
}

float *getSuperGlobe(void) {
  if (errCode)
    return 0;
  else
    return data;
}

int main()
{
  int i, fd;

  fd = startSuperGlobe("/dev/ttyd2");

  for (i = 0; i < 100; i++) {

#ifdef THREAD
    float *p;

    sleep(1);
    if (p = getSuperGlobe()) {
      printf("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
	     p[0], p[1], p[2], p[3], p[4],
	     p[5], p[6], p[7], p[8], p[9]);
    }
#else
    char buf[READCOUNT + 1], *ptr = buf;
    int count = READCOUNT;

    do {
      int length = read(fd, ptr, count);
      if (length <= 0) {
	buf[0] = 'E';
	break;
      }
      ptr += length;
      count -= length;
    }
    while (count > 0);

    if (buf[0] == 'C') {		/* データブロック（連続モード）	*/
      buf[READCOUNT] = '\0';
      sscanf(buf + 1, "%3f%3f%3f%3f%3f%3f%3f%3f%3f%3f",
	     data, data + 1, data + 2, data + 3, data + 4, data + 5,
	     data + 6, data + 7, data + 8, data + 9);
      printf("%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
	     data[0], data[1], data[2], data[3], data[4],
	     data[5], data[6], data[7], data[8], data[9]);
    }
    else {
      break;
    }
#endif
  }

  stopSuperGlobe(fd);

  return 0;
}
