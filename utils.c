#include "main.h"

static void get_window_size (int* width, int* height);
static void call_termios(int reset);
static void create_map (struct map* this_map);
static void destroy_map (struct map* this_map);
static void destroy_objects(struct moving_object** objects);

static struct moving_object** objects;
static int number_of_objects = 0;

static struct map* this_map;

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
void select_new_map(struct map* new_map){
	free(this_map);
	this_map = new_map;
}
struct moving_object* init_moving_object(int x, int y, char texture)
{
	static int objects_size = 0;
	if (number_of_objects == objects_size){
		objects_size += 5;
		if (objects == NULL){
			objects = (struct moving_object**) malloc (sizeof(struct moving_object*)*objects_size);
		} else {
			void ** temp = (void**)objects;
			objects = (struct moving_object**) realloc (temp, sizeof(struct moving_object*)*objects_size);
		}
	}
	objects[number_of_objects] = (struct moving_object*) malloc (sizeof(struct moving_object));
	objects[number_of_objects]->pos_x = x;
	objects[number_of_objects]->pos_y = y;
	objects[number_of_objects]->texture = texture;

	move_to_pos(objects[number_of_objects], this_map, x, y);		

	return objects[number_of_objects++];
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
int handle_user_input(int* x, int* y)
{
	int blob = getchar();
	if( blob == '0' ) return -1;	
	if( blob == 'w' && *x > 1 ) (*x)--;
	if( blob == 'a' && *y > 1 ) (*y)--;
	if( blob == 's' && *x < this_map->height-2 ) (*x)++;
	if( blob == 'd' && *y < this_map->width-2 ) (*y)++;

	return 0;
}
char* move_to_pos (struct moving_object* object, struct map* this_map, int new_x, int new_y)
{
	object->pos_x = new_x;
	object->pos_y = new_y;
	new_x++;
	new_y++;
	static int old_x = 2, old_y = 2;
	static char ret [100];
	sprintf(ret, "\033[%i;%iH", old_x, old_y);
	printf("%s%c", ret, this_map->fields[old_x-1][old_y-1].init_texture);
	sprintf(ret, "\033[%i;%iH", new_x, new_y);
	printf("%s%c", ret, object->texture);
	fflush(stdout);
	old_x = new_x;
	old_y = new_y;
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
static void create_map (struct map* this_map)
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
void free_memory (){
	destroy_map(this_map);
	destroy_objects(objects);
}
static void destroy_map (struct map* this_map)
{
	for (int i = 0; i < this_map->height; ++i){
		free(this_map->fields[i]);
	}
	free(this_map->fields);
	free(this_map);
}
static void destroy_objects(struct moving_object** objects)
{
	for (int i = 0; i < number_of_objects; ++i){
		free(objects[i]);
	}
	free(objects);
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
	printf("width: %i height: %i\n", *width, *height);
}