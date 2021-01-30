#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <stdio.h>
#include <unistd.h> // for STDOUT_FILENO
#include <termios.h>
#include <stdlib.h>

//#include <fcntl.h>
struct moving_object {
	int pos_x;
	int pos_y;
	char texture;
};

struct map {
	struct field ** fields;
	int width, height;
};

struct field {
	char curr_texture;
	char init_texture;
};

struct moving_object* init_moving_object (int x, int y, char texture);

void init_game ();

void end_game ();

char* move_to_pos (struct moving_object* object, struct map* this_map, int new_x, int new_y);

void print_map ();

struct map* init_map ();

void free_memory ();

int handle_user_input ();
