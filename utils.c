#include "main.h"

void call_termios(int reset)
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
	printf("%s.", ret);
	sprintf(ret, "\033[%i;%iH", x, y);
	printf("%so", ret);
	fflush(stdout);
	old_x = x;
	old_y = y;
	return ret;
}
struct map* init_map (int width, int height)
{
	struct map* this_map;
	this_map = (struct map*) malloc (sizeof(struct map));
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
				this_map->fields[i][j].texture = '-';
				if( (j == 0) || (j == this_map->width-1)){
					this_map->fields[i][j].texture = '*';
				}
			} else if( (j == 0) || (j == this_map->width-1)){
				this_map->fields[i][j].texture = '|';
			} else {
				this_map->fields[i][j].texture = '.';
			}
		}
		//this_map->fields[i][j].texture = '\n';
	}
	for (j = 0; j < this_map->width; ++j){
		if ( (j == 0) || (j == this_map->width-1) ){
			this_map->fields[i][j].texture = '*';
		} else {
			this_map->fields[i][j].texture = '-';
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
			putchar(this_map->fields[i][j].texture);
		}
		printf("\n");
	}
	for (j = 0; j < this_map->width; ++j){
		putchar(this_map->fields[i][j].texture);
	}
	fflush(stdout);
}
void get_window_size (){

}