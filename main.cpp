#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <istream>
#include "graf.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::ifstream ifile("graf1.txt");
    std::stringstream s1;
    Graf<int> G;
    if (ifile){
        s1 << ifile.rdbuf();
    }
    string s, t, p;
    s1 >> G;

    std::cout << G;
}
