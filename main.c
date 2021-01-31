#include "main.h"


int main(int argc, char const *argv[])
{
	init_game();
	struct map* this_map = init_map();
	print_map();
	struct moving_object* jeffrey = init_moving_object(1,1,'o',1);
	while(1){
		if(handle_user_input() == -1) break;
	}
	free_memory();
	end_game();
	return 0;
}