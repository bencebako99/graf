#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "matrix.h"

template <typename T>
class Graf
{
    private:
        void DFSUtil(int v, bool visited[]);
        
        bool BFS(int src, int dest, int pred[], int dist[]);
    public:
        Matrix<T> M;
        void ShortestPath(int src, int dest);
        bool isfull();
        void ConnectedComponents();
        bool istree();
        bool isconnected();
        bool iscyclic(int v, bool visited[], int parent);
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
                getline(ss1, tmp, ' ');  j= std::stoi(tmp);
                getline(ss1, tmp);
                G.M(i,j) = std::stoi(tmp);
                G.M(j,i) = std::stoi(tmp);
            }
            break;
    }
    return s;
}

//Addig and removing verteces and edges
template <typename T>
void add_edge(Graf<T>& G, int i, int j, bool isdirected, T weight){
    G.M(i,j) = 1;
    if(isdirected == false)
        G.M(j, i) = weight;
}

template <typename T>
void remove_edge(Graf<T>& G, int i, int j, bool isdirected){
    G.M(i,j) = 0;
    if(isdirected == false)
        G.M(j, i) = 0;
}

template <typename T>
Graf<T> add_vertex(Graf<T> const& G){
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


//Finding shortest path between two nodes
template <typename T>
bool Graf<T>::BFS(int src, int dest, int pred[], int dist[]){
    list<int> queue;
    bool visited[M.N];
    for (int i = 0; i < M.N; i++) { 
        visited[i] = false; 
        dist[i] = INT8_MAX; 
        pred[i] = -1; 
    }
    visited[src] = true; 
    dist[src] = 0; 
    queue.push_back(src); 
    while (!queue.empty()) { 
        int u = queue.front(); 
        queue.pop_front(); 
        for (int i = 0; i < M.N; i++) { 
            if (M(u,i)!=0 && visited[i] == false) { 
                visited[i] = true; 
                dist[i] = dist[u] + M(u,i); 
                pred[i] = u; 
                queue.push_back(i); 
  
                if (i == dest) 
                   return true; 
            } 
        } 
    } 
  
    return false; 
}

template <typename T>
void Graf<T>::ShortestPath(int src, int dest){
    int pred[M.N];
    T dist[M.N]; 
    if (BFS(src, dest, pred, dist) == false) 
    { 
        cout << "Given source and destination"
             << " are not connected"; 
        return; 
    } 
    vector<int> path; 
    int crawl = dest; 
    path.push_back(crawl); 
    while (pred[crawl] != -1) { 
        path.push_back(pred[crawl]); 
        crawl = pred[crawl]; 
    } 
    cout << "Shortest path length is : " << dist[dest]; 
        std::cout << "\nPath is:  "; 
    for (int i = path.size() - 1; i >= 0; i--) 
        std::cout << path[i] << " "; 
    std::cout << endl;
}


//Checking if graph is full
template <typename T>
bool Graf<T>::isfull(){
    for(int i=0; i< M.N; i++){
        int u=0;
        for(int j=0; j< M.N; j++)
            if(M(i,j)!=0)
                u++;
        if(u!=M.N-1) {return false;}
    }
    return true;
}

//Check if graph is fully connected
template <typename T>
bool Graf<T>::isconnected(){
    for(int i=0; i<M.N; i++){
        for(int j=i+1; j< M.N; j++){
            int pred[M.N];
            T dist[M.N]; 
            if (!BFS(i, j, pred, dist)) {return false;}  
        } 
    }
    return true;
}

//Find connected parts
template <typename T>
void Graf<T>::DFSUtil(int v, bool visited[]){ 
    visited[v] = true; 
    cout << v << " "; 
    for(int i = 0; i<M.N; i++) 
        if(!visited[i] && M(v, i)!=0) 
            DFSUtil(i, visited); 
} 

template <typename T>
void Graf<T>::ConnectedComponents(){
    bool visited[M.N];
    for(int i=0; i<M.N; i++){
        visited[i]=false;
    }
    for (int v=0; v<M.N; v++) 
    { 
        if (visited[v] == false) 
        { 
            DFSUtil(v, visited); 
            cout << "\n"; 
        } 
    }   
}

//Check if graph is tree
template <typename T>
bool Graf<T>::iscyclic(int v, bool visited[], int parent){
    visited[v]=true;
    for(int i=0; i<M.N; i++){
        if(M(v,i)!=0){
            if(visited[i] && i!=parent) { return true;}
            if(!visited[i])
                if(iscyclic(i, visited, v)) {return true;}
        }
    }
    return false;
}

template <typename T>
bool Graf<T>::istree(){
    if(!isconnected()) {return false;}
    bool visited[M.N];
    for(int i=0; i< M.N; i++)
        visited[i]=false;
    if(iscyclic(0, visited, -1)) { return false;}
    return true;
}
