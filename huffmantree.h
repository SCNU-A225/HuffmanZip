#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <map>

using namespace std;

/*
HuffmanTreeNode Node
哈夫曼树节点
保存节点信息，用于创建哈夫曼树。
*/
typedef struct HuffmanTreeNode{
    int data;//节点所表示的字符
    int weight;//字符出现的次数
    HuffmanTreeNode *parent,*lchild,*rchild,*address;//address用于存储节点的指针

    //构造函数
    HuffmanTreeNode():address(this){}
    HuffmanTreeNode(int d,int w):data(d),weight(w),parent(nullptr),lchild(nullptr),rchild(nullptr),address(this){}

    //重载>运算符，用于使用优先队列时比较
    bool operator >(const HuffmanTreeNode other) const
    {
        return weight>other.weight;
    }
}Node;

/*
HuffmanTree
哈夫曼树
用于生成哈夫曼树并生成其哈夫曼编码表。
*/
class HuffmanTree
{
public:
    HuffmanTree(int weights[]);//构造函数，使用权值数组进行构造
    map<int,string> getCodeTable(){return codeTable;}//获取哈夫曼树对应的编码表
    Node *getRoot(){return root;}//获取哈夫曼树根节点的指针

private:
    map<int, string> codeTable;//哈夫曼编码表
    Node *root;//树的跟节点

    Node* mergeTree(Node *tree1, Node *tree2);//合并两个哈夫曼树
    void makeCodeTable(Node *root,string code);//生成哈夫曼编码表

};

#endif // HUFFMANTREE_H
