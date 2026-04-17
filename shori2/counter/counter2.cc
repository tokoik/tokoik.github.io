#include <iostream.h>
#include <fstream.h>
#define COLUMN 6

void main(void)
{
  int count;
  ifstream ifile("count");
  ifile >> count;
  ifile.close();
  ++count;
  ofstream ofile("count");
  ofile << count << endl;
  ofile.close();

  int i, digit[COLUMN];
  for (i = 0; i < COLUMN; i++) {
    digit[i] = count % 10;
    count /= 10;
  }
  for (i = COLUMN; i > 0;) {
    cout << "<img src=\"" << digit[--i] << ".gif\" border=\"0\">";
  }
}

