#include <bits/stdc++.h>
using namespace std;


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

int main() {
	
	UF uf(10);
	
	uf.unite(4,3);
	cout << uf.connected(4,3) << endl;
	uf.unite(3,8);
	cout << uf.connected(4,8) << endl;
	uf.unite(6,5);
	uf.unite(9,4);
	uf.unite(2,1);
	cout << uf.connected(8,9) << endl;	
	cout << uf.connected(5,4) << endl;	
	uf.unite(5,0);
	uf.unite(7,2);
	uf.unite(6,1);
	uf.unite(7,3);
	cout << uf.connected(5,4) << endl;	
	return 0;
}