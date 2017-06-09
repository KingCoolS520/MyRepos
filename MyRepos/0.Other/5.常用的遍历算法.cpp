#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>

#include <algorithm>
#include <vector>
#include <list>
#include <functional>

using namespace std;


void printInt(int &value)
{
	cout << value << " ";
}

class Show
{
public:
	Show() {
		cnt = 0;
	}
	void operator()(int &value) {
		cout << value << " ";
		cnt++;
	}

	int getCnt() {
		return cnt;
	}
private:
	int cnt;
};

void test_for_each() {
	vector<int> vec;

	for (int i = 0; i < 10; i++) {
		vec.push_back(rand() % 20);
	}
	vec.push_back(3);
	vec.push_back(3);
	vec.push_back(3);
	vec.push_back(3);
	vec.push_back(2);

	for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
		printInt(*it);
	}
	cout << endl;

	Show showObj;
	/*
	_Fn1 for_each(_InIt _First, _InIt _Last, _Fn1 _Func)  //_Func = showObj
	{	// perform function for each element
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Func);
	_For_each(_Unchecked(_First), _Unchecked(_Last), _Func);
		return _Func;                         //showObj = _Func
	*/
	showObj = for_each(vec.begin(), vec.end(), showObj);
	cout << endl;

	cout << "cnt: " << showObj.getCnt() << endl;
}

int increase(int &value) {
	return value + 100;
}

void test_transform() 
{
	vector<int> vec;
	vector<int> vec2;

	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(9);

	vec2.resize(vec.size());

	list<int> lst;

	for_each(vec.begin(), vec.end(), printInt);
	cout << endl;

	/*
	_OutIt _Transform(_InIt1 _First1, _InIt1 _Last1,
	_InIt2 _First2, _OutIt _Dest, _Fn2 _Func)
	{	// transform [_First1, _Last1) and [_First2, ...) with _Func
	for (; _First1 != _Last1; ++_First1, ++_First2, ++_Dest)
	*_Dest = _Func(*_First1, *_First2);
	return (_Dest);
	}
	*/
	//transform 在搬运过程中， 不会给目标容器开辟空间
	//提供的函数对象或是回调函数，必须要有返回值。
	//transform(vec.begin(), vec.end(), vec2.begin(), increase);
	transform(vec.begin(), vec.end(), vec2.begin(), bind2nd(plus<int>(), 100));

	for_each(vec2.begin(), vec2.end(), printInt);
	cout << endl;


	//1 给目标容器开辟空间
	lst.resize(vec.size());
	transform(vec.begin(), vec.end(), vec2.begin(), lst.begin(), plus<int>());

	for_each(lst.begin(), lst.end(), printInt);
	cout << endl;

}

int main(void)
{
	//test_for_each();
	test_transform();
	return 0;
}