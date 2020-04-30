#include <iostream>
#include <string>
#include "matrix.h"

template <typename T>
class Graf
{
public:
    Matrix<T> M;
};

//Operators
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

//Addig and removing verteces and edges
template <typename T>
void add_edge(Graf<T>& G, int i, int j, bool isdirected){
    G.M(i,j) = 1;
    if(isdirected == false)
        G.M(j, i) = 1;
}

template <typename T>
void remove_edge(Graf<T>& G, int i, int j, bool isdirected){
    G.M(i,j) = 0;
    if(isdirected == false)
        G.M(j, i) = 0;
}

template <typename T>
Graf<T> add_vertex(Graf<T> & G){
    Graf<T> G1;
    G1.M.N = G.M.N+1;
    for(int i=0; i<G1.M.N; i++)
        for(int j=0; j< G1.M.N; j++)
            G1.M.data.push_back(0);
    for(int i=0; i<G.M.N; i++)
        for(int j=0; j<G.M.N; j++)
            G1.M(i,j)=G.M(i,j);
    return G1;
}

template <typename T>
Graf<T> remove_vertex(Graf<T> const& G, int x){
    Graf<T> G1;
    G1.M.N = G.M.N-1;
    for(int i=0; i<G1.M.N; i++)
        for(int j=0; j< G1.M.N; j++)
            G1.M.data.push_back(0);
    for(int i=0; i<G1.M.N; i++)
        if(i<x)
            for(int j=0; j<G1.M.N; j++)
                if(j<x)
                    G1.M(i,j)=G.M(i,j);
                else
                    G1.M(i,j) = G.M(i, j+1);
        else
            for(int j=0; j<G1.M.N; j++)
                if(j<x)
                    G1.M(i,j)=G.M(i+1,j);
                else
                    G1.M(i,j) = G.M(i+1, j+1);            
    return G1;
}


