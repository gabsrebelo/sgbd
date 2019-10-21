#include <iostream>
#include <string>
#include <vector>
#include "registro.h"

#ifndef BLOCO_CLASS
#define BLOCO_CLASS

class Bloco {
public:
    Registro registros[2]; // size = 3024
    char lixo[1072]; // usado para completar os 4k do bloco (4096 - 3024 = 1072)
};

#endif
