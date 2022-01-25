class Compare
{
public:
    bool operator() (vector<int> edge1, vector<int> edge2)
    {
        return (edge1[2] > edge2[2]);
    }
};

class Solution {
private:
    void visit(priority_queue<
            vector<int>,
            vector<vector<int>>,
            Compare
            >& pq,
            vector<vector<vector<int>>>& graph,
            vector<bool>& visited, int vertex){
        visited[vertex] = true;
        
        for(auto edge: graph[vertex]){
            
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            if(u != vertex and !visited[u]){
                pq.push(edge);
            }
            else if(v != vertex and !visited[v]){
                pq.push(edge);
            }
        }
        
    }
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        
        vector<bool> visited(n+1, false);
        
        vector<vector<vector<int>>> graph(n+1);
        
        for(auto edge: connections){
            
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            graph[u].push_back(edge);
            graph[v].push_back(edge);
        }
        
        
        priority_queue<
            vector<int>,
            vector<vector<int>>,
            Compare
            > pq;
        bool possible = true;
        
        int cost = 0;
        int mst_edge_count = 0;
        visit(pq, graph, visited, 1);
        while(!pq.empty() and (mst_edge_count<(n-1))){
            
            auto edge = pq.top();
            pq.pop();
            
            if(visited[edge[0]] and visited[edge[1]]){
                continue;
            }

            if(!visited[edge[0]]){
                visit(pq, graph, visited, edge[0]);
            }
            
            if(!visited[edge[1]]){
                visit(pq, graph, visited, edge[1]);
            }
            cost += edge[2];
            mst_edge_count++;
        }
        
        int retval = -1;
        if(mst_edge_count == n-1){
            retval = cost;
        }
        
        return retval;
        
    }
};