#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <stdio.h>
#include <unistd.h> // for STDOUT_FILENO
#include <termios.h>

//#include <fcntl.h>

void call_termios(int reset);

char* moveToPos(int x, int y);