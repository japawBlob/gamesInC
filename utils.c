#include "main.h"

void call_termios(int reset){
	static struct termios tio, tioOld;
	tcgetattr(STDIN_FILENO, &tio);
	if (reset) {
		tcsetattr(STDIN_FILENO, TCSANOW, &tioOld);
	} else {
		tioOld = tio; //backup
		cfmakeraw(&tio);
		tio.c_oflag |= OPOST; // enable output postprocessing
		tcsetattr(STDIN_FILENO, TCSANOW, &tio);
	}
}

char* moveToPos(int x, int y){
	static int old_x = 2, old_y = 2;
	static char ret [100];
	sprintf(ret, "\033[%i;%iH", old_x, old_y);
	printf("%s.", ret);
	sprintf(ret, "\033[%i;%iH", x, y);
	printf("%so", ret);
	fflush(stdout);
	old_x = x;
	old_y = y;
	return ret;
}