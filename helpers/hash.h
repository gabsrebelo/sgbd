#include <iostream>
#include "../data_types/registro.h"

#ifndef HASH_HELPER
#define HASH_HELPER

void init_hash_file();
int get_bucket(int id);
void place_on_hash(Registro registro);

#endif