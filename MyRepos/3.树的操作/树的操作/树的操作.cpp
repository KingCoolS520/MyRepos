#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// 二叉链表表示法
typedef struct _BiTNode
{
	struct _BiTNode *lchild, *rchild;
	char data;
}BiTNode;

// 中序遍历
void inOrder(BiTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	// 左子树
	inOrder(root->lchild);
	// 访问根节点
	printf("%c ", root->data);
	inOrder(root->rchild);
}


// 寻找最左边的节点
BiTNode* findLeft(BiTNode* root, stack<BiTNode*> &st)
{
	if (root == NULL)
	{
		return NULL;
	}
	// 如果有左子树
	while (root->lchild != NULL)
	{
		// 节点入栈
		st.push(root);
		// 指向左子树
		root = root->lchild;
	}
	return root;
}

// 中序非递归
void myOrder(BiTNode* root)
{
	if (root == NULL)
	{
		return;
	}
	stack<BiTNode*> st;
	// 步骤1
	BiTNode* pLeft = findLeft(root, st);

	while (pLeft)
	{
		// 访问
		cout << pLeft->data << " ";
		// 判断有没有右子树
		if (pLeft->rchild != NULL)
		{
			pLeft = findLeft(pLeft->rchild, st);
		}
		else
		{
			// 如果栈不为空
			if (!st.empty())
			{
				// 去出栈顶元素
				pLeft = st.top();
				// 出栈
				st.pop();
			}
			else
			{
				cout << "遍历结束" << endl;
				break;
			}
		}
	}
}

// 树的层序遍历
void layerOrder(BiTNode* root)
{
	if (root == NULL)
	{
		// 空树
		return;
	}
	// 创建对象
	queue<BiTNode*> q;
	// 根节点入队列
	q.push(root);

	// 如果队列为空, 遍历结束
	while (!q.empty())
	{
		// 取出队头元素
		BiTNode* p = q.front();
		// 访问
		cout << p->data << " ";
		// 出队列
		q.pop();
		// 判断该当前节点有没有左子树
		if (p->lchild != NULL)
		{
			q.push(p->lchild);
		}
		// 判断该当前节点有没有有子树
		if (p->rchild != NULL)
		{
			q.push(p->rchild);
		}
	}
}


// #法创建树
BiTNode* createTree()
{
	char c;
	cin >> c;
	if (c == '#')
	{
		return NULL;
	}
	// 创建根节点
	BiTNode* pNew = new BiTNode;
	// 初始化
	pNew->data = c;	// 数据
	pNew->lchild = createTree();	// 创建左子树
	pNew->rchild = createTree();	// 创建右子树

	return pNew;
}

// 销毁树
void destroyTree(BiTNode* root)
{
	// 后序方式销毁树
	if (root == NULL)
	{
		return;
	}
	// 销毁左子树
	destroyTree(root->lchild);
	// 销毁右子树
	destroyTree(root->rchild);
	cout << "销毁的节点: " << root->data << endl;
	// 释放根节点
	delete root;
}

int main()
{
	//构建一颗二叉树
	//用二叉链表示法
	//定义七个节点
	BiTNode nodeA, nodeB, nodeC, nodeD, nodeE, nodeF, nodeG;
	//节点初始化
	memset(&nodeA, 0, sizeof(BiTNode));
	memset(&nodeB, 0, sizeof(BiTNode));
	memset(&nodeC, 0, sizeof(BiTNode));
	memset(&nodeD, 0, sizeof(BiTNode));
	memset(&nodeE, 0, sizeof(BiTNode));
	memset(&nodeF, 0, sizeof(BiTNode));
	memset(&nodeG, 0, sizeof(BiTNode));

	//节点关系
	nodeA.data = 'A';	//节点值
	nodeA.lchild = &nodeB;	//左孩子
	nodeA.rchild = &nodeC;	//右孩子

	nodeB.data = 'B';	//节点值
	nodeB.lchild = &nodeD;	//左孩子
	nodeB.rchild = &nodeE;	//右孩子

	nodeC.data = 'C';	//节点值
	nodeC.lchild = &nodeF;	//左孩子
	nodeC.rchild = &nodeG;	//右孩子

	nodeD.data = 'D';	//节点值

	nodeE.data = 'E';	//节点值

	nodeF.data = 'F';	//节点值

	nodeG.data = 'G';	//节点值

	cout << "中序遍历: " << endl;
	inOrder(&nodeA);
	cout << endl;
	cout << "中序非递归: " << endl;
	myOrder(&nodeA);

	cout << "层序遍历树: " << endl;
	layerOrder(&nodeA);
	cout << endl;

	// 创建树
	cout << "输入字符串: 格式: ABDH#K###E##CFI###G#J##" << endl;
	BiTNode* root = createTree();
	inOrder(root);
	cout << endl;
	destroyTree(root);

	system("pause");
	return 0;
}
