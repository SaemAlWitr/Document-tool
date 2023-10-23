// Do NOT add any other includes
#include "dict.h"


trie_node::trie_node(trie_node* p){
    par=p;
    word_count=0;
}

trie_node::~trie_node(){
    par=nullptr;
    word_count=0;

    return;
}

trie::trie(){
    size=0;
    root=new trie_node();
}

int get_idx(char x){
    int asc=int(x);
    if(asc>47 && asc<58) return (asc-22);
    if(asc>64 && asc<91) return (asc-65);
    if(asc>96 && asc<123) return (asc-97);
    if(x=='/') return 36;
    if(asc==163) return 37;
    if(asc==35) return 38;
    if(asc==36) return 39;
    if(asc==37) return 40;
    if(asc==38) return 41;
    if(asc==42) return 42;
    if(asc==43) return 43;
    if(asc==60) return 44;
    if(asc==62) return 45;
    if(asc==61) return 46;
    if(asc==94) return 47;
    if(asc==96) return 48;
    if(asc==128) return 49;
    if(asc==165) return 50;
    if(asc==181) return 51;
    //add other possible symbols
    return -1;
}

pair_util trie::insert(string& word,int st,int end){
    trie_node* n=root;
    bool is_new=false;
    for (int i = st; i < end; ++i)
    {
        int asc=get_idx(word[i]);
        if(asc<0) continue;
        if(n->child[asc]) n=n->child[asc];
        else{
            n->child[asc]=new trie_node(n);
            size++;
            n=n->child[asc];
        }
    }
    n->word_count++;
    if(n->word_count==1) is_new=true;
    else{
        pair_util res={is_new,nullptr,""};
        return res;
    }
    string w=word.substr(st,(end-st));
    //convert to lower case
    for(int x=0;x<w.size();x++){
        int asc=int(w[x]);
        if(asc>64 && asc<91) w[x]=char(asc+32);
    }
    pair_util res={is_new,n,w};
    return res;
}

int trie::search(string& word){
    trie_node* n=root;
    for(auto i:word){
        int asc=get_idx(i);
        if(asc<0) return 0;
        if(!n->child[asc]) return 0;
        n=n->child[asc];
    }
    return n->word_count;
}

void rec_del(trie_node* n){
    for (auto i:n->child)
    {
        if(i) rec_del(i);
    }
    delete n;
}

trie::~trie(){
    size=0;
    rec_del(root);
}

Dict::Dict(){
}

Dict::~Dict(){
    return;    
}

bool Dict::is_separator(char x){
    for(auto i:separators){
        if(i==x) return true;
    }
    return false;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    
    for (int i = 0; i < sentence.size(); ++i)
    {
        if(is_separator(sentence[i])) continue;
        int start=i;
        while(i<sentence.size() && !(is_separator(sentence[i]))){
            i++;
        }
        pair_util pair= t.insert(sentence,start,(i));
        if(pair.is_new) distinct_words.push_back(pair);
    }
    return;
}

int Dict::get_word_count(string word){
    return t.search(word);
}

void Dict::dump_dictionary(string filename){
    ofstream fout(filename);
    for(auto pair:distinct_words){
        fout<<pair.word<<", "<<pair.node->word_count<<endl;
    }
    fout.close();
    return;
}

// int main(int argc, char const *argv[])
// {
//     Dict d;
//     // ifstream fin(argv[0]);

//     d.insert_sentence(1,2,3,4,"£ s d 3 pairs of trousers 1 16 0 1 jacket suit (vest & jacket) 2 0 0 3 white shirts 0 6 0 2 woollen shirts 0 16 0 2 woollen undervests or merino 0 11 0 4 cotton undervests 0 8 0 2 woollen drawers 0 13 0 6 pairs of woollen socks 0 12 0 £ 7 2 0 12 pairs of merino or cotton socks 0 9 0 12 cotton handkerchiefs 0 2 0 2 felt hats 0 7 0 6 neckties 0 3 0 1 slippers 0 2 0 4 pairs of boots and shoes 1 12 0 1 pair of gloves 0 3 0 £ 10 0 0 £ s d brought forward 10 0 0 3 tooth brushes 0 1 6 2 umbrellas 0 11 0 1 razor 0 3 0 1 evening suit on hire for one evening 0 5 0");
//     cout<<d.get_word_count("jacket");
//     d.dump_dictionary("dict.txt");
//     return 0;
// }