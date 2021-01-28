#include "main.h"


int main(int argc, char const *argv[])
{
	struct winsize size;
	printf("\e[?25l");
	call_termios(0);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int width, height;
	width = size.ws_col+1;
	height = size.ws_row;
	struct map* this_map = init_map(width, height);
	//destroy_map(this_map);
	/*for (i = 0; i < size.ws_row-1; ++i){
		for (int j = 0; j < size.ws_col-1; ++j){
			putchar( '.' );
		}
		putchar('\n');
	}
	for (int j = 0; j < size.ws_col-1; ++j){
		putchar( '.' );
	}*/
	print_map(this_map);
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
	printf("\e[1;1H\e[2J");
	return 0;
}