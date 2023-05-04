#include<bits/stdc++.h>
using namespace std;
unordered_map<char,string> b_map;
struct Tree{
    int frequency;
    char character;
    Tree* left=NULL;
    Tree* right=NULL;
};

class TreeComparator{
    public:
    bool operator() (Tree* a, Tree* b){
        return a->frequency>b->frequency;
    }
};

string printVector(vector<int> A, char c)
{
    unordered_map<char,string> binary_map;
    string bin_string="";
    for(int i=0; i<A.size(); i++)
    {
        string l = to_string(A[i]);
        bin_string+=l;
        cout<<A[i];
    }
    return bin_string;
}

Tree* buildHuffmanTree(vector<pair<char, int> > freqtable)
{
    
    priority_queue<Tree*, vector<Tree*>,TreeComparator> huffqueue; 
    for(int i=0; i<freqtable.size(); i++)
    {
        Tree* node=new Tree();
        node->frequency=freqtable[i].second;
        node->character=freqtable[i].first;
        huffqueue.push(node);
    }

    while(huffqueue.size()>1)
    {
        Tree* a, *b;
        a=huffqueue.top();
        huffqueue.pop();
        b=huffqueue.top();
        huffqueue.pop();
        Tree* c=new Tree();
        c->frequency=a->frequency+b->frequency;
        c->left=a;
        c->right=b;
        huffqueue.push(c);
    }

    return huffqueue.top();
}

void traverseHuffmanTree(Tree* root, vector<int> code, int toAppend, unordered_map<char,string>& binary_map)
{
    
    if(toAppend!=-1)
    {
        code.push_back(toAppend);
    }
    if(root->right==NULL&&root->left==NULL){
        
        cout<<root->character<<" ";
        string bin_string=printVector(code,root->character);
        binary_map[root->character]=bin_string;
        cout<<endl;
    }
    if(root->right!=NULL)
    {
        traverseHuffmanTree(root->right,code, 1, b_map);
    }

    if(root->left!=NULL)
    {
        traverseHuffmanTree(root->left, code, 0, b_map);
    }


}


int main(){

     unordered_map<char,int> mp;
    ifstream input("original_huffman.txt");
    string s;
    char c;
    while(input.get(c)){
        string k = string(1,c);
        s+=k;
    }
    for(int i = 0; i< s.length();i++){
        if(mp.find(s[i])!=mp.end()){
            mp[s[i]]++;
        }else{
            mp[s[i]]=1;
        }
    }
    vector<pair<char,int>> vp;
    for(int i =0 ; i<s.length();i++){
        if(mp[s[i]]!=0){
            vp.push_back(make_pair(s[i],mp[s[i]]));
            mp[s[i]]=0;
        }
    }

    Tree* root=buildHuffmanTree(vp);
    vector<int> code;
    traverseHuffmanTree(root, code, -1,b_map);
    string comp_string="";
    for (char& c : s) {
        comp_string+=b_map[c];
    }
    cout<<comp_string<<endl;
     for (char& c : s) {
        if (b_map.count(c) > 0) {
            c = static_cast<char>(stoi(b_map[c], nullptr, 2));
        }
    }
    ofstream output_file("compressed.txt");
    output_file << s;
    output_file.close();

}