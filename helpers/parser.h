#include <iostream>
#include <vector>
#include <string>

#ifndef PARSER
#define PARSER

// std::string remove_quotes();
void check_badformat_erros(std::vector< std::string > &tupla);
void create_registro(std::vector< std::string > tupla);
bool atributo_null(std::string atributo);
void read_file2();
void read_file();

#endif