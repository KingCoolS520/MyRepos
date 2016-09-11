#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

//定义一个堆数据结构, 直接用数组存储也是可以的
typedef struct
{
	//指向数据的指针, 创建一个动态数组
	int *pnData;
	//当前堆中结点个数
	int nSize;
}MyHeap;

//进行比较调整新插入结点的位置
int IncreaseKey(MyHeap *pHeap, int nPos) 
{
	//循环和它的父节点比较
	while (nPos>1)  
	{
		//临时变量,存取新插入结点的值
		int nMax = pHeap->pnData[nPos]; 
		//计算父节点位置
		int nParent = nPos / 2;
		//如果大于它的父节点
		if (nMax > pHeap->pnData[nParent])
		{
			//将该节点与它的父节点调换位置
			pHeap->pnData[nPos] = pHeap->pnData[nParent];
			pHeap->pnData[nParent] = nMax;
			//记录下父节点的位置
			nPos = nParent;
		}
		else
		{
			//已找到合适的位置,插入完成
			break;
		}
	}
	return 1;
}

//往堆中插入新结点
int Insert(MyHeap *pHeap, int nData)
{
	//堆的结点数+1
	++pHeap->nSize;
	//赋值,将新数据插入到数组合空闲的位置,即最后一个数据后边
	pHeap->pnData[pHeap->nSize] = nData;
	//向上渗透
	IncreaseKey(pHeap, pHeap->nSize);
	return 1;
}

//得到堆中根结点的关键字,并删除这个结点
int PopMaxHeap(MyHeap *pHeap) 
{
	//保存根节点的值
	int nMax = pHeap->pnData[1];
	//根节点是在数组的的1号位置存储的
	int nPos = 1;
	//计算左孩子结点位置
	int nChild = nPos * 2; 
	//将最后一个数据的值赋给根结点
	int nTemp = pHeap->pnData[nPos] = pHeap->pnData[pHeap->nSize];
	//向下寻找如果计算出的左孩子位置大于数组中元素的个数结束循环
	while (nChild <= pHeap->nSize)
	{
		//如果左孩子小于右孩子的值
		if (nChild + 1 <= pHeap->nSize && pHeap->pnData[nChild] < pHeap->pnData[nChild + 1])
		{
			++nChild;
		}
		if (nTemp >= pHeap->pnData[nChild])
			break;
		//左右孩子中较大的一个移动到他们的父节点的位置
		pHeap->pnData[nPos] = pHeap->pnData[nChild];
		nPos = nChild;
		//找到nPos的左孩子
		nChild *= 2;
	}
	
	pHeap->pnData[nPos] = nTemp;
	--pHeap->nSize;
	return nMax;
}

void heapSort(int* array, int len)
{
	int i;
	MyHeap myHeap;
	myHeap.pnData = (int*)malloc(sizeof(int)* (len+1));
	myHeap.nSize = 0;
	for (i = 1; i <= len; i++)
	{
		Insert(&myHeap, array[i-1]);
	}
	for (i = 1; i <= len; i++)
	{
		PopMaxHeap(&myHeap);
		//printf("%d\t", PopMaxHeap(&myHeap));
	}
	free(myHeap.pnData);
}

#if 0
void main()
{
	int i;
	//定义整型数组
	int array[] = { 12, 5, 33, 6, 10 };
	//计算数组长度
	int len = sizeof(array) / sizeof(int);
	//遍历数组
	printf("待排序数组序列: ");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");


	//遍历
	printf("堆排序之后的序列: ");
	heapSort(array, len);
	printf("\n");
}
#endif

