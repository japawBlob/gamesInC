#include "main.h"


int main(int argc, char const *argv[])
{
	struct winsize size;
	printf("\e[?25l");
	call_termios(0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

	struct map* this_map = init_map(size.ws_col, size.ws_row);
	destroy_map(this_map);
	int i;
	for (i = 0; i < size.ws_row-1; ++i){
		for (int j = 0; j < size.ws_col-1; ++j){
			putchar( '.' );
		}
		putchar('\n');
	}
	for (int j = 0; j < size.ws_col-1; ++j){
		putchar( '.' );
	}
	fflush(stdout);
	int x = 2, y = 2;
	move_to_pos(x, y);
	while(1){
		int blob = getchar();
		if( blob == 48 ) break;	
		if( blob == 'w') x--;
		if( blob == 'a') y--;
		if( blob == 's') x++;
		if( blob == 'd') y++;
		move_to_pos(x,y);
	}
	call_termios(1);
	printf("\e[?25h");
	return 0;
}