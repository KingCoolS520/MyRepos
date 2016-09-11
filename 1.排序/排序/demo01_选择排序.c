#include <stdio.h>

/*-------------------- 排序规则 --------------------

		它的工作原理是每一次从待排序的数据元素中选出
		最小（或最大）的一个元素，存放在序列的起始位
		置，直到全部待排序的数据元素排完。

		稳定性:选择排序是不稳定的排序方法 如:[5,5,3]

-------------------------------------------------*/

//选择排序(升序排列)
void selectionSort(int *array, int len)
{
	int i, j;
	//保存小元素的位置
	int minIndex = 0;
	//外层做 len-1 次循环
	for (i = 0; i < len-1; ++i)
	{
		minIndex = i;
		//内层做 len-1-i 次循环
		for (j = i + 1; j < len; ++j)
		{
			//比较大小
			if (array[minIndex] > array[j])
			{
				//找最小元素的位置
				minIndex = j;
			}
		}
		//****** 交换两个两个元素的值,每一趟最多只交换一次 ******
		if (minIndex != i)
		{
			int temp = array[i];
			array[i] = array[minIndex];
			array[minIndex] = temp;
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
}
#endif