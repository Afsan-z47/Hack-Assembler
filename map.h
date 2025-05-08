struct map {
	char store[2][1024][50];
	int directory_number;
};


void map_store_at(struct map* map, char* key, char* value);
int map_get_at(struct map* map, char* key, char* ret);
void map_init(struct map* m);

