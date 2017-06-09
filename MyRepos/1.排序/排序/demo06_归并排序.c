#include <stdio.h>
#include <stdlib.h>

//将两个有序数列a[first...mid]和a[mid+1...last]合并。
void mergeArray(int a[], int first, int mid, int last, int temp[])
{
	int leftStart = first;	//	左子树数组开始位置
	int leftEnd = mid;	// 结束位置
	int rightStart = mid + 1;	// 右子树数组开始位置
	int rightEnd = last;	// 右 -- 结束位置
	// 长度
	int length = 0;	// 记录从first -- last 共有多少个元素
	int i = leftStart;
	int j = rightStart;

	// 合并连个有序序列
	while (i <= leftEnd && j <= rightEnd)
	{
		if (a[i] < a[j])
		{
			// 取出小的
			temp[length] = a[i];
			length++;
			i++;
		}
		else
		{
			temp[length++] = a[j++];
		}
	}

	// 剩下了一个有序序列还有数据
	while (i <= leftEnd)
	{
		//取出剩下的数据
		temp[length++] = a[i++];
	}
	while (j <= rightEnd)
	{
		temp[length++] = a[j++];
	}

	// temp是一个新的有序序列
	// 覆盖指定位置的无序序列
	for (int i = 0; i < length; ++i)
	{
		a[first + i] = temp[i];
	}
}

//归并排序
void mergeSort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		// 找到中间位置
		int mid = (first + last) / 2;
		// 递归调用
		// 拆分左半边
		mergeSort(a, first, mid, temp);
		// 拆分右半边
		mergeSort(a, mid + 1, last, temp);
		// 合并两个有序序列
		mergeArray(a, first, mid, last, temp);
	}
}

#if 1
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

	//创建合适大小的临时数组
	int *p = (int*)malloc(sizeof(int) * len);
	if (p == NULL)
	{
		return;
	}
	mergeSort(array, 0, len - 1, p);
	free(p);

	//遍历
	printf("归并排序之后的序列:	");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
	system("pause");
}
#endif