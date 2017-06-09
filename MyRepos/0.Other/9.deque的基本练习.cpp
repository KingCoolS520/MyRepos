#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <deque>

using namespace std;

void printDeque(deque<int> &d)
{
	for (deque<int>::iterator it = d.begin(); it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}


void testDeque() {
	deque<int> d;

	d.push_back(3);
	d.push_back(4);
	d.push_back(6);
	d.push_back(8);
	d.push_back(0);

	printDeque(d);

	d.push_front(-1);
	d.push_front(-3);
	d.push_front(-7);
	d.push_front(-10);

	printDeque(d);


	d.pop_back();

	printDeque(d);

	d.pop_front();
	printDeque(d);


	cout << "首元素" << d.front() << endl;
	cout << "尾元素" << d.back() << endl;

}

//deque 的删除
void testDeque2() {
	//1, 4,5,7,8,9,8,3,8,10,8
	int array[11] = { 1, 4, 5, 7, 8, 9, 8, 3, 8, 10, 8 };

	deque<int> d(array, array + 10);


	for (deque<int>::iterator it = d.begin(); it != d.end();) {
		if (*it == 8) {
			it = d.erase(it);
		}
		else {
			it++;
		}
	}

	printDeque(d);
}

int main(void)
{
	//testDeque();
	testDeque2();
	
	return 0;
}