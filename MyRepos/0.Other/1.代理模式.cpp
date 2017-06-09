#include <iostream>
#include <cstdio>

using namespace std;

/* -----1. 代理模式 -----
class BeautyGirl
{
public:
	virtual void MakeEyesWithMan() = 0;
	virtual void HappyWithMan() = 0;
};

class Jinlian:public BeautyGirl
{
	virtual void MakeEyesWithMan()
	{
		cout << "金莲对你抛了一个媚眼" << endl;
	}

	virtual void HappyWithMan()
	{
		cout << "金莲和你进行了一次约会" << endl;
	}
};

class WangPo:public BeautyGirl
{
public:
	WangPo(BeautyGirl *girl) 		{ this->girl = girl; }
	virtual void MakeEyesWithMan() 	{ girl->MakeEyesWithMan(); }
	virtual void HappyWithMan()		{ girl->HappyWithMan(); }
private:
	BeautyGirl *girl;
};

int main(int argc, char const *argv[])
{
	BeautyGirl *jinlian = new Jinlian;
	WangPo *wangpo = new WangPo(jinlian);

	wangpo->MakeEyesWithMan();
	wangpo->HappyWithMan();

	delete wangpo;
	delete jinlian;
	return 0;
}*/

/* -----2. 装饰模式 -----*/
class Hero
{
public:
	virtual void status() = 0;
};

class Akali:public Hero
{
public:
	virtual void status()
	{
		cout << "----- 阿卡丽 -----" << endl;
		cout << " HP : 2000 " << endl;
		cout << " AD : 100 " << endl;
		cout << " AP : 200 " << endl;
	}
};

class Decorator:public Hero
{
public:
	Decorator(Hero *hero) { this->hero = hero; }
	virtual void status() = 0;
protected:
	Hero *hero;
};

class WYZHDecorator:public Decorator
{
public:
	WYZHDecorator(Hero *hero):Decorator(hero) {}
	virtual void status()
	{
		hero->status();
		cout << " 装备了 巫妖之祸, AP + 300 " << endl;
	}
};

class SYQZDecorator:public Decorator
{
public:
	SYQZDecorator(Hero *hero):Decorator(hero) {}
	virtual void status()
	{
		hero->status();
		cout << " 装备了 深渊权杖, AP + 500 " << endl;
	}
};

int main(int argc, char const *argv[])
{
	Hero *akali = new Akali;
	cout << " --- 阿卡丽 " << endl;
	akali->status();

	hero *wyakali = new WYZHDecorator(akali);
	wyakali->status();

	Hero *syakali = new SYQZDecorator(akali);
	syakali->status();
	return 0;
}