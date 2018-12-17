#include "huffmantree.h"
#include <queue>
#include <QDebug>

/*
哈夫曼树构造函数
int weights[]: 权值数组
*/
HuffmanTree::HuffmanTree(int weights[])
{
    Node **treeNodes = new Node *[256];//用于保存对应为0-255的字符的节点信息
    priority_queue<Node,vector<Node>,greater<Node> > pq;//使用优先队列维护节点的权值排列
    for (int i=0,cnt=0;i<256;i++)//生成出现过的哈夫曼节点
    {
        if (weights[i]<=0) continue;//若字符没有出现，则跳过
        treeNodes[cnt] = new Node(i, weights[i]);
        pq.push(*treeNodes[cnt++]);//入队
    }
    //数据检查
    if(pq.size()<=0)
    {
        qDebug()<<"节点生成有误";
        return;
    }

    Node tnode1,tnode2;//用于临时存储最小两个节点的信息
    while(pq.size()>=2)//合并哈夫曼树，直到只剩一棵树
    {
        tnode1 = pq.top();pq.pop();
        tnode2 = pq.top();pq.pop();
        pq.push(*mergeTree(tnode1.address,tnode2.address));
    }
    root = pq.top().address;//储存根节点地址
    makeCodeTable(root,"");//生成编码表
}

/*
合并哈夫曼树
Node *tree1: 左树指针
Node *tree2: 右树指针
*/
Node* HuffmanTree::mergeTree(Node *tree1, Node *tree2)
{
    Node *parent = new Node(-1,tree1->weight+tree2->weight);
    parent->lchild = tree1;
    parent->rchild = tree2;
    tree1->parent = parent;
    tree2->parent = parent;
    return parent;
}

//生成哈夫曼编码表
void HuffmanTree::makeCodeTable(Node *root, string code)
{
    if(root==nullptr) return;
    if(root->lchild==nullptr && root->rchild==nullptr)
    {
        codeTable.insert(map<int, string>::value_type(root->data, code));
        return;
    }
    //生成时默认左边为0，右边为1
    makeCodeTable(root->lchild,code+'0');
    makeCodeTable(root->rchild,code+'1');
}
