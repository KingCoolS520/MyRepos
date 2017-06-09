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
	// ��������
	int a = []{return 1; }();
	CCLOG("a= %d", a);

	// ��Lambada����ʽ��ֵ��һ������
	auto func = []{return 1; };
	a = func();

	// ������Lambada����ʽ������
	{
		auto func = []()mutable->bool{
			return true;
		};
		// []��ʾ�����б�����[]�ı���ʽ��ʾ�����lambada����ʽ�ⲿ�ı��� 
		// () ��ʾ�����б�������ͨ�Ĳ����б�û������Ҳ����ʡ��
		// ->int �������ͣ�ͨ��ʡ��
		// {} �����壬����ͨ����Ҳû������
		// mutable,�������б��й�ϵ
	}

	{
		// �����б������������ⲿ����
		int a = 10;
		int b = 20;
		auto func = [a, b](){
			CCLOG("%d, %d", a, b);
		};

		// �����б�������һ�ֲ��񷽷���ʹ��=���������ⲿ����
		auto func1 = [=](){
			CCLOG("%d, %d", a, b);
		};

		// ʹ��=�����Ǳ���������ı�����ֻ�ܶ�������д
		auto func2 = [=](){
		//	a++; ERROR
			CCLOG("%d, %d", a, b);
		};

		// ʹ��&���Ų����ⲿ����
		auto fun3 = [&a]()
		{
			a++;
		};

		// Ҳ����ֱ����&���Ų��������ⲿ����
		auto func4 = [&]()
		{
			a++;
			b++;
		};

		// Ҳ����ֱ����&���Ų��������ⲿ����
		auto func5 = [=, &b]()
		{
			//a++;
			// b++ ERROR
		};


		// ʹ�ô�ֵ�����ʱ�����Lambada��ʾ��mutable�ؼ������Σ���ô
		// �ں������У�Ҳ�����޸Ĳ�����������������޸ģ����ı��ⲿ����
		auto func6 = [a]()mutable{ a++; };
		
	}

	// ΪʲôҪ���Lambada����ʽ�����������
	// �ں��������ʱ�򣬿��Ը��ú�������

	// Lambada����ʽ��std::function�Ĺ�ϵ
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