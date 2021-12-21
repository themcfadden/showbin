
#include "showbin.hpp"
#include <iostream>

#include <unistd.h>
#include <stdio.h>

#include <time.h>

using namespace std;

void showhelp(char **argv)
{
  printf("Usage: %s [OPTIONS] NUMBER\r\n", argv[0]);
  printf("Options:\r\n");
  printf("  -h --help\t Print this message and exit.\r\n");
  printf("\r\n");
  printf("Specifying Numbers:\r\n");
  printf("  1234\t\tDecimal\r\n");
  printf("  0x1234\tHexidecimal\r\n");
  printf("  0o1234\tOctal\r\n");
}
// showbin -h
// showbin <number>
int main(int argc, char** argv) {
	ShowBin b;

  if (argc < 2)
  {
    showhelp(argv);
    return 1;
  }

  while(true)
  {
    int opt = getopt(argc, argv, "h");
    if (opt == -1)
      break;
    switch (opt)
    {
      case 'h':
        showhelp(argv);
        return 0;
      default:
        showhelp(argv);
        return 1;
    }
  }

  b.convertAndDisplay(argv[1]);

  return 0;
}
