#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

template <class T>
class IndexedPriorityQueue{
	

public:
	class Entry{
	public:
		int key;
		T val;
		
		Entry(int key, T val){
			this->key = key;
			this->val = val;
		}
		T get(int key){
			return val;
		}
		void update(T val){
			this->val = val;
		}
	};
	IndexedPriorityQueue(){
		size = 0;
		this->nodes = vector<Entry>();
	}
	IndexedPriorityQueue(const vector<Entry>& nodes){
		size = 0;
		this->nodes = vector<Entry>();
		build(nodes);
	}
	
	void build(const vector<Entry>& nodes){
		int n = nodes.size();
		for(auto node: nodes){
			this->nodes.push_back(node);
			key_to_position[node.key] = size;
			size++;
		}
		for(int i = ((size/2)-1);i>=0;i--){
			sink(i);
		}
	}
	
	Entry top(){
		return nodes[0];	
	}
	
	void pop(){
		int k = nodes[0].key;
		key_to_position.erase(nodes[0].key);
        exchange(0, size-1);
		size--;
		int pos = sink(0);
		nodes.pop_back();
		
	}
	
	int push(const Entry& node){
		int key = node.key;
		nodes.push_back(node);
		int pos = swim(size);
		size++;
		key_to_position[key] = pos;
		return size-1;
	}
	
	void decrease(int id, int new_val){
		nodes[key_to_position[id]].update(new_val);
		swim(key_to_position[id]);
	}
    void print(){
        for(auto node: nodes){
            cout << node.key << " " << node.val << endl;
        }
        for(auto p: key_to_position){
            cout << p.first << "->" << p.second << endl;
        }
        cout << endl;
    }
    bool empty(){
        return (size == 0);
    }
    bool contains(int key){
        return (key_to_position.find(key) != key_to_position.end());
    }
private:
	int size;
	vector<Entry> nodes; // Entry key will be the key users provide. For example; vertex number in a graph.
	unordered_map<int, int> key_to_position; // mapping from key (provided by user) to position in the nodes vector.


	inline int parent(int pos){
		return (pos == 0) ? pos : (pos-1)/2;
	}
	inline int left(int pos){
        return (2*pos + 1);
	}
	inline int right(int pos){
        return (2*pos + 2);
	}
	
    void exchange(int a, int b){
        if(a == b) return;
        key_to_position[nodes[a].key] = b;
        key_to_position[nodes[b].key] = a;
        swap(nodes[a], nodes[b]);
    }
	int sink(int pos){
		bool stop = false;

		while(left(pos) < size and !stop){
			int l = left(pos);
			int r = right(pos);
			
            int min_index = l;
            if(l < size-1 and nodes[l].val > nodes[r].val) { 
                min_index = r;
            } 
            
            if(nodes[min_index].val < nodes[pos].val) {
                exchange(min_index, pos);
            }
            else {
                min_index = pos;
                stop = true; 
            }
            
            pos = min_index;
		}
		
		return pos;
	}
	int swim(int pos){
		while(parent(pos) != pos and nodes[parent(pos)].val > nodes[pos].val){
            exchange(pos, parent(pos));
			pos = parent(pos);
		}
		return pos;
	}
		
};

class Edge{
public:
    int u;
    int v;
    double weight;
    Edge(int u, int v, double weight){
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
    int from(){
        return this->u;
    }
    int to(){
        return this->v;
    }
    double get_weight(){
        return this->weight;
    }
};

class Digraph{
private:
    int V;
    vector<Edge>* adj;
public:
    Digraph(int V){
        this->V = V;
        this->adj = new vector<Edge>[V];
    }

    Digraph(int V, vector<Edge>& edges){
        this->V = V;
        this->adj = new vector<Edge>[V];
        for(auto edge: edges){
            int u = edge.from();
            int v = edge.to();
            this->adj[u].push_back(edge);
        }
    }

    void add_edge(Edge edge){
        int u = edge.from();
        this->adj[u].push_back(edge);
    }

    void print(){
        for(int i = 0;i<V;i++){
            cout << i << ":" << " ";
            for(int j = 0;j<adj[i].size();j++){
                cout << adj[i][j].to() << " ";
            }
            cout << endl;
        }
    }
    
    vector<double> shortest_path_lengths(int source){

        vector<double> distance(V, numeric_limits<double>::max());
        distance[source] = 0.0;

        IndexedPriorityQueue<double> pq;
        pq.push(IndexedPriorityQueue<double> :: Entry(source, 0.0));

        while(!pq.empty()){
            auto entry = pq.top();
            pq.pop();

            for(Edge outgoing_edge: adj[entry.key]){
                
                int u = outgoing_edge.from();
                int v = outgoing_edge.to();
                double w = outgoing_edge.get_weight();

                if((distance[u] + w) < distance[v]){
                	distance[v] = (distance[u] + w);
                	if(!pq.contains(v)){
	                    pq.push(IndexedPriorityQueue<double> :: Entry(v, distance[v]));
	                }
	                else{
                    	pq.decrease(v, distance[v]);
	                }
	                
                }
            }
        }

        return distance;
    }
    
};

/* 
    Implementation reference : Coursera - Algorithms by robert sedgewick and kevin wayne
*/
int main()
{
    int vertices = 8;
    Digraph graph(vertices);
    graph.add_edge(Edge(0, 1, 5));
    graph.add_edge(Edge(0, 4, 9));
    graph.add_edge(Edge(0, 7, 8));
    graph.add_edge(Edge(1, 2, 12));
    graph.add_edge(Edge(1, 3, 15));
    graph.add_edge(Edge(1, 7, 4));
    graph.add_edge(Edge(2, 3, 3));
    graph.add_edge(Edge(2, 6, 11));
    graph.add_edge(Edge(3, 6, 9));
    graph.add_edge(Edge(4, 5, 4));
    graph.add_edge(Edge(4, 6, 20));
    graph.add_edge(Edge(5, 2, 1));
    graph.add_edge(Edge(5, 6, 13));
    graph.add_edge(Edge(7, 5, 6));
    graph.add_edge(Edge(7, 2, 7));

    int source = 0;
    vector<double> shortest_path_lengths = graph.shortest_path_lengths(source);
    for(int v = 0;v<vertices;v++){
        cout << "Shortest path from 0 to " << v << " = " << shortest_path_lengths[v] << endl;
    }

    /*
    Following is the output:
    Shortest path from 0 to 0 = 0
    Shortest path from 0 to 1 = 5
    Shortest path from 0 to 2 = 14
    Shortest path from 0 to 3 = 17
    Shortest path from 0 to 4 = 9
    Shortest path from 0 to 5 = 13
    Shortest path from 0 to 6 = 25
    Shortest path from 0 to 7 = 8
    */

    return 0;
}