#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"



char scan[1024];
char input[16];
int counter = 0;


//BINARY CONVERTER

int print_bit(int decimal){

	
	int bit_holder[16];
	int finder = 1;

	for(int i=0; i<16; i++){


		bit_holder[i] = (decimal & finder) == finder ;
		finder = finder << 1 ;

	}

	for (int i=15; i>=0; i-- ){

		printf("%d", bit_holder[i]);
	}

	printf("\n");
	return 0;
}

int execute_dest(int n,char* dest,char* input, int sz){
	dest[0]='\0';
	dest[1]='\0';
	dest[2]='\0';
	dest[3]='\0';
	int y = 0;
	for(int i=0; i<sz;i++){
		if (input[i] == '='){
			y=1;
			break;
		}


	} 
	if (y == 1){
		//DEST
		for( ;; n++){

			dest[n] = input[n];


			if( input[n] == '=' || input[n] == '\0'){


				dest[n] = '\0' ;
				n++ ;

				break;
			}
		}
	}
	return n;
}


int execute_comp(int n, char* comp, char* input, int sz){

	//COMP
	for( int i = 0; i < sz ; i++,n++){


		if (input[n] == ';' || input[n] == '\0'){

			comp[i] = '\0' ;

			n++ ;

			break;

		}

		comp[i] = input[n];

	}
	return n;
}

int execute_jump(int n, char* jump, char* input, int sz){
	jump[0] = '\0';
	int y=0;
	for (int i=0; i<sz; i++){

		if (input[n-1] == ';'){
			y =1;
			break;

		}
	}
	if (y == 1){

		//JUMP
		for (int i= 0;; i++,n++){

			if(input[n] == '\0'){

				jump[i] = '\0' ;

				break;
			}

			jump[i] = input[n];

		}

	}

	return n;
}

int translate(char* comp_in, char* comp_with, char* comp_out){

	if ( !strcmp(comp_in, comp_with )){
		printf("%s", comp_out);

		return 1;
	}
	return 0;
}


void print_instruction(char* comp, char* dest, char* jump){
	//unused bit print
	printf("111");
	//COMP INSTRUCTIONS


	translate(comp,   "0", "0101010");
	translate(comp,   "1", "0111111");
	translate(comp,  "-1", "0111010");
	translate(comp,   "D", "0001100");
	translate(comp,   "A", "0110000");
	translate(comp,  "!D", "0001101");
	translate(comp,  "!A", "0110001");
	translate(comp,  "-D", "0001111");
	translate(comp,  "-A", "0110011");
	translate(comp, "D+1", "0011111");
	translate(comp, "A+1", "0110111");
	translate(comp, "D-1", "0001110");
	translate(comp, "A-1", "0110010");
	translate(comp, "D+A", "0000010");
	translate(comp, "D-A", "0010011");
	translate(comp, "A-D", "0000111");
	translate(comp, "D&A", "0000000");
	translate(comp, "D|A", "0010101");

	translate(comp,   "M", "1110000");
	translate(comp,  "!M", "1110001");
	translate(comp,  "-M", "1110011");
	translate(comp, "M+1", "1110111");
	translate(comp, "M-1", "1110010");
	translate(comp, "D+M", "1000010");
	translate(comp, "M-D", "1000111");
	translate(comp, "D-M", "1010011");
	translate(comp, "D&M", "1000000");
	translate(comp, "D|M", "1010101");

	//DEST INSTRUCTION

	translate(dest,   "\0", "000");
	translate(dest,    "M", "001");
	translate(dest,    "D", "010");
	translate(dest,   "MD", "011");
	translate(dest,    "A", "100");
	translate(dest,   "AM", "101");
	translate(dest,   "AD", "110");
	translate(dest,  "AMD", "111");
	//JUMP INSTRUCTION

	translate(jump,    "\0", "000");
	translate(jump,   "JGT", "001");
	translate(jump,   "JEQ", "010");
	translate(jump,   "JGE", "011");
	translate(jump,   "JLT", "100");
	translate(jump,   "JNE", "101");
	translate(jump,   "JLE", "110");
	translate(jump,   "JMP", "111");

	printf("\n");	

}

void get_bits(int decimal, int* bit_holder){

	int finder = 1;

	for(int i=15; i>=0; i--){


		bit_holder[i] = (decimal & finder) == finder ;
		finder = finder << 1 ;

	}


}

int is_input_variable(char* input){



	if ( input[1] > '9' ||input[1] < '0' ){ 
		return 1;
	}
	else return 0;

}

void processAreg(char* input){

	input[0] = '0';	
	//printf("Atoi input: %c \n", input[0]);

	int bit = atoi(input);

	//printf("printing bit: %d \n", bit);


	int bitholder[16];
	get_bits(bit, bitholder);

	for(int i=0;i<16;i++){

		printf("%d", bitholder[i]);
	}
	
	counter++;
	printf("\n");


}


void processDreg(char* input, int size){
	int n = 0;	
	char dest[4];
	char comp[4];
	char jump[4];

	n = execute_dest(n, dest, input, size);
	//	printf("%d\n", n);
	n = execute_comp(n, comp, input, size);
	//	printf("%d\n", n);

	n = execute_jump(n, jump, input, size);
	//	printf("%d\n", n);
	print_instruction(comp, dest, jump);

	counter++;
	//	printf("dest:%s\ncomp:%s\njump:%s\n \n END\n\n", dest, comp, jump);

}


//}

int resize_input(char* scan, int size){

	int i,j;
	for(i=0,j=0;i<size; i++){
		if( scan[i] == ' '){
			continue;
		}
		if( scan[i] == '/' ){
			scan[i] = '\0';
			j++;
			break;
		}

		input[j] = scan[i];
		j++;
	}

	//	printf("input_size: %d\n", j);
	return j;
}

/*
* interpret_oneline
* scans the input line
* returns the size of input
* returns -1 when EOF is reached
*/
//Returns -1 When EOF
int interpret_oneline(){

	//Line Scanner
	int i;
	int scanf_ret;

	for(i=0;; i++){
		scanf_ret = scanf("%c", &scan[i]);
		if (scanf_ret == EOF){
			return -1;
		}
		if ( scan[i] == '\n'){ 	
			scan[i] = '\0';
			i++;
			break;
		}
	}

	int input_sz = resize_input(scan, i);

	//	printf("scan : %s \n" , scan);
	//	printf("input: %s \n", input);
	//scanner END
	return input_sz;
}


void add_predefined_symbols(struct map* symbol_table)
{
	map_store_at(symbol_table, "@R0", "@0");
	map_store_at(symbol_table, "@R1", "@1");
	map_store_at(symbol_table, "@R2", "@2");
	map_store_at(symbol_table, "@R3", "@3");
	map_store_at(symbol_table, "@R4", "@4");
	map_store_at(symbol_table, "@R5", "@5");
	map_store_at(symbol_table, "@R6", "@6");
	map_store_at(symbol_table, "@R7", "@7");
	map_store_at(symbol_table, "@R8", "@8");
	map_store_at(symbol_table, "@R9", "@9");
	map_store_at(symbol_table, "@R10", "@10");
	map_store_at(symbol_table, "@R11", "@11");
	map_store_at(symbol_table, "@R12", "@12");
	map_store_at(symbol_table, "@R13", "@13");
	map_store_at(symbol_table, "@R14", "@14");
	map_store_at(symbol_table, "@R15", "@15");
	map_store_at(symbol_table, "@SP", "@0");
	map_store_at(symbol_table, "@LCL", "@1");
	map_store_at(symbol_table, "@ARG", "@2");
	map_store_at(symbol_table, "@THIS", "@3");
	map_store_at(symbol_table, "@THAT", "@4");
}


int handle_variable(struct map* symbol_table, int directory_number){
	char dump[50];
	int find = map_get_at( symbol_table, input, dump);

	if( find == 0){
		sprintf( dump, "@%d", directory_number);
		map_store_at(symbol_table, input,  dump);
		directory_number++;
	}

	processAreg(dump);
	return directory_number;
}

int main(){
	int input_size;	
	struct map symbol_table;
	map_init(&symbol_table);
	int directory_number = 16;
	char label[50];
	
	//predefined symbol sorting
	add_predefined_symbols(&symbol_table);
	
	
	for(;;){

		//fflush(stdin);
		//fflush(string);
		input_size = interpret_oneline();

		if (input_size == -1)
		{
			return 0;
		}

		if(input_size == 1) 
		continue;
		//A Register input handle

		if ( input[0] == '@' || input[0] == '('){


			//label sorting
			if ( input[0] == '('){
				label[0] = '@';
				for( int i=1; i<50; i++){
					if(input[i] == ')'){ break;}
					label[i] = input[i];
				}
				char tmp[50];
				sprintf( tmp, "@%d", counter+1);
				map_store_at(&symbol_table, label, tmp);
				continue;

			}

			//Variable sorting
			int is_variable = is_input_variable(input);
			if (is_variable){
				directory_number =  handle_variable(
					&symbol_table,
					directory_number
				);
			}
			else	processAreg(input);
			
		}
		//D Register input handle
		else{
			processDreg(input, input_size);
		}
	}


}
