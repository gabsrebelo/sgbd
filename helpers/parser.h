#include <iostream>
#include <vector>
#include <string>

#ifndef PARSER
#define PARSER

// std::string remove_quotes();
void check_badformat_erros(std::vector< std::string > &tupla);
void create_registro(std::vector< std::string > tupla);
void teste(std::vector<std::string> &tupla);
void preprocess_linha(std::string &linha);
void process_content(std::fstream &cursor);
void read_file();

#endif