#include <stdio.h>

/******************* 排序规则 *******************

	每次处理就是将无序数列的第一个元素与有序数列
	的元素从后往前逐个进行比较，找出插入位置，将
	该元素插入到有序数列的合适位置中。

	稳定性:插入排序是稳定的

***********************************************/

//插入排序算法(升序排列)
void insertionSort(int *array, int len)
{
	int i, j;
	int k = -1;
	int temp = -1;
	for (i = 1; i < len; ++i)
	{
		//待插入位置
		k = i;
		//保存第i个元素的值
		temp = array[k];
		//将第i个元素与前边的i-1个元素进行比较
		for (j = i - 1; (j >= 0) && (array[j] > temp); --j)
		{
			//符合条件的元素后移
			array[j + 1] = array[j];
			//记录k需要插入的位置
			k = j;
		}
		//将i位置的元素放到k位置
		array[k] = temp;
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
	for (int i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");

	//排序
	insertionSort(array, len);

	//遍历
	printf("插入排序之后的序列:	");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
}
#endif