#include<bits/stdc++.h>
using namespace std;

class Digraph{
private:
    int V;
    vector<int>* adj;
public:
    Digraph(int V, vector<int> adjacency[]){
        this->V = V;
        this->adj = new vector<int>[V];
        for(int i = 0;i<V;i++){
            for(int j = 0;j<adjacency[i].size();j++){
                this->adj[i].push_back(adjacency[i][j]);
            }
        }
    }
    
    Digraph reverse(){
        vector<int> rev_adj[this->V];
        
        for(int i = 0;i<V;i++){
            for(int j = 0;j<adj[i].size();j++){
                rev_adj[adj[i][j]].push_back(i);
            }
        }
        return Digraph(this->V, rev_adj);
    }
    
    void print(){
        for(int i = 0;i<V;i++){
            cout << i << ":" << " ";
            for(int j = 0;j<adj[i].size();j++){
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    void utility(int v, vector<bool>& visited, stack<int>& rev_post_order){
        visited[v] = true;
        for(int i = 0;i<this->adj[v].size();i++){
            if(!visited[adj[v][i]]){
                utility(adj[v][i], visited, rev_post_order);
            }
        }
        rev_post_order.push(v);
        
    }
    stack<int> reverse_post_order(){
        
        vector<bool> visited(V, false);
        stack<int> ans;
        
        for(int i = 0;i<this->V;i++){
            if(!visited[i]){
                this->utility(i, visited, ans);
            }
        }
        return ans;
    }
    
    void dfs(int v, vector<bool>& visited){
        visited[v] = true;
        for(int i = 0;i<this->adj[v].size();i++){
            if(!visited[adj[v][i]]){
                dfs(adj[v][i], visited);
            }
        }
    }
    
};
class Solution
{
	public:
	//Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<int> adj[])
    {
        Digraph graph(V, adj);
        stack<int> rev_po = graph.reverse().reverse_post_order();
        
        vector<bool> visited(V, false);
        
        int count = 0;
        while(!rev_po.empty()){
            int v = rev_po.top();
            rev_po.pop();
            if(!visited[v]){
                graph.dfs(v, visited);
                count++;
            }
        }
        
        return count;
        
    }
};

int main()
{
    
    int t;
    cin >> t;
    while(t--)
    {
    	int V, E;
    	cin >> V >> E;

    	vector<int> adj[V];

    	for(int i = 0; i < E; i++)
    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    	}

    	Solution obj;
    	cout << obj.kosaraju(V, adj) << "\n";
    }

    return 0;
}