#include <stdio.h>
#include <stdlib.h>

/**************************** 排序规则 ****************************

	希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；
	随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰
	被分成一组，算法便终止。

	稳定性: 希尔排序是非稳定排序算法。

*****************************************************************/
//希尔排序
void shellSort(int *array, int len)
{
	// 步长 
	int gap = len;
	while (gap > 1)
	{
		// 步长递减
		gap = gap / 3 + 1;	// 分为了gap组
		printf("gap = %d\n", gap);
		// 对每一组进行插入排序
		for (int i = 0; i < gap; ++i)
		{
			int tmp;	// 第一个坑的数值
			int index;	// 坑的位置
			// 插入排序
			// 遍历无序序列
			for (int j = i + gap; j < len; j += gap)
			{
				tmp = array[j];
				index = j;
				for (int k = j - gap; k >= 0; k -= gap)
				{
					// 判断
					if (tmp < array[k])
					{
						array[k + gap] = array[k];
						// 记录新坑的位置
						index = k;
					}
					else
					{
						break;
					}
				}
				// 填坑
				array[index] = tmp;
			}
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
	system("pause");
}
#endif