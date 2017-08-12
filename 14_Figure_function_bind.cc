#include <math.h>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;
using std::bind;


//基于对象的编程方式
//1. 具体类,不再是一个抽象类
//2. 其它的图形类也是与Figure无关的类
//3. 要调用的成员函数的名字可以进行灵活的变动
class Figure
{
public:
	Figure(){}
	
	//注册回调函数
	void setDisplayCallback(const function<void()> & cb)
	{	_displayCallback = cb;	}

	void setAreaCallback(const function<float()> & cb)
	{	_areaCallback = cb;	}

	//执行回调函数
	void handleDisplayCallback()
	{
		if(_displayCallback)
			_displayCallback();
	}
	float handleAreaCallback()
	{
		if(_areaCallback)
			return 	_areaCallback();
		else
			return 0;
	}

private:
	//function<void()> _displayCallback;
	auto _displayCallback
	//function<float()> _areaCallback;
	auto _areaCallback;
};


class Circle
{
public:
	Circle(float fradius)
	: _fradius(fradius)
	{}

	void show() const
	{	cout << "circle:";}

	float calcArea() 
	{
		return 3.14159 * _fradius * _fradius;
	}
private:
	float _fradius;
};

class Rectangle
{
public:
	Rectangle(float flength, float fwidth)
	: _flength(flength)
	, _fwidth(fwidth)
	{}

	void display() const
	{	cout << "rectangle:";}
	float area()
	{
		return _flength * _fwidth;
	}
private:
	float _flength;
	float _fwidth;
};

class Triangle 
{
public:
	Triangle(float fa, float fb, float fc)
	: _fa(fa)
	, _fb(fb)
	, _fc(fc)
	{}

	void print() const
	{	cout << "triangle:";}

	float statisticArea()
	{
		float p = (_fa + _fb + _fc) / 2;
		return sqrt(p * (p - _fa) * (p - _fb) * (p - _fc));//海伦公式
	}
private:
	float _fa;
	float _fb;
	float _fc;
};


void display(Figure & fig)
{
	fig.handleDisplayCallback();
	cout << fig.handleAreaCallback() << endl;
}

int main(void)
{
	Circle circle(10);
	Rectangle rectangle(3, 4);
	Triangle triangle(3, 4, 5);

	Figure fig;
	fig.setDisplayCallback(bind(&Circle::show, &circle));
	fig.setAreaCallback(bind(&Circle::calcArea, &circle));
	display(fig);

	fig.setDisplayCallback(bind(&Triangle::print, &triangle));
	fig.setAreaCallback(bind(&Triangle::statisticArea, &triangle));
	display(fig);

	fig.setDisplayCallback(bind(&Rectangle::display, &rectangle));
	fig.setAreaCallback(bind(&Rectangle::area, &rectangle));
	display(fig);
	return 0;
}
