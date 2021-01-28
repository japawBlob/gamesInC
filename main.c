#include "main.h"


int main(int argc, char const *argv[])
{
	struct winsize size;
	printf("\e[?25l");
	call_termios(0);	
	//while(1){
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	//printf("width: %i\theight: %i\n", size.ws_row, size.ws_col);
	//usleep(1000*100);
//}	
	int i;
	for (i = 0; i < size.ws_row-1; ++i){
		for (int j = 0; j < size.ws_col-1; ++j){
			//printf("%i", i%10);
			putchar( (i%10) + 48 );
		}
		//printf("\n\r");
		putchar('\n');
	}
	for (int j = 0; j < size.ws_col-1; ++j){
		//printf("%i", i%10);
		putchar( (i%10) + 48 );
	}
	fflush(stdout);
	
	while(1){
		//rewind(stdout);
		//printf("   blob   ");
		//printf("\033[<6>A    blob   ");
		//printf("");
		//fflush(stdout);
		printf("\033[8;5Hhello");

		int blob = getchar();
		if( blob == 48 ) break;	
	}
	
	
	call_termios(1);
	printf("\e[?25h");
	return 0;
}