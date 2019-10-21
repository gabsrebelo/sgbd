#include <iostream>
#include <string>

#ifndef REGISTRO_CLASS
#define REGISTRO_CLASS

class Registro
{
public:
    bool vazio;
    int id;
    char titulo[300];
    int ano;
    char autores[150];
    int citacoes;
    char atualizacao[19]; // "XX-XX-XXXX XX:XX:XX"
    char snippet[1024];
};

#endif