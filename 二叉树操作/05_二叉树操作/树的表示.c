#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 二叉链表表示法
typedef struct tag_BiTNode
{
	// 数据
	char data;
	// 左孩子指针
	struct tag_BiTNode* left;
	// 右孩子指针
	struct tag_BiTNode* right;
}BiTNode;

// 三叉链表表示法
typedef struct tag_TirTNode
{
	// 数据
	char data;
	// 左孩子指针
	struct tag_TirTNode* left;
	// 右孩子指针
	struct tag_TirTNode* right;
	// 指向父节点的指针
	struct tag_TirTNode* parent;
}TirTNode;

// 双亲表示法
typedef struct tag_BPTNode
{
	//节点数据
	char data;
	//指向双亲的指针(数组下标)
	int parentPosition;
	//左右孩子标志域
	char LRTag;
}BPTNode;

//定义树的数据结构
typedef struct tag_BPTree
{
	//因为节点之间是分散的, 需要把节点存储到数组中
	BPTNode nodes[100];
	//节点的数目
	int num_node;
	//根节点的位置(***注意此域存储的是父亲节点在数组中的下标***)
	int root;
}BPTree;


int main01()
{
	BiTNode nodeA, nodeB, nodeC, nodeD, nodeE, nodeF, nodeG;
	// 初始化
	memset(&nodeA, 0, sizeof(BiTNode));
	memset(&nodeB, 0, sizeof(BiTNode));
	memset(&nodeC, 0, sizeof(BiTNode));
	memset(&nodeD, 0, sizeof(BiTNode));
	memset(&nodeE, 0, sizeof(BiTNode));
	memset(&nodeF, 0, sizeof(BiTNode));
	memset(&nodeG, 0, sizeof(BiTNode));

	// 构建树
	nodeA.data = 'a';
	nodeA.left = &nodeB;
	nodeA.right = &nodeC;

	nodeB.data = 'b';
	nodeB.left = &nodeD;
	nodeB.right = &nodeE;


	nodeC.data = 'c';
	nodeC.left = &nodeF;
	nodeC.right = &nodeG;

	nodeD.data = 'd';
	nodeE.data = 'e';
	nodeF.data = 'f';
	nodeG.data = 'g';


	BPTree tree;
	// 初始化
	memset(&tree, 0, sizeof(BPTree));
	tree.root = 0;
	// a
	tree.nodes[0].data = 'a';	// 数据
	tree.num_node++;
	// b
	tree.nodes[1].data = 'b';
	tree.nodes[1].LRTag = 1;
	tree.nodes[1].parentPosition = 0;
	tree.num_node++;
	// c
	tree.nodes[2].data = 'c';
	tree.nodes[2].LRTag = 2;
	tree.nodes[2].parentPosition = 0;
	tree.num_node++;


	return 0;
}