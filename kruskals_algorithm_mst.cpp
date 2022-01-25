
class UF{
	
private:
	
	vector<int> sizes;
	vector<int> nodes;
	
	int root(int u){
		int i = u;
		while(nodes[i] != i){
			nodes[i] = nodes[nodes[i]];
			i = nodes[i]; 
		}
		return i;
	}
	
public:

	UF(int N){
		sizes = vector<int>(N, 1);
		nodes = vector<int>(N, 0);
		for(int i = 0;i<N;i++){
			nodes[i] = i;
		}
	}
	bool connected(int u, int v){
		int p = root(u);
		int q = root(v);
		
		return (p == q);
	}
	
	void unite(int u, int v){
		
		int p = root(u);
		int q = root(v);
		
		if(sizes[p] <= sizes[q]){
			nodes[p] = q;
			sizes[q] += sizes[p];
		}
		else{
			nodes[q] = p;
			sizes[p] += sizes[q];	
		}
	}
};
class Compare
{
public:
    bool operator() (vector<int> edge1, vector<int> edge2)
    {
        return (edge1[2] > edge2[2]);
    }
};
class Solution {

public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        
        priority_queue<
            vector<int>,
            vector<vector<int>>,
            Compare
            > pq(connections.begin(), connections.end());
        
        UF uf(n+1);
        
        int cost = 0;
        int mst_edge_count = 0;
        while(!pq.empty() and (mst_edge_count<(n-1))){
            
            auto edge = pq.top();
            pq.pop();
            
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            if(uf.connected(u,v)){
                continue;
            }
            uf.unite(u, v);
            cost += w;
            mst_edge_count++;
        }
        
        int retval = -1;
        if(mst_edge_count == n-1){
            retval = cost;
        }
        
        return retval;
    }
};