#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//决定一个函数
// 1. 返回类型
// 2,函数参数的类型和个数


int add(int a ,int b)
{
	return a + b;
}

int mult(int a, int b)
{
	return a*b;
}


//架构
int show(int a, int(*p)(int, int))
{
	//固定业务1
	// 自定义业务
	//用回调函数来完成
	p(a, a);
	//固定业务=2
	//固定业务3
	//固定业务4

	return p(a, a);
}

int main(void)
{
	int a = 10;
	int ret = show(a, mult);

	printf("%d\n", ret);

	return 0;
}