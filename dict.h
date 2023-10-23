// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class trie_node{
public:
    trie_node* par;
    int word_count;
    vector<trie_node*> child=vector<trie_node*>(52,nullptr);

    trie_node(trie_node* p=nullptr);
    ~trie_node();
};

struct pair_util{
    bool is_new;
    trie_node* node;
    string word;
};

class trie{
public:
    int size;
    trie_node* root;
    trie();
    ~trie();
    pair_util insert(string& word,int start,int end);
    int search(string& word);
};

class Dict {
private:
    string separators = " .,-:!\"\'()?—[]“”‘’˙;@";
    bool is_separator(char x);
    trie t;
    vector<pair_util> distinct_words;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};