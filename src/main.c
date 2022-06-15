#include "main.h"

pthread_mutex_t mut_game_terminated;

int main(int argc, char const *argv[])
{
	init_game();
	init_map();
	print_map();

	init_jeffrey(5,5);
	pthread_t input_thread;
	pthread_create(&input_thread, NULL, handle_user_input, NULL);

	move_jeffrey();

	pthread_mutex_init(&mut_game_terminated, NULL);
	pthread_mutex_lock(&mut_game_terminated);
	struct timespec time;
	long period = 1 * 1000000000/2;
	clock_gettime(CLOCK_REALTIME,&time);
	long nanos = 1000000000 * time.tv_sec + time.tv_nsec + period;
	while(1){
		clock_gettime(CLOCK_REALTIME,&time);
		if (nanos < 1000000000 * time.tv_sec + time.tv_nsec){
            //update_direction();
			if(move_jeffrey() == -1){
				break;
			}
			nanos = 1000000000 * time.tv_sec + time.tv_nsec + period;
		}
		if(pthread_mutex_trylock(&mut_game_terminated) == 0){
			pthread_mutex_unlock(&mut_game_terminated);	
			break;
		}
	}

	pthread_join(input_thread, NULL);
	pthread_mutex_destroy(&mut_game_terminated);
	free_memory();
	end_game();

	return 0;
}
