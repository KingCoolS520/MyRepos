#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

int bin(vector<int> v, int bidx, int eidx, int n)
{
	while (bidx <= eidx)
	{
		int mid = (bidx + eidx) / 2;
		if (v[mid] == n)
			return mid;
		else if (v[mid] > n)
			//eidx = mid - 1;
			return bin(v, bidx, mid - 1, n);
		else
			//bidx = mid + 1;
			return bin(v, mid+1, eidx, n);
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	vector<int> v = { 0, 11, 122, 233, 144, 355, 266, 177, 288, 399, 111 };

	sort(v.begin(), v.end());	// 实现升序排列

	//reverse(v.begin(), v.end());	// 实现反转数组(头文件:<algorithm>)

	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	cout << bin(v, 0, v.size(), 399) << endl;

	return 0;
}