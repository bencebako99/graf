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
        std::ifstream ifile1("graf1.txt");
        std::stringstream s1;
        Graf<int> G1;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        std::cout << G1;
        add_edge(G1, 0, 3, false, 1); //add an adge
        std::cout << G1;
        remove_edge(G1, 0, 3, false); //remove the edge
        G1 = add_vertex(G1); //add a vertex
        std::cout << G1;
        G1 = remove_vertex(G1, 0); //remove the first vertex
        std::cout << G1;
    }

    //Testing shortest path on unweighted graph
    {
        std::ifstream ifile1("graf3.txt"); 
        std::stringstream s1;
        Graf<int> G3;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G3;
        }
        std::cout << G3;
        ShortestPath(G3, 0, 6);
    }

    //Testing if graph is full
    {
        std::ifstream ifile1("graf3.txt"); 
        std::ifstream ifile2("graf4.txt");
        std::stringstream s1, s2;
        Graf<int> G3, G4;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G3;
        }
        string s;
        if (ifile2){
            s2 << ifile2.rdbuf();
            s2 >> G4;
        }
        if(isfull(G3) || !isfull(G4)) {cout << "Error in reading graph."; return 0;}
    }

}
