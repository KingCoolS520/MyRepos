#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <map>
#include <string>

using namespace std;

void testMap() 
{
	map<int, string> map1;

	//插入方法一
	pair<map<int, string>::iterator , bool> result = map1.insert(pair<int, string>(1, "teacher1"));
	if (result.second == true) {
		cout << "插入成功" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}
	else {
		cout << "插入失败" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}

	//插入方法二
	result = map1.insert(make_pair(2, "teacher2"));
	if (result.second == true) {
		cout << "插入成功" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}
	else {
		cout << "插入失败" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}

	//插入方法三
	result = map1.insert(map<int, string>::value_type(3, "teacher3"));
	if (result.second == true) {
		cout << "插入成功" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}
	else {
		cout << "插入失败" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}

	result = map1.insert(map<int, string>::value_type(3, "teacher33"));
	if (result.second == true) {
		cout << "插入成功" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}
	else {
		cout << "插入失败" << endl;
		cout << "key: " << result.first->first << ", value: " << result.first->second << endl;
	}

	//插入方法四
	map1[4] = "teacher4";
	map1[4] = "teacher44";

	cout << "---取值---" << endl;
	cout << map1[5] << endl;
	cout << "---取值---" << endl;

	//方法四，会无条件的覆盖value值

	//遍历
	for (map<int, string>::iterator it = map1.begin(); it != map1.end(); it++) {
		cout << "key: " << it->first << ", value : " << it->second << endl;
	}
	map<int, string>::iterator it = map1.begin();
	while (!map1.empty()) {
		it = map1.begin();
		map1.erase(it);
	}

	if (map1.empty()) {
		cout << "kong" << endl;
	}

}

int main(void)
{
	testMap();
	
	return 0;
}