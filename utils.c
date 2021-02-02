#include "main.h"

static void get_window_size (int* width, int* height);
static void call_termios(int reset);
static void create_map (struct map* this_map);
static void destroy_map (struct map* this_map);
static void destroy_objects(struct moving_object** objects);

static struct moving_object** objects;
static int number_of_objects = 0;

static struct moving_object* user_object;

static struct map* this_map;
/*
 *   1
 * 2   3
 *   4
*/
static int direction = 4;
int get_direction(){
	return direction;
}
struct map* get_map(){
	return this_map;
}

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
struct moving_object* init_moving_object(int x, int y, char texture, int user)
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

	

	if (user){
		user_object = objects[number_of_objects];
		move_to_pos();
	}	

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
void* handle_user_input()
{
	// while(1){
	// 	int blob = getchar();
	// 	if( blob == '0' ) break;	
	// 	if( blob == 'w' && user_object->pos_x > 1 ) (user_object->pos_x)--;
	// 	if( blob == 'a' && user_object->pos_y > 1 ) (user_object->pos_y)--;
	// 	if( blob == 's' && user_object->pos_x < this_map->height-2 ) (user_object->pos_x)++;
	// 	if( blob == 'd' && user_object->pos_y < this_map->width-2 ) (user_object->pos_y)++;

	// 	move_to_pos();
	// }

	while(1){
		int blob = getchar();
		if( blob == '0' ) break;	
		if( blob == 'w' ) direction = 1;
		if( blob == 'a' ) direction = 2;
		if( blob == 's' ) direction = 3;
		if( blob == 'd' ) direction = 4;
		if( blob == 'l' ) add_snake_part();
	}

	pthread_mutex_unlock(&mut_game_terminated);

	return NULL;
}

char* move_to_pos ()
{
	int new_x = user_object->pos_x;
	int new_y = user_object->pos_y;
	new_x++;
	new_y++;
	static int old_x = 2, old_y = 2;
	static char ret [100];
	sprintf(ret, "\033[%i;%iH", old_x, old_y);
	printf("%s%c", ret, this_map->fields[old_x-1][old_y-1]->init_texture);
	sprintf(ret, "\033[%i;%iH", new_x, new_y);
	printf("%s%c", ret, user_object->texture);
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
	this_map->width = width-1;
	this_map->height = height;
	this_map->fields = (struct field***) malloc (sizeof(struct field**)*height);
	for (int i = 0; i < this_map->height; ++i){
		this_map->fields[i] = (struct field **) malloc (sizeof(struct field*)*this_map->width);
		for (int j = 0; j < this_map->width; ++j){
			this_map->fields[i][j] = (struct field*) malloc (sizeof(struct field));
		}
	}
	create_map(this_map);
	return this_map;
}
static void create_map (struct map* this_map)
{
	int i, j;
	for (i = 0; i < this_map->height-1; ++i){
		for (j = 0; j < this_map->width; ++j){
			this_map->fields[i][j]->id = i*this_map->width+j;
			this_map->fields[i][j]->type = 0;
			if(i == 0){
				this_map->fields[i][j]->init_texture = '-';
				this_map->fields[i][j]->curr_texture = '-';
				if( (j == 0) || (j == this_map->width-1)){
					this_map->fields[i][j]->init_texture = '*';
					this_map->fields[i][j]->curr_texture = '*';
				}
			} else if( (j == 0) || (j == this_map->width-1)){
				this_map->fields[i][j]->init_texture = '|';
				this_map->fields[i][j]->curr_texture = '|';
			} else {
				this_map->fields[i][j]->init_texture = '.';
				this_map->fields[i][j]->curr_texture = '.';
			}
		}
		//this_map->fields[i][j]->texture = '\n';
	}
	for (j = 0; j < this_map->width; ++j){
		if ( (j == 0) || (j == this_map->width-1) ){
			this_map->fields[i][j]->init_texture = '*';
			this_map->fields[i][j]->curr_texture = '*';
		} else {
			this_map->fields[i][j]->init_texture = '-';
			this_map->fields[i][j]->curr_texture = '-';
		}
	}
}
void free_memory (){
	destroy_map(this_map);
	destroy_objects(objects);
	free_jeffrey();
}
static void destroy_map (struct map* this_map)
{
	for (int i = 0; i < this_map->height; ++i){
		for (int j = 0; j < this_map->width; ++j){
			free(this_map->fields[i][j]);
		}
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

void print_map()
{
	int i, j;
	for (i = 0; i < this_map->height-1; ++i){
		for (j = 0; j < this_map->width; ++j){
			putchar(this_map->fields[i][j]->curr_texture);
		}
		putchar('\n');
	}
	for (j = 0; j < this_map->width; ++j){
		putchar(this_map->fields[i][j]->curr_texture);
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