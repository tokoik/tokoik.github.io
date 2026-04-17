#include <iostream.h>
#include <fstream.h>

void main(void)
{
  int count;
  ifstream ifile("count");
  ifile >> count;
  ifile.close();
  cout << ++count << endl;
  ofstream ofile("count");
  ofile << count << endl;
  ofile.close();
}

