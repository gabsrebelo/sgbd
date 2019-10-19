#include<string>
#include<iostream>
using namespace std;
class Register{
    public:
        int id;
        char title[300];
        short int year;
        char authors[150];
        int citations;
        char updated[19];
        char snippet[1024];
};

//int main(){
//    Register reg;
//    reg.id = 1;
//    reg.title = "aaaaa";
//
//    cout << reg.title << endl;
//}