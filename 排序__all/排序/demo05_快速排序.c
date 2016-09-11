#include <stdio.h>

//快速排序
void quickSort(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r;
		// 拿出第一个元素, 保存到x中,第一个位置成为一个坑
		int x = s[l];
		while (i < j)
		{
			// 从右向左找小于x的数
			while (i < j && s[j] >= x)
			{
				//左移, 直到遇到小于等于x的数
				j--;
			}
			if (i < j)
			{
				//将右侧找到的小于x的元素放入左侧坑中, 右侧出现一个坑
				//左侧元素索引后移
				s[i++] = s[j];
			}

			// 从左向右找大于等于x的数
			while (i < j && s[i] < x)
			{
				//右移, 直到遇到大于x的数
				i++;
			}
			if (i < j)
			{
				//将左侧找到的元素放入右侧坑中, 左侧出现一个坑
				//右侧元素索引向前移动
				s[j--] = s[i];
			}
		}
		//此时 i=j,将保存在x中的数填入坑中
		s[i] = x;
		quickSort(s, l, i - 1); // 递归调用 
		quickSort(s, i + 1, r);
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
	quickSort(array, 0, len-1);

	//遍历
	printf("快速排序之后的序列:	");
	for (i = 0; i < len; ++i)
	{
		printf("%d\t", array[i]);
	}
	printf("\n");
}
#endif