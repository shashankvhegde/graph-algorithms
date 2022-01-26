#include <iostream>
using namespace std;


class Trie {

private:
    bool terminal;
    Trie* children[26]; 
    
    void insert(const string& word, int index){
        if(index == word.length()){
            terminal = true;
        }
        else{
            if(children[word[index]-'a'] == nullptr){
                children[word[index]-'a'] = new Trie();
            }
            children[word[index]-'a']->insert(word, index+1);
        }
    }
    
    bool search(const string& word, int index){
        bool found = false;
        if(index == word.length()){
            found = terminal;    
        }
        else if(children[word[index]-'a'] != nullptr){
            found = children[word[index]-'a']->search(word, index+1);
        }
        return found;
    }
    
    bool starts_with(const string& word, int index){
        bool found = false;
        if(index == word.length()){
            found = true;    
        }
        else if(children[word[index]-'a'] != nullptr){
            found = children[word[index]-'a']->starts_with(word, index+1);
        }
        return found;
    }
    bool remove(const string& word, int index){
	bool last_word = false;    
    	if(index == word.length()){
    		if(terminal){
    			terminal = false;
    		}
    	}
    	else{
    		if(children[word[index]-'a'] != nullptr){
    			bool last_word = children[word[index]-'a']->remove(word, index+1);
    			if(last_word){
    				delete children[word[index]-'a'];
    				children[word[index]-'a'] = nullptr;
    			}
    		}
    	}
	bool empty = true;
	for(int i = 0;i<26 and empty;i++){
		if(children[i] != nullptr){
			empty = false;
		}
	}
	last_word = empty;
    	return last_word;
    }
    void all_strings(string current, vector<string>& ans){
        
        if(ans.size() == 3){
            return;
        }
        if(terminal){
            ans.push_back(current);
        }
        
        for(int i = 0;i<26;i++){
            if(children[i] == nullptr) continue;
            current.push_back((char) ('a'+i));
            children[i]->all_strings(current, ans);
            current.pop_back();
        }
    }
    vector<string> strings_starting_with(string& prefix, int index){
        vector<string> ans;
        if(index == prefix.length()){
            this->all_strings(prefix, ans);
        }
        else if(children[prefix[index]-'a'] != nullptr){
            ans = children[prefix[index]-'a']->strings_starting_with(prefix, index+1);
        }
        return ans;
    }
    
public:
    Trie() {
        terminal = false;
        for(int i = 0;i<26;i++){
            children[i] = nullptr;
        }
    }
    

    void insert(string word) {
        insert(word, 0);
    }
    

    bool search(string word) {
        return search(word, 0);
    }
    
    bool startsWith(string prefix) {
        return starts_with(prefix, 0);
    }

    vector<string> strings_starting_with(string& prefix){
        return strings_starting_with(prefix, 0);
    }
	
    void remove(string word){
	remove(word, 0);
    }
};

/**
 * Refer leetcode problem: Implement Trie (https://leetcode.com/problems/implement-trie-prefix-tree/). 
 * Deletion is not present on leetcode but present here. It has been tested and verified against Coursera Algorithm's course booksite : https://algs4.cs.princeton.edu/52trie/TrieST.java.html
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
 
int main() {
	Trie* obj = new Trie();
	obj->insert("apple");
	cout << obj->search("apple") << endl;
	cout << obj->search("app") << endl;
	cout << obj->startsWith("app") << endl;
	obj->insert("app");
	cout << obj->search("app") << endl;
	obj->insert("applepen");
	obj->remove("apple");
	cout << obj->search("applepen") << endl;
	cout << obj->search("apple") << endl;
	cout << obj->search("app") << endl;
	cout << obj->search("appl") << endl;
	return 0;
}
