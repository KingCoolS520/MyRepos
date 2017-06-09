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

// 先序遍历
void preOrder(BiTNode* root)
{
	// 空树
	if (root == NULL)
	{
		return;
	}
	// 访问根节点
	printf("%c  ", root->data);
	// 访问左子树
	preOrder(root->left);
	// 访问右子树
	preOrder(root->right);
}

// 中序 遍历
void inOrder(BiTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	// 访问左子树
	inOrder(root->left);
	// 访问根节点
	printf("%c  ", root->data);
	// 访问右子树
	inOrder(root->right);
}

// 后序 遍历
void postOrder(BiTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	// 访问左子树
	postOrder(root->left);
	// 访问右子树
	postOrder(root->right);
	// 访问根节点
	printf("%c  ", root->data);
}

int main02()
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

	// 先序遍历
	preOrder(&nodeA);
	printf("\n");
	// 中序
	inOrder(&nodeA);
	printf("\n");
	// 后序
	postOrder(&nodeA);


	system("pause");
	return 0;
}