#include <iostream>
#include <cstdio>

using namespace std;

/* ----- 1. 简单工厂模式 ---- 
class Fruit
{
public:
	virtual void getName() = 0;
};

class Apple:public Fruit
{
	virtual void getName() { cout << "我是苹果~" << endl; }
};

class Banana:public Fruit
{
	virtual void getName() { cout << "我是香蕉~" << endl; }
};

class Pear:public Fruit
{
	virtual void getName() { cout << "我是鸭梨~" << endl; }
};

class Factory
{
public:
	Fruit *createFruit(string name)
	{
		if (name == "apple")
			return new Apple;
		else if (name == "banana")
			return new Banana;
		else
			return new Pear;
	}
};

int main(int argc, char const *argv[])
{
	Factory *factory = new Factory;
	Fruit *fruit = NULL;
	fruit = factory->createFruit("apple");
	fruit->getName();
	delete fruit;
	fruit = NULL;

	fruit = factory->createFruit("banana");
	fruit->getName();
	delete fruit;
	fruit = NULL;

	fruit = factory->createFruit("pear");
	fruit->getName();
	delete fruit;
	fruit = NULL;

	delete factory;
	return 0;
}*/

/* ----- 2. 工厂方法模式 ------
class Fruit
{
public:
	virtual void getName() = 0;
};

class AbstractFactory
{
public:
	virtual Fruit *createFruit() = 0;
};

class Apple:public Fruit
{
	virtual void getName() { cout << "我是苹果~" << endl; }
};

class Banana:public Fruit
{
	virtual void getName() { cout << "我是香蕉~" << endl; }
};

class Pear:public Fruit
{
	virtual void getName() { cout << "我是鸭梨~" << endl; }
};

class AppleFactory:public AbstractFactory
{
public:
	virtual Fruit *createFruit() { return new Apple; }
};

class BananaFactory:public AbstractFactory
{
public:
	virtual Fruit *createFruit() { return new Banana; }
};

class PearFactory:public AbstractFactory
{
public:
	virtual Fruit *createFruit() { return new Pear; }
};

int main(int argc, char const *argv[])
{
	AbstractFactory *abFactory = NULL;
	Fruit *fruit = NULL;

	abFactory = new AppleFactory;
	fruit = abFactory->createFruit();
	fruit->getName();
	delete abFactory;
	delete fruit;
	return 0;
}*/

/* ----- 3. 抽象工厂模式 ------
class AbstractApple
{
public:
	virtual void getName() = 0;
};

class AbstractBanana
{
public:
	virtual void getName() = 0;
};

class ChinaApple:public AbstractApple
{
public:
	virtual void getName() { cout << "中国苹果~" << endl; }
};

class UsaApple:public AbstractApple
{
public:
	virtual void getName() { cout << "美国苹果~" << endl; }
};

class ChinaBanana:public AbstractBanana
{
public:
	virtual void getName() { cout << "中国香蕉~" << endl; }
};

class UsaBanana:public AbstractBanana
{
public:
	virtual void getName() { cout << "美国香蕉~" << endl; }
};

class AbstractFactory
{
public:
	virtual AbstractApple *createApple() = 0;
	virtual AbstractBanana *createBanana() = 0;
};

class ChinaFactory:public AbstractFactory
{
public:
	virtual AbstractApple *createApple()   { return new ChinaApple; }
	virtual AbstractBanana *createBanana() { return new ChinaBanana; }
};

class UsaFactory:public AbstractFactory
{
public:
	virtual AbstractApple *createApple() 	 { return new UsaApple; }
	virtual AbstractBanana *createBanana()   { return new UsaBanana; }
};

int main(int argc, char const *argv[])
{
	AbstractApple *apple = NULL;
	AbstractBanana *banana = NULL;
	AbstractFactory *factory = NULL;

	factory = new ChinaFactory;
	apple = factory->createApple();
	banana = factory->createBanana();
	apple->getName();
	banana->getName();

	delete apple;
	delete banana;
	delete factory;
	return 0;
}*/

/* ----- 4. 单例模式 ------
class Singelton
{
public:
	static Singelton *getInstance()
	{
		if(instance == NULL)
			instance = new Singelton;
		m_count++;
		return instance;
	}
	int getCount() { return m_count; }
private:
	Singelton()
	{
		instance = NULL;
		m_count = 0;
		cout << "构造函数私有化" << endl;
	}
	static int m_count;
	static Singelton *instance;
};

int Singelton::m_count = 0;
Singelton *Singelton::instance = NULL;

// 饿汉模式(已自动创建类对象)
class Singelton2
{
public:
	static Singelton2 *getInstance()
	{
		m_count++;
		return instance;
	}
	int getCount() { return m_count; }
private:
	Singelton2()
	{
		instance = NULL;
		m_count = 0;
	}
	static int m_count;
	static Singelton2 *instance;
};

int Singelton2::m_count = 0;
Singelton2 *Singelton2::instance = NULL;

int main(int argc, char const *argv[])
{
	Singelton *singer = Singelton::getInstance();
	cout << singer->getCount() << endl;
	Singelton *singer2 = Singelton::getInstance();
	cout << singer2->getCount() << endl;
	if(singer == singer2)
		cout << "二者是同一个实例" << endl;
	else
		cout << "二者不是同一个实例" << endl;

	cout << "----- 以下是 饿汉模式 -----" << endl;
	Singelton2 *singer3 = Singelton2::getInstance();
	cout << singer3->getCount() << endl;
	Singelton2 *singer4 = Singelton2::getInstance();
	cout << singer4->getCount() << endl;
	if(singer3 == singer4)
		cout << "二者是同一个实例" << endl;
	else
		cout << "二者不是同一个实例" << endl;
	return 0;
}*/