#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printVector(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

class Teacher{
public:
	Teacher(string name, int age) {
		this->name = name;
		this -> age = age;
	}

	void show() {
		cout << "name: " << name << ", age :" << age << endl;
	}

private:
	string name;
	int age;
};


//vector的基本赋值
void testvector1() {
	vector<int> vec;

	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(9);

	vector<int> vec2 = vec;

	vector<int> vec3(vec);
	vector<int> vec4;

	vec4.assign(vec.begin(), vec.end());

	printVector(vec4);

	cout << "第一个元素" << endl;
	cout << vec.front() << endl;
	cout << "最后一个元素" << endl;
	cout << vec.back() << endl;


	/*
	reference front()
	{	// return first element of mutable sequence
	return (*begin());
	}

	*/
	vec.front() = 3;
	vec.back() = 20;

	printVector(vec);

	int last = vec.back();
	vec.pop_back();

	cout << "----" << endl;
	printVector(vec);
	printVector(vec4);
	vec.swap(vec4);
	printVector(vec);
	printVector(vec4);

	cout << "vec:size():" << vec.size() << endl;
	vec.resize(10);//重新给vec开辟10个空间,从已有的空间增加或减少,默认填充值为0
	printVector(vec);
	vec.resize(15, 8);	// 重新给vec开辟15个空间,默认填充值为8
	printVector(vec);
}

void testVector2() {
	Teacher t1("张老师", 45);
	Teacher t2("刘老师", 85);
	Teacher t3("离开老师", 25);
	Teacher t4("王老师", 18);

	vector<Teacher> vecT;

	vecT.push_back(t1);
	vecT.push_back(t2);
	vecT.push_back(t3);
	vecT.push_back(t4);


	//正向遍历
	for (vector<Teacher>::iterator it = vecT.begin(); it != vecT.end(); it++) {
		(*it).show();
	}

	cout << "-----" << endl;
	//反向遍历
	for (vector<Teacher>::reverse_iterator rit = vecT.rbegin(); rit != vecT.rend(); rit++) {
		(*rit).show();
	}

	vector<Teacher>::iterator it = vecT.begin();

	it = it + 2; //任意跨度 叫随机，随机访问迭代器是跟容器的特性来的
	(*it).show();


}

//vector的插入与删除
void testVector3() {
	vector<int> vA;
	vector<int> vB;


	vA.push_back(2);
	vA.push_back(3);
	vA.push_back(6);
	vA.push_back(7);
	printVector(vA);

	//在首位置插入元素,插入的元素不是根据整形位置int计算， 而是需要迭代器
	vA.insert(vA.begin(), 9);
	printVector(vA);

	vB.push_back(9);
	vB.push_back(10);

	//向vA中插入另一个容器
	vA.insert(vA.begin(), vB.begin(), vB.end());
	printVector(vA);

	vA.insert(vA.begin(), 3, 10);

	printVector(vA);

	cout << "----" << endl;
	//删除
	vA.erase(vA.begin() + 1);
	printVector(vA);
	//10 10 9 10 9 2 3 3 6 7

	vA.erase(vA.begin(), vA.begin() + 3);
	printVector(vA);

	vA.push_back(10);
	vA.push_back(10);
	vA.push_back(10);
	vA.push_back(10);
	vA.push_back(10);

	// 删除所有值为10的元素
	for (vector<int>::iterator it = vA.begin(); it != vA.end();) {
		if (*it == 10) {
			//调用erase函数，返回的是元素下一个位置，需要用迭代器接回来。
			it = vA.erase(it);
		}
		else {
			it++;
		}
	}
	printVector(vA);


	//两种清空容器的方法
	vA.erase(vA.begin(), vA.end());
	if (vA.empty()) {
		cout << "kong" << endl;
	}
	vA.push_back(1);
	vA.clear();
	if (vA.empty()) {
		cout << "kong" << endl;
	}
}
int main(void)
{
	//testvector1();
	//testVector2();
	testVector3();
	return 0;
}