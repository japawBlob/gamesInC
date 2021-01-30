#include "main.h"


int main(int argc, char const *argv[])
{
	init_game();
	struct map* this_map = init_map();
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
	destroy_map(this_map);
	end_game();
	return 0;
}