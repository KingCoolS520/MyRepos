#define  _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <map>
#include <string>

using namespace std;

void testMultiMap()
{
	multimap<int, string> mmap;

	mmap.insert(make_pair(1, "teacher1"));
	mmap.insert(pair<int, string>(2, "teacher2"));
	mmap.insert(multimap<int, string>::value_type(2, "teacher22"));

	//mmap[2] = "teacher222";

	for (multimap<int, string>::iterator it = mmap.begin(); it != mmap.end(); it++) {
		cout << "key :" << it->first << ", value : " << it->second << endl;
	}

}

/*
公司有销售部（sale）（员工2名）、技术研发部
（development）（1人）、财务部（Financial）（2人）
人员信息有：姓名(name)，年龄(age)，电话(tel)、工资
(salary)等组成
通过 multimap进行 信息的插入、保存、显示.
*/

class Person {
public:
	Person(string name, int age, string tel, double salary) {
		this->name = name;
		this->age = age;
		this->tel = tel;
		this->salary = salary;
	}

	void display() {
		cout << "姓名:" << name << ", age:" << age << ", tel: " << tel << ",  salary: " << salary << endl;
	}

private:
	string name;
	int age;
	string tel;
	double salary;
};

void testMultimap2()
{
	Person p1("老王", 18, "11231232321132", 4000);
	Person p2("刘大爷", 88, "11321132", 2000);
	Person p3("赵小姐", 18, "1132112232", 200000);
	Person p4("李Boss", 48, "1132112232", 100000);
	Person p5("张工", 38, "1132112232", 18000);


	multimap<string, Person> companyMap;

	//保存 
	companyMap.insert(pair<string, Person>("sale", p3));
	companyMap.insert(pair<string, Person>("sale", p4));
	companyMap.insert(pair<string, Person>("development", p5));
	companyMap.insert(pair<string, Person>("Financial", p1));
	companyMap.insert(pair<string, Person>("Financial", p2));

	//显示所有员工信息
	for (multimap<string, Person>::iterator it = companyMap.begin(); it != companyMap.end(); it++) {
		cout << "部门：" << it->first;
		it->second.display();
	}
	
	cout << "-----" << endl;
	multimap<string, Person>::iterator it;
	it = companyMap.find("sale");
	int cnt = companyMap.count("sale");
	for (int i = 0; i < cnt; i++) {
		cout << "部门：" << it->first;
		it->second.display();
		it++;
	}

	pair<multimap<string, Person>::iterator, multimap<string, Person>::iterator> range = companyMap.equal_range("Financial");
	for (it = range.first; it != range.second; it++) {
		cout << "部门：" << it->first;
		it->second.display();
	}

}

int main(void)
{
	
	//testMultiMap();
	testMultimap2();
	return 0;
}