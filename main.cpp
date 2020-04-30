#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <string>
#include <istream>
#include "graf.h"

int main(int, char**) {

    //Testing reading graphs
    {
        std::ifstream ifile1("graf1.txt"); //adjacency matrix
        std::ifstream ifile2("graf2.txt"); //adjacency list
        std::stringstream s1, s2;
        Graf<int> G1, G2;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        if (ifile2){
            s2 << ifile2.rdbuf();
            s2 >> G2;
        }
        for(int i=0; i<G1.M.N; i++)
            for(int j=0; j<G1.M.N; j++)
                if(G1.M(i,j)!=G2.M(i,j)) {cout << "Error in reading graph."; return 0;} //if the read graphs are not the same, there is an error
    }
    
    //Test addig and removing verteces and edges
    {
        std::ifstream ifile1("graf1.txt"); //adjacency matrix
        std::stringstream s1;
        Graf<int> G1;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        std::cout << G1;
        add_edge(G1, 0, 3, false); //add an adge
        std::cout << G1;
        remove_edge(G1, 0, 3, false); //remove the edge
        G1 = add_vertex(G1); //add a vertex
        std::cout << G1;
        G1 = remove_vertex(G1, 0); //remove the first vertex
        std::cout << G1;
    }

}
