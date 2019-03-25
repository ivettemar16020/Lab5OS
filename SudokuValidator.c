#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/io.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//num_threads

int sudoku[9][9] = {
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
};

typedef struct{
	int row;
	int col;
}parameters;

void *columnVal(void* sudos){
	parameters *sudo = (parameters*) sudos;
	int row = sudo->row;
	int col = sudo->col;
	int valid[9] = {0};
	int i; 
	for (i=0; i<9; i++){
		int num = sudoku[i][col];
		if(num < 1 || num > 9 || valid[num - 1] == 1){
			printf("no");		
		}
		else{
			valid[num - 1] = 1;
		}

	}
	
	printf ("valid");
}

void *rowVal(void* sudos){
	parameters *sudo = (parameters*) sudos;
	int row = sudo->row;
	int col = sudo->col;
	int valid[9] = {0};
	int i; 
	for (i=0; i<9; i++){
		int num = sudoku[row][i];
		if(num < 1 || num > 9 || valid[num - 1] == 1){
			printf("no");		
		}
		else{
			valid[num - 1] = 1;
		}

	}
	
	printf ("valid");
}

void *blockVal(void* sudos){
	parameters *sudo = (parameters*) sudos;
	int row = sudo->row;
	int col = sudo->col;
	int valid[9] = {0};
	int i, j; 
	for (i= row; i< row + 3; i++){
		for(j = col; j < col + 3; j++){
			int num = sudoku[i][j];
			if(num < 1 || num > 9 || valid[num - 1] == 1){
				printf("no");		
			}
			else{
				valid[num - 1] = 1;
			}
		}

	}
	
	printf ("valid");
}

int main(int argc, char const *argv[]){
	unsigned char *f;
	int size;
	struct stat s;
	const char * file_name = argv[1];
	int fd = open (argv[1], O_RDONLY);

	//size
	int status = fstat(fd, & s);
	size = s.st_size;

	f = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
	int i;
	for (i=0; i<size; i++){
		char c;
		c = f[i];
		putchar(c);	
	}
	return 0;	
}
