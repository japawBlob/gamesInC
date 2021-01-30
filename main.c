#include "main.h"


int main(int argc, char const *argv[])
{
	init_game();
	struct map* this_map = init_map();
	print_map(this_map);
	struct moving_object* jeffrey = init_moving_object(1,1,'o');
	while(1){
		int x = jeffrey->pos_x;
		int y = jeffrey->pos_y;
		if(handle_user_input(&x, &y) == -1) break;
		move_to_pos(jeffrey, this_map, x, y);
	}
	free_memory();
	end_game();
	return 0;
}