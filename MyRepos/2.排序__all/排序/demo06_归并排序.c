#include <stdio.h>
#include <stdlib.h>

//将两个有序数列a[first...mid]和a[mid+1...last]合并。
void mergeArray(int a[], int first, int mid, int last, int temp[])
{
	int leftStart = first;	//左有序序列起点
	int leftEnd = mid;	//左有序序列终点
	int rightStart = mid + 1;	//右有序序列起点
	int rightEnd = last;	//右有序序列终点
	int length = 0;	//两个有序序列合并之后的有序序列长度
	int i = leftStart, j = rightStart;
	
	//将两个有序序列中的元素合并到第三个有序序列中(a的左半部分和右半部分合并到temp中)
	while (i <= leftEnd && j <= rightEnd)
	{
		//按照从小到大的顺序放入到temp中
		if (a[i] <= a[j])
		{
			temp[length++] = a[i++];
		}
		else
		{
			temp[length++] = a[j++];
		}
	}
	//如果左半部分还有元素, 直接放到temp中
	while (i <= leftEnd)
	{
		temp[length++] = a[i++];
	}
	//如果右半部分还有元素, 直接放到temp中
	while (j <= rightEnd)
	{
		temp[length++] = a[j++];
	}
	//将temp中排好的序列拷贝到a数组中
	for (i = 0; i < length; i++)
	{
		//只替换已排好序的那一部分
		a[leftStart + i] = temp[i];
	}
}

//归并排序
void mergeSort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		//找到数组的中间位置
		int mid = (first + last) / 2;
		//左边有序
		mergeSort(a, first, mid, temp);  
		//右边有序
		mergeSort(a, mid + 1, last, temp); 
		//再将二个有序数列合并
		mergeArray(a, first, mid, last, temp); 
	}
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
}
#endif