#include <stdio.h>
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
#include <time.h>


void tryCursorMovement()
{
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	int i;
	for (i = 0; i < size.ws_row-1; ++i){
		for (int j = 0; j < size.ws_col; ++j){
			putchar('0');
		}
		putchar('\n');
	}
	for (int j = 0; j < size.ws_col; ++j){
		putchar('0');
	}
	fflush(stdout);
	char string [100];
	sprintf(string, "\033[%i;%iH", 2, 2);
	printf("%s_ola_", string);
	fflush(stdout);
}

void printBlocks(){
	for (int i = 0; i < 50; ++i){
		for (int j = 0; j < 50; ++j){
			putchar('0');
		}
		putchar('\n');
	}
}
void tryModifyFunc(int *i){
	int temp = *i;
	temp++;
	*i += 1;
	(*i)++;
	//*i = 5;
}
void swap(int *x, int *y) {

   int temp;

   temp = *x; /* save the value of x */
   *x = *y;    /* put y into x */
   *y = temp; /* put temp into y */
  
   return;
}

int main(int argc, char const *argv[])
{
  	//tryCursorMovement();
	int i = 0;
	int j = 5;
	//int *p = &i;
	//tryModifyFunc(&i);
	printf("%i %i\n", i, j);
	swap(&i, &j);	
	printf("%i %i\n", i, j);
	tryModifyFunc(&i);
	printf("%i %i\n", i, j);
	
	//printBlocks();
	while(1){
		
		
		sleep(1);
	}
	return 0;
}
