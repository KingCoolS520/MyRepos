#include <stdio.h>

/**************************** 排序规则 ****************************

	希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；
	随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰
	被分成一组，算法便终止。

	稳定性: 希尔排序是非稳定排序算法。

*****************************************************************/

//插入排序
#if 0
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
#endif

//希尔排序
void shellSort(int *array, int len)
{
	int j, i;
	int gap = len;
	int temp = -1;
	do
	{
		//效率比较高的计算步长的算法
		gap = gap / 3 + 1; //O(n*1.3)
		//gap组进行排序
		for (int k = 0; k <gap; ++k)
		{
			//对每一组进行插入排序
			for (i = gap+k; i<len; i+=gap)
			{
				//printf("i = %d\n", i);
				//保存待插入元素的位置
				int k = i;
				//保存i位置的元素的值
				temp = array[k];
				//分组插入排序
				for (j = i - gap; (j >= 0) && (array[j] > temp); j -= gap)
				{
					array[j + gap] = array[j];
					k = j;
				}
				//将数据插入到有序序列中的合适位置
				array[k] = temp;
			}
		}
	} while (gap > 1);
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
	shellSort(array, len);

	//遍历
	printf("希尔排序之后的序列:	");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
}
#endif