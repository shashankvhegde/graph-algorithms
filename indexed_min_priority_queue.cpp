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
	
	T top(){
		return nodes[0].val;	
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

// Test: output before both "###...#" should be same.
// Implementation reference : Algorithms by robert sedgewick and kevin wayne
int main()
{
    IndexedPriorityQueue<int> pq;
    pq.push(IndexedPriorityQueue<int> :: Entry(1, 3));
    pq.push(IndexedPriorityQueue<int> :: Entry(2, 2));
    pq.push(IndexedPriorityQueue<int> :: Entry(3, 15));
    pq.push(IndexedPriorityQueue<int> :: Entry(4, 5));
    pq.push(IndexedPriorityQueue<int> :: Entry(5, 4));
    pq.push(IndexedPriorityQueue<int> :: Entry(6, 45));
 
    pq.print();
    pq.decrease(6, 1);
    pq.decrease(3, 2);
    pq.decrease(5, 2);
    pq.print();
    cout << endl << endl;
    

    while(!pq.empty()){
        cout << pq.top() << endl;
        pq.pop(); 
    }
    cout << "####################################################################" << endl;
    
    vector<IndexedPriorityQueue<int> :: Entry> nodes;
    nodes.push_back(IndexedPriorityQueue<int> :: Entry(1, 3));
    nodes.push_back(IndexedPriorityQueue<int> :: Entry(2, 2));
    nodes.push_back(IndexedPriorityQueue<int> :: Entry(3, 15));
    nodes.push_back(IndexedPriorityQueue<int> :: Entry(4, 5));
    nodes.push_back(IndexedPriorityQueue<int> :: Entry(5, 4));
    nodes.push_back(IndexedPriorityQueue<int> :: Entry(6, 45));
    
    IndexedPriorityQueue<int> minheap(nodes);
    minheap.print();
    minheap.decrease(6, 1);
    minheap.decrease(3, 2);
    minheap.decrease(5, 2);
    minheap.print();
    cout << endl << endl;
    
    while(!minheap.empty()){
        cout << minheap.top() << endl;
        minheap.pop(); 
    }
    cout << "####################################################################" << endl;
    
    return 0;
}