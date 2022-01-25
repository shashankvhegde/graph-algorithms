#include<bits/stdc++.h>
using namespace std;

class Graph{
    
    private:
        int v;
        vector<int>* graph;
        bool* visited;
        void dfsUtil(int vertex);
        void bfsUtil(int vertex);
    public:
        Graph(int v);
        void addEdge(int u, int v);
        void dfs();
        void bfs();
        void print();
};

Graph::Graph(int v){
    this->v = v;
    graph = new vector<int>[v];
    visited = new bool[v];
}
void Graph::addEdge(int u, int v){
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void Graph::dfsUtil(int vertex){
    visited[vertex] = true;
    cout << vertex << endl;
    for(int i = 0;i<graph[vertex].size();i++){
        if(!visited[graph[vertex][i]]){
            dfsUtil(graph[vertex][i]);
        }
    }
}
void Graph::dfs(){
    
    for(int i = 0;i<v;i++){
        if(!visited[i]){
            dfsUtil(i);
        }
    }
}

void Graph::bfsUtil(int vertex){
    
    queue<int> q;
    q.push(vertex);
    
    visited[vertex] = true;
    
    while(!q.empty()){
        int x = q.front();
        cout << x << endl;
        q.pop();
        for(int i = 0;i<graph[x].size();i++){
            int w = graph[x][i];
            if(!visited[w]){
                visited[w] = true;
                q.push(w);
            }
        }
    }
    
}

void Graph::bfs(){
    
    for(int i = 0;i<v;i++){
        if(!visited[i]){
            bfsUtil(i);
        }
    }
    
}

void Graph::print(){
    for(int i = 0;i<v;i++){
        cout << i << ": ";
        for(int j = 0;j<graph[i].size();j++){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    
    int vertex = 8;
    
    Graph graph(vertex);
    
    graph.addEdge(0, 1);
    graph.addEdge(1, 6);
    graph.addEdge(6, 7);
    graph.addEdge(0, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.print();
    
    // graph.dfs();
    
    graph.bfs();
    
    return 0;
}