#include <iostream>
#include "matrix.h"

template <typename T>
class Graf
{
public:
    Matrix<T> M;
};

template <typename T>
 ostream& operator<<(std::ostream& o, Graf<T> const& G){
        o << 1 << endl;
        o << G.M;
        return o;
    }

template <typename T>
istream& operator>>(std::istream& s, Graf<T>& G){
    const auto state = s.rdstate();
    const auto pos = s.tellg();
    string tmp;
    getline(s, tmp);
    stringstream ss(tmp);
    int mode;
    getline(ss, tmp);  mode = stoi(tmp);
    /*switch(mode){
        case 1:
            s >> G.M;
    }*/
    s >> G.M;
    return s;
}

