#include <stdio.h>
#include <stdlib.h>

/********************* 排序规则 *********************

冒泡排序算法的运作如下：（从后往前）
	1. 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
	2. 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
	3. 针对所有的元素重复以上的步骤，除了最后一个。
	4. 持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。

稳定性:冒泡排序是一种稳定排序算法

***************************************************/

//冒泡排序(升序)
void bubbleSort(int *array, int len)	//O(n²)
{
#if 1
	// 往上冒泡
	// 外层循环
	// flag == 0 没有排好   == 1 排好了
	int flag = 0;
	for (int i = len - 1; (flag==0) && i > 0; --i)
	{
		// 认为下边for循环走完之后序列有序
		flag = 1;
		// 内层循环
		for (int j = 0; j < i; ++j)
		{
			// 相邻的两个元素进行比较
			if (array[j] > array[j + 1])
			{
				// 交换位置
				int tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
				// 如果进入到了if语句,就认为没有排好
				flag = 0;
			}
		}
	}
#else
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = len - 1; j>i; --j)
		{
			// 交换
			if (array[j - 1] > array[j])
			{
				int tmp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = tmp;
			}
		}
	}
#endif
}

// for (int i = 0; i < len - 1; ++i)
// {
// 	for (int j = 0; j < len-i-1; ++j)
// 	{
//		if(array[j] array[j+1]
// 	}
// }

#if 0
void main()
{
	int i;
	//定义整型数组
	int array[] = { 11, 8, 7, 6, 3 };
	//计算数组长度
	int len = sizeof(array) / sizeof(int);
	//遍历数组
	printf("待排序数组序列: ");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");

	//排序
	bubbleSort(array, len);

	//遍历
	printf("冒泡排序之后的序列:	");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
	system("pause");
}
#endif

