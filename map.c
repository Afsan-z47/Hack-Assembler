#include <stdio.h>
#include <string.h>

#include "map.h"


void map_init(struct map* m){
	m->directory_number = 0;
}

int is_equal( char* old, char* new){

	int search_result;
	//	printf(" old: %s\n", old);
	//	printf(" new: %s\n", new);
	if(!strcmp(  old,  new)){
		search_result = 1;
	}
	else search_result = 0;

	return search_result;
}

int map_get_at(struct map* map, char* key, char* ret){
	
	int location;
	int result = 0;

	//char*** store = map->store;
		

	for( location=0;location<1024;location++){
		result = is_equal(map->store[0][location], key);
		if (result == 1){
			break;
		}
	}
	
	if (result == 0) return 0;

	char* value;
	//	printf("rsult: %d\n", result );
//	printf("File has: %s\n", map->store[1][location]);

	value = map->store[1][location];
	for(int i=0;i<50;i++){
		ret[i] = value[i];
		if( ret[i] == '\0' ){
		break;}
	}

	return 1;


}

void map_store_at(struct map* map, char* key, char* value){


	//char*** store = map->store;
	int directory_number = map->directory_number;	

	//Type-0 info storing
	for(int i=0;i<50;i++){
		map->store[0][directory_number][i] = key[i];
		if( key[i] == '\0' ){
		break;}
	}
	//		printf("name: %s\n", store[0][directory_number]);

	//Type-1 info storing
	for(int i=0;i<50;i++){
		map->store[1][directory_number][i] = value[i];
		if( value[i] == '\0' ){
		break;}
	}
	//		printf("info: %s\n", store[1][directory_number]);

	map->directory_number++;



}
/*
int main(){


	struct map map;
	map_init(&map);

	map_store_at(&map,"Hello", "World");
	map_store_at(&map,"game", "minecraft");
	map_store_at(&map,"mobile", "anime");
	map_store_at(&map,"hidden", "facebook");
	map_store_at(&map,"pc", "code");
	map_store_at(&map,"H", "World");
	map_store_at(&map, "Hello", "World");

	char file_name[50];
	char file_info[50];
	char mystr[100];

	for(;;){
		scanf("%s" , file_name);
		map_get_at(&map,file_name, mystr);
	}
}

*/
