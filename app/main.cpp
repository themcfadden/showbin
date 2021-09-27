
#include "showbin.hpp"
#include <iostream>

#include <unistd.h>
#include <stdio.h>

#include <time.h>

using namespace std;

int main(int argc, char** argv) {
	ShowBin b;

  cout << "One:" << endl;
	b.convertAndDisplay("1");
  cout << endl;

  cout << "Two:" << endl;
  b.convertAndDisplay("2");
  cout << endl;

  cout << "Three:" << endl;
  b.convertAndDisplay("3");
  cout << endl;

  cout << endl;
  b.convertAndDisplay("0xAA");
  cout << endl;

  cout << endl;
  b.convertAndDisplay("0xAAA");
  cout << endl;

  cout << "Done.\n";

}
