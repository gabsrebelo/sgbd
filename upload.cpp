#include <iostream>
#include <stdio.h>
#include "data_types/registro.h"
#include "data_types/bloco.h"
#include "helpers/hash.h"
#include "helpers/parser.h"

int main(int argc, char *argv[]){
    init_hash_file();

    parse_file(argv[1]);
    
    return 0;
}