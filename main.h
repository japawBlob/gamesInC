#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <stdio.h>
#include <unistd.h> // for STDOUT_FILENO
#include <termios.h>
#include <stdlib.h>

//#include <fcntl.h>
struct map {
	struct field ** fields;
	int width, height;
};

struct field {
	char curr_texture;
	char init_texture;
};

void init_game();

void end_game();

char* move_to_pos(int x, int y);

void print_map();

struct map* init_map ();

void destroy_map (struct map* this_map);

void create_map (struct map* this_map);
