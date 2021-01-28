#include <stdio.h>
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO


void tryCursorMovement()
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int i;
	for (i = 0; i < size.ws_row-1; ++i){
		for (int j = 0; j < size.ws_col; ++j){
			putchar('0');
		}
		putchar('\n');
	}
	for (int j = 0; j < size.ws_col; ++j){
		putchar('0');
	}
	fflush(stdout);
	char string [100];
	sprintf(string, "\033[%i;%iH", 2, 2);
	printf("%s_ola_", string);
	fflush(stdout);
}

void printBlocks(){
	for (int i = 0; i < 50; ++i){
		for (int j = 0; j < 50; ++j){
			putchar('0');
		}
		putchar('\n');
	}
}

int main(int argc, char const *argv[])
{
  	//tryCursorMovement();
	printBlocks();
	while(1);
	return 0;
}
