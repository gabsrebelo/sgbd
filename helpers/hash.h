#include <iostream>
#include "../data_types/registro.h"

#ifndef HASH_HELPER
#define HASH_HELPER

void init_hash_file();
void findrec(int id);
long get_bucket(int id);
long get_bucket_byte(int id);
void place_on_hash(Registro registro);
void read_hash_file();

#endif