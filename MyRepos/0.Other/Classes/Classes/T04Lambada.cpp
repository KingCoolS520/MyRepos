#include "T04Lambada.h"


T04Lambada::T04Lambada()
{
}


T04Lambada::~T04Lambada()
{
}


bool T04Lambada::init()
{
	Layer::init();

	// Lambada
	// 匿名函数
	int a = []{return 1; }();
	CCLOG("a= %d", a);

	// 将Lambada表达式赋值给一个变量
	auto func = []{return 1; };
	a = func();

	// 完整的Lambada表达式的样例
	{
		auto func = []()mutable->bool{
			return true;
		};
		// []表示捕获列表，在[]的表达式表示捕获该lambada表达式外部的变量 
		// () 表示参数列表，跟普通的参数列表没有区别，也可以省略
		// ->int 返回类型，通常省略
		// {} 函数体，跟普通函数也没有区别
		// mutable,跟捕获列表有关系
	}

	{
		// 捕获列表，用来捕获外部变量
		int a = 10;
		int b = 20;
		auto func = [a, b](){
			CCLOG("%d, %d", a, b);
		};

		// 捕获列表的另外一种捕获方法，使用=捕获所有外部变量
		auto func1 = [=](){
			CCLOG("%d, %d", a, b);
		};

		// 使用=或者是变量名捕获的变量，只能读，不能写
		auto func2 = [=](){
		//	a++; ERROR
			CCLOG("%d, %d", a, b);
		};

		// 使用&符号捕获外部变量
		auto fun3 = [&a]()
		{
			a++;
		};

		// 也可以直接用&符号捕获所有外部变量
		auto func4 = [&]()
		{
			a++;
			b++;
		};

		// 也可以直接用&符号捕获所有外部变量
		auto func5 = [=, &b]()
		{
			//a++;
			// b++ ERROR
		};


		// 使用传值捕获的时候，如果Lambada表示被mutable关键字修饰，那么
		// 在函数体中，也可以修改捕获变量，但是这种修改，不改变外部变量
		auto func6 = [a]()mutable{ a++; };
		
	}

	// 为什么要设计Lambada表达式，优势在哪里？
	// 在函数定义的时候，可以给该函数参数

	// Lambada表达式和std::function的关系
	std::function<void()> f = []{};

	Sprite* sprite = Sprite::create("CloseNormal.png");
	_sprite = sprite;
	addChild(sprite);
	sprite->setPosition(200, 200);

	auto ev = EventListenerTouchOneByOne::create();
	ev->onTouchBegan = [](Touch*, Event*){return true; };
	ev->onTouchMoved = [&](Touch* touch, Event*)
	{
		sprite->setPosition(touch->getLocation());
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);




	return true;
}