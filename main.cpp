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
        std::ifstream ifile2("graf2.txt"); //list of edges
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
                if(G1.M(i,j)!=G2.M(i,j)) {cout << "Error in reading graph.\n"; return 0;} //if the graphs read are not the same, there is an error
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
        std::cout << "Here's our graph: \n";
        std::cout << G1;
        G1.add_edge(0, 3, 1); //add an adge
        std::cout << "We add an edge between 0 and 3: \n" << G1;
        G1.remove_edge(0, 3); //remove the edge
        std::cout << "We remove the edge added: \n" << G1;
        G1 = add_vertex(G1); //add a vertex
        std::cout << "We add a vertex: \n" << G1;
        G1 = remove_vertex(G1, 0); //remove the first vertex
        std::cout << "Than we remove the first one:\n" << G1;
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
        cout << "To test the shortest path algorithm, we consider graf3.\n";
        G3.ShortestPath(0, 6);
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
        if(G3.isfull() || !G4.isfull()) {cout << "Error in graph full algorithm.\n";}
    }

    //Test if graph is fully connected and find connected components
    {
        std::ifstream ifile1("graf3.txt"); 
        std::ifstream ifile2("graf5.txt");
        std::stringstream s1, s2;
        Graf<int> G1, G2;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        string s;
        if (ifile2){
            s2 << ifile2.rdbuf();
            s2 >> G2;
        }
        if(!G1.isconnected() || G2.isconnected()) {cout << "Error in graph connected algorithm.\n";}
        else {std::cout << "Connected components of graf5: \n" ;G2.ConnectedComponents();}
    }

    //Test if graph is tree
    {
        std::ifstream ifile1("graf3.txt"); 
        std::ifstream ifile2("graf5.txt");
        std::ifstream ifile3("graftree.txt");
        std::stringstream s1, s2, s3;
        Graf<int> G1, G2, G3;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        if (ifile2){
            s2 << ifile2.rdbuf();
            s2 >> G2;
        }
        if (ifile3){
            s3 << ifile3.rdbuf();
            s3 >> G3;
        }
        if(G1.istree() || G2.istree() || !G3.istree()) { std::cout << "Problem in tree algorithm.\n";}
    }

    //Test disjoint union
    {
        std::ifstream ifile1("graf1.txt"); 
        std::ifstream ifile2("graf3.txt");
        std::stringstream s1, s2;
        Graf<int> G1, G2;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        string s;
        if (ifile2){
            s2 << ifile2.rdbuf();
            s2 >> G2;
        }
        //All 4 versions are done, one is presented here
        std::cout << "Disjoint union of graf1 and graf3:\n" << std::move(G1)+std::move(G2);
    }

    //Test Cartesian product
    {
        std::ifstream ifile1("graf4.txt"); 
        std::ifstream ifile2("graf6.txt");
        std::stringstream s1, s2;
        Graf<int> G1, G2;
        if (ifile1){
            s1 << ifile1.rdbuf();
            s1 >> G1;
        }
        string s;
        if (ifile2){
            s2 << ifile2.rdbuf();
            s2 >> G2;
        }
        //All 4 versions done, one presented
        cout << "Cartesian product of graf4 and graf6:\n" << G1*std::move(G2);
    }
}
