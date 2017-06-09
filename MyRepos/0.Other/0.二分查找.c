#include <stdio.h>

int bin(int *p, int low, int high, int data)  //二分查找
		// 传入:数组, 开始下标, 结束下标, 查找值
{
	while (low <= high) // 当开始下标 < 结束下标 循环
	{
		int mid = (low + high) / 2;	// 以开始加结束一半的下标值来判断
		if (p[mid] == data)			// 当下标值与查找值相等时, 返回下标位置
			return mid;
		else if (p[mid] > data)		// 当下标值大于查找值时, 返回high的值
			high = mid - 1;			// high等于当前下标-1, 避免下次重复循环当前下标
		else
			low = mid + 1;
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	int str[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
	printf ("%d\n", bin(str, 0, 11, 5));
	return 0;
}


/*int re_bin(int *p, int low, int high, int data)  //递归二分查找
{
	while (low <= high)
	{
	int mid = (low + high) / 2;
	if (p[mid] == data)
		return mid;
	else if (data < p[mid])
		return bin(p, low, mid-1, data);
	else
		return bin(p, mid+1, high, data);
	}
	return -1;
}*/
