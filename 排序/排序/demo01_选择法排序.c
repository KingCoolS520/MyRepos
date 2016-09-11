#include <stdio.h>
#include <stdlib.h>

/*-------------------- 排序规则 --------------------

		它的工作原理是每一次从待排序的数据元素中选出
		最小（或最大）的一个元素，存放在序列的起始位
		置，直到全部待排序的数据元素排完。

		稳定性:选择排序是不稳定的排序方法 如:[5,5,3]

-------------------------------------------------*/

//选择排序(升序排列)
void selectionSort(int *array, int len)
{
	int min;
	// 外层循环
	for (int i = 0; i < len - 1; ++i)
	{
		// 初始化
		min = i;
		// 内存循环
		for (int j = i + 1; j < len; ++j)
		{
			// 比较
			if (array[j] < array[min])
			{
				// 记录最小值的位置
				min = j;
			}
			else
			{
				break;
			}
		}
		// 交换
		if (min != i)
		{
			int tmp = array[i];
			array[i] = array[min];
			array[min] = tmp;
		}
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

	//排序
	selectionSort(array, len);

	//遍历
	printf("选择排序之后的序列:	");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
	system("pause");
}
#endif