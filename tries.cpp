/*
Program : Auto complete feature using tries
Reference : geeksforgeeks.com
*/
#include<bits/stdc++.h>
using namespace std;
#define SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')  // macro to convert a char c to integer index
struct trieNode
{
    bool isEnd;
    struct trieNode* children[SIZE];  // The array of pointers sores the references to the children of next level
};
struct trieNode* getnode()                                //Create a new node and return its pointer
{
    trieNode* node=new trieNode;
    node->isEnd=false;
    for(int i=0;i<SIZE;++i)
        node->children[i]=NULL;
    return node;

};
void insrt(trieNode* root,const string key)
{
    trieNode* crawl=root;
    for(int i=0;i<key.length();++i)
    {
        int index=CHAR_TO_INDEX(key[i]);
        if(!crawl->children[index])
            crawl->children[index]=getnode();
        crawl=crawl->children[index];
    }
    crawl->isEnd=true;
}

bool isLastNode(trieNode* root)                       //to check if a node is the last node.
{
    for(int i=0;i<SIZE;++i)
        if(root->children[i])
            return false;
    return true;
}
void suggestions(trieNode* root,string q) //to find the words below the tree in prefix(after prefix).
{
    if(root->isEnd)
    {
        cout<<q<<endl;
    }
    if(isLastNode(root))
        return;
    for(int i=0;i<SIZE;++i)
    {
        if(root->children[i])
        {
             q.push_back(97+i);
             suggestions(root->children[i],q);
             q.pop_back();                //Important statement.
        }

    }
}
int printSuggestions(trieNode* root, string q) // crawls n levels and calls the suggestions function if the query is not he last node
{
    trieNode* crawl =root;
    int n=q.length();
    for(int l=0;l<n;++l)
    {
        int index=CHAR_TO_INDEX(q[l]);
        if(!crawl->children[index])
            return 0;
        crawl=crawl->children[index];
    }
    bool isWord= (crawl->isEnd==true);
    bool isLast=isLastNode(crawl);

    if(isLast&&isWord)
    {
        cout<<q<<endl;
        return -1;
    }
    if(!isLast)
    {
        string prefix=q;
        suggestions(crawl,prefix);
        return 1;
    }
}
int main()
{
    int n;
    cout<<"Enter the number of strings : ";
    cin>>n;
    trieNode* root=getnode();
    vector<string> keys(n);
    for(int i=0;i<n;++i)
        cin>>keys[i];
    for(int i=0;i<n;++i)
        insrt(root,keys[i]);
    string pre;
    cout<<"Enter the prefix to be looked for : ";
    cin>>pre;
    int comp = printSuggestions(root, pre);

    if (comp == -1)
        cout << "No other strings found with this prefix\n";
    else if (comp == 0)
        cout << "No string found with this prefix\n";
}
