#include "main.h"

static struct snake* jeffrey;

static void update_jeffrey_position ();

static void show_jeffrey ();

static void move_snake_body ();

static void print_jeffrey ();

static FILE* f;

void init_jeffrey(x, y)
{
	f = fopen("jeffrey.out", "w+");
	jeffrey = (struct snake*) malloc (sizeof(struct snake));
	jeffrey->head_texture = '*';
	jeffrey->body_texture = 'o';
	jeffrey->length = 3;
	jeffrey->snake_head = (struct snake_part*) malloc (sizeof(struct snake_part));
	jeffrey->snake_head->position_in_body = jeffrey->length;
	jeffrey->snake_head->part_pos_y = y;
	jeffrey->snake_head->part_pos_x = x;
	jeffrey->snake_head->next_part = NULL;
	jeffrey->snake_head->prev_part = NULL;
	jeffrey->snake_head->occupied_field = get_map()->fields[x][y];
	jeffrey->snake_head->occupied_field->type = jeffrey->length;
	jeffrey->snake_head->occupied_field->curr_texture = jeffrey->head_texture;
	struct snake_part* temp = jeffrey->snake_head;	
	for (int i = jeffrey->length-1; i > 0; i--){
		temp->next_part = (struct snake_part*) malloc (sizeof(struct snake_part));
		temp->next_part->position_in_body = i;
		temp->next_part->part_pos_x = x;
		temp->next_part->part_pos_y = --y;
		temp->next_part->occupied_field = get_map()->fields[x][y];
		temp->next_part->occupied_field->type = i;
		temp->next_part->occupied_field->curr_texture = jeffrey->body_texture;
		temp->next_part->prev_part = temp;
		temp->next_part->next_part = NULL;
		temp = temp->next_part;
	}
	jeffrey->snake_tail = temp;
	print_jeffrey();
	show_jeffrey();

}

static void show_jeffrey ()
{
	char ret [100];
	sprintf(ret, "\033[%i;%iH", jeffrey->snake_head->part_pos_x+1, jeffrey->snake_head->part_pos_y+1);
	printf("%s%c", ret, jeffrey->head_texture);
	fflush(stdout);
	struct snake_part* temp = jeffrey->snake_head->next_part;
	while(temp != NULL){
		sprintf(ret, "\033[%i;%iH", temp->part_pos_x+1, temp->part_pos_y+1);
		printf("%s%c", ret, jeffrey->body_texture);
		//printf("%s%i", ret, temp->occupied_field->type);
		fflush(stdout);
		temp = temp->next_part;
	}
}
static void print_jeffrey ()
{
	
	struct snake_part* temp = jeffrey->snake_head;
	fprintf(f, "FROM FRONT\n");
	while(temp!=NULL){
		fprintf(f ,"Position in body: %i\n", temp->position_in_body);
		fprintf(f ,"Field:\npart_pos_x: %i\npart_pos_y: %i\n", temp->part_pos_x, temp->part_pos_y);
		fprintf(f, "Field type: %i\n", temp->occupied_field->type);
		fprintf(f, "Id: %i\n", temp->occupied_field->id);	
		fprintf(f, "------------------------------------------------------\n");
		temp = temp->next_part;
	}
	fprintf(f, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	fprintf(f, "FROM BACK\n");
 	temp = jeffrey->snake_tail;
	while(temp!=NULL){
		fprintf(f ,"Position in body: %i\n", temp->position_in_body);
		fprintf(f ,"Field:\npart_pos_x: %i\npart_pos_y: %i\n", temp->part_pos_x, temp->part_pos_y);
		fprintf(f, "Field type: %i\n", temp->occupied_field->type);
		fprintf(f, "Id: %i\n", temp->occupied_field->id);	
		fprintf(f, "------------------------------------------------------\n");
		temp = temp->prev_part;
	}
	fprintf(f, "=========================================================\n");
}

int move_jeffrey()
{
	if (get_direction() == 1){
		move_snake_body();
		jeffrey->snake_head->part_pos_x--;
	} else if (get_direction() == 2){
		move_snake_body();
		jeffrey->snake_head->part_pos_y--;
	} else if (get_direction() == 3){
		move_snake_body();
		jeffrey->snake_head->part_pos_x++;
	} else if (get_direction() == 4){
		move_snake_body();
		jeffrey->snake_head->part_pos_y++;
	}
	if(!( 0 < jeffrey->snake_head->part_pos_x && jeffrey->snake_head->part_pos_x < get_map()->height-1) ||
	   !( 0 < jeffrey->snake_head->part_pos_y && jeffrey->snake_head->part_pos_y < get_map()->width-1)){
		return -1;
	}

	//update_jeffrey_position();
	show_jeffrey ();
	print_jeffrey ();
	return 0;
}
static void move_snake_body ()
{
	struct snake_part* temp = jeffrey->snake_tail;
	while(temp->prev_part != NULL){
		temp->occupied_field->type--;
		temp->part_pos_x = temp->prev_part->part_pos_x;
		temp->part_pos_y = temp->prev_part->part_pos_y;
		temp = temp->prev_part;
	}
	
	/*if (pos == 'x'){
		jeffrey->snake_head->part_pos_x += incremet;
		struct snake_part temp = jeffrey->snake_head->next_part;
		while(temp != NULL){
			temp->part_pos_x += incremet;
			temp = temp->next_part;
		}
	}
	if (pos == 'y'){
		jeffrey->snake_head->part_pos_y += incremet;
		struct snake_part temp = jeffrey->snake_head->next_part;
		while(temp != NULL){
			temp->part_pos_y += incremet;
			temp = temp->next_part;
		}
	}*/
}

static void update_jeffrey_position ()
{
	int new_x = jeffrey->snake_head->part_pos_x;
	int new_y = jeffrey->snake_head->part_pos_y;
	new_x++;
	new_y++;
	static int old_x = 2, old_y = 2;
	static char ret [100];
	sprintf(ret, "\033[%i;%iH", old_x, old_y);
	printf("%s%c", ret, get_map()->fields[old_x-1][old_y-1]->init_texture);
	sprintf(ret, "\033[%i;%iH", new_x, new_y);
	printf("%s%c", ret, jeffrey->head_texture);
	fflush(stdout);
	old_x = new_x;
	old_y = new_y;
}

void free_jeffrey()
{
	for (int i = 0; i < jeffrey->length; ++i){
		struct snake_part* temp = jeffrey->snake_head->next_part;
		free(jeffrey->snake_head);
		jeffrey->snake_head = temp;
	}
	free(jeffrey);
	fclose(f);
}