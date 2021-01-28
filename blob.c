#include <stdio.h>
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO


void tryCursorMovement(){
	struct winsize size;
	//while(1){
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	//printf("width: %i\theight: %i\n", size.ws_row, size.ws_col);
	//usleep(1000*100);
//}	
	int i;
	for (i = 0; i < size.ws_row-1; ++i){
		for (int j = 0; j < size.ws_col; ++j){
			//printf("%i", i%10);
			putchar('0');
		}
		//printf("\n");
		putchar('\n');
	}
	for (int j = 0; j < size.ws_col; ++j){
		//printf("%i", i%10);
		putchar('0');
	}
	fflush(stdout);
	char string [100];
	sprintf(string, "\033[%i;%iH", 2, 2);
	printf("%s_ola_", string);
	fflush(stdout);
}

void printBlocks(){
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
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
