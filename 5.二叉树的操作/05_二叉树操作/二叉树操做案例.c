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

// 求树的叶子节点的个数
int number = 0;
void leafNum(BiTNode *root)
{
	if (root == NULL)
	{
		return;
	}
	// 是不是叶子节点
	if (root->left == NULL && root->right == NULL)
	{
		number++;
	}
	// 遍历左子树
	leafNum(root->left);
	// 遍历右子树
	leafNum(root->right);
}

void leafNum_plus(BiTNode *root, int *num)
{
	if (root == NULL)
	{
		return;
	}
	// 遍历左子树
	leafNum_plus(root->left, num);
	// 遍历右子树
	leafNum_plus(root->right, num);
	// 是不是叶子节点
	if (root->left == NULL && root->right == NULL)
	{
		(*num)++;
	}
}

int leafNum_plus1(BiTNode *root)
{
	if (root == NULL)
	{
		return 0;
	}
	// 遍历左子树
	int  left = leafNum_plus1(root->left);
	// 遍历右子树
	int right = leafNum_plus1(root->right);
	// 是不是叶子节点
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return left + right;
}

// 求树的高度
int depthTree(BiTNode* root)
{
	// 空树
	if (root == NULL)
	{
		return 0;
	}
	// 求左子树高度
	int left = depthTree(root->left);
	// 求右子树
	int right = depthTree(root->right);
	// 取比较高的树
	int max = left > right ? left : right;
	// 当前树的高度 = 子树高度+1
	max++;
	return max;
}

// 拷贝二叉树
BiTNode* copyTree(BiTNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	// 拷贝左子树
	BiTNode* left = copyTree(root->left);
	// 创建新节点
	BiTNode* pNew = (BiTNode*)malloc(sizeof(BiTNode));
	// 拷贝右子树
	BiTNode* right = copyTree(root->right);

	// 连接节点
	pNew->data = root->data;
	pNew->left = left;
	pNew->right = right;
	
	return pNew;
}


int main()
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
	printf("中序遍历:\n");
	inOrder(&nodeA);
	printf("\n");
	// 后序
	postOrder(&nodeA);

	// 求叶子节点
	leafNum(&nodeA);
	printf("\n叶子节点的个数: %d\n", number);

	int num = 0;
	num = leafNum_plus1(&nodeA);
	printf("\n----叶子节点的个数: %d\n", num);

	// 树的高度
	int depth = depthTree(&nodeA);
	printf("树的高度: %d\n", depth);

	// 拷贝二叉树
	BiTNode *root = copyTree(&nodeA);
	// 中序遍历新树
	inOrder(root);
	printf("\n");



	system("pause");
	return 0;
}