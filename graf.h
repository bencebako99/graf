#include <iostream>
#include <string>
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
    switch(mode){
        case 1:
            s >> G.M;
            break;
        case 2:
            getline(s, tmp);
            stringstream ss(tmp);
            getline(ss, tmp);  G.M.N= std::stoi(tmp);
            for(int i=0; i<G.M.N; i++)
                for(int j=0; j< G.M.N; j++){
                    G.M.data.push_back(0);
                }
            while(s.peek() != EOF){
                getline(s, tmp, '\n');
                stringstream ss1(tmp);
                int i, j;
                getline(ss1, tmp, ' ');  i= std::stoi(tmp);
                getline(ss1, tmp);  j= std::stoi(tmp);
                G.M(i,j) = 1;
            }
            break;
    }
    return s;
}

