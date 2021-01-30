#include "main.h"

static struct map* this_map;
static void get_window_size (int* width, int* height);
static void call_termios(int reset);

void init_game()
{
	printf("\e[?25l");
	call_termios(0);
}

void end_game()
{
	call_termios(1);
	printf("\e[?25h");
	printf("\e[1;1H\e[2J");
}

static void call_termios(int reset)
{
	static struct termios tio, tioOld;
	tcgetattr(STDIN_FILENO, &tio);
	if (reset) {
		tcsetattr(STDIN_FILENO, TCSANOW, &tioOld);
	} else {
		tioOld = tio; //backup
		cfmakeraw(&tio);
		tio.c_oflag |= OPOST; // enable output postprocessing
		tcsetattr(STDIN_FILENO, TCSANOW, &tio);
	}
}

char* move_to_pos(int x, int y)
{
	static int old_x = 2, old_y = 2;
	static char ret [100];
	sprintf(ret, "\033[%i;%iH", old_x, old_y);
	printf("%s%c", ret, this_map->fields[old_x-1][old_y-1].init_texture);
	sprintf(ret, "\033[%i;%iH", x, y);
	printf("%so", ret);
	fflush(stdout);
	old_x = x;
	old_y = y;
	return ret;
}
struct map* init_map ()
{
	this_map = (struct map*) malloc (sizeof(struct map));
	int width, height;
	get_window_size(&width, &height);
	this_map->width = width;
	this_map->height = height;
	this_map->fields = (struct field**) malloc (sizeof(struct field*)*height);
	for (int i = 0; i < height; ++i){
		this_map->fields[i] = (struct field *) malloc (sizeof(struct field)*width);
	}
	create_map(this_map);
	return this_map;
}
void create_map (struct map* this_map)
{
	int i, j;
	for (i = 0; i < this_map->height-1; ++i){
		for (j = 0; j < this_map->width; ++j){
			if(i == 0){
				this_map->fields[i][j].init_texture = '-';
				this_map->fields[i][j].curr_texture = '-';
				if( (j == 0) || (j == this_map->width-1)){
					this_map->fields[i][j].init_texture = '*';
					this_map->fields[i][j].curr_texture = '*';
				}
			} else if( (j == 0) || (j == this_map->width-1)){
				this_map->fields[i][j].init_texture = '|';
				this_map->fields[i][j].curr_texture = '|';
			} else {
				this_map->fields[i][j].init_texture = '.';
				this_map->fields[i][j].curr_texture = '.';
			}
		}
		//this_map->fields[i][j].texture = '\n';
	}
	for (j = 0; j < this_map->width; ++j){
		if ( (j == 0) || (j == this_map->width-1) ){
			this_map->fields[i][j].init_texture = '*';
			this_map->fields[i][j].curr_texture = '*';
		} else {
			this_map->fields[i][j].init_texture = '-';
			this_map->fields[i][j].curr_texture = '-';
		}
	}
}
void destroy_map (struct map* this_map)
{
	for (int i = 0; i < this_map->height; ++i){
		free(this_map->fields[i]);
	}
	free(this_map->fields);
	free(this_map);
}
void print_map(struct map * this_map)
{
	int i, j;
	for (i = 0; i < this_map->height-1; ++i){
		for (j = 0; j < this_map->width; ++j){
			putchar(this_map->fields[i][j].curr_texture);
		}
		printf("\n");
	}
	for (j = 0; j < this_map->width; ++j){
		putchar(this_map->fields[i][j].curr_texture);
	}
	fflush(stdout);
}
static void get_window_size (int* width, int* height){
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	*width = size.ws_col;
	*height = size.ws_row;
}