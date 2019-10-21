#include "hash.h"
#include "../data_types/bloco.h"
#include <iostream>
#include <fstream>

/*

    BUCKET: 4 blocos
    N_BUCKETS: 196.613 buckets
    N_BLOCOS: 786.452 blocos
    N_MAX_REGISTERS: 1.572.904

    HASH_FILE_SIZE: 2.39 GB

*/

#define N_BUCKETS 196613
#define BLOCOS_POR_BUCKET 4
#define N_TOTAL_BLOCOS 786452 // 4 * N_BUCKETS

void init_hash_file(){
    std::fstream cursor_teste;

    // Abre o arquivo `hash.bin` para leitura apenas pra testar se ele existe.
    cursor_teste.open("files/hash.bin", std::ios::in);

    // Se o arquivo não existir, cria.
    if(!cursor_teste.is_open()){
        std::cout << "[INIT] Criando arquivo de hash" << std::endl;

        std::ofstream cursor_binario;
        cursor_binario.open("files/hash.bin", std::ios::binary);

        Bloco bloco_vazio;
        bloco_vazio.vazio = true;

        for(int i = 0; i < N_TOTAL_BLOCOS; i++){
            cursor_binario.write((char*) &bloco_vazio, sizeof(Bloco));
        }   
    }
}