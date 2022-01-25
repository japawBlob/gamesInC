#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <stdio.h>
#include <unistd.h> // for STDOUT_FILENO
#include <termios.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>

#include <time.h>

#define EMPTY_FIELD (int) 0;
#define SNAKE_FIELD (int) 1;
#define APPLE_FIELD (int) 2;
//#include <fcntl.h>
struct snake {
	struct snake_part* snake_head;
	struct snake_part* snake_tail;
	int length;
	char head_texture;
	char body_texture;
};
struct snake_part {
	struct snake_part * next_part;
	struct snake_part * prev_part;
	struct field * occupied_field;
	int part_pos_x;
	int part_pos_y;
	int position_in_body;
};

struct moving_object {
	int pos_x;
	int pos_y;
	char texture;
};

struct map {
	struct field *** fields;
	int width, height;
};

struct field {
	char curr_texture;
	char init_texture;
	int id;
	int type;
};

enum directions {
    up = 1, left, down, right
};

extern pthread_mutex_t mut_game_terminated;

struct moving_object* init_moving_object (int x, int y, char texture, int user);

void init_game ();

void end_game ();

char* move_to_pos ();

void print_map ();

struct map* init_map ();

void free_memory ();

void* handle_user_input ();

void init_jeffrey (int x, int y);

int move_jeffrey();

void free_jeffrey();

void update_direction();

int get_direction();

void add_snake_part ();

struct map* get_map();

void game_over();
