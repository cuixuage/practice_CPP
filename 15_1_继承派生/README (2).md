**派生类拷贝控制成员**   
理解:  
派生类对象拷贝和移动自身成员时，也需要拷贝和移动基类部分数据成员  

总结:  
派生类复制函数负责派生类的数据成员，基类复制函数只能负责基类部分的数据成员  
注:   
派生类\基类均显示定义复制函数(例如重载operator =),则在派生类拷贝移动函数中需要显示调用基类拷贝移动函数  


例如:  
基类:  
	Base & operator=(const Base & rhs)   
	{  
		cout << "Base & operator=(const Base&)" << endl;   
		if(this != &rhs)  		//思考； 拷贝构造函数或者拷贝赋值操作符 传递引用&参数的作用 
		{  
			delete [] _pdata1;  
			_pdata1 = new char[strlen(rhs._pdata1) + 1]();   
			strcpy(_pdata1, rhs._pdata1);   
		}  
		return *this;  
	}  

派生类:  
	Derived & operator=(const Derived & rhs)  
	{  
		cout << "Derived & operator=(const Derived & rhs)" << endl;  
		if(this != &rhs)  
		{  
			Base::operator=(rhs);					//必须加上  手动显式调用基类的相应拷贝移动函数  
													//这也是 派生类Derived对象向上转型为基类Base对象去初始化基类部分成员   									
			delete [] _pdata2;  
			_pdata2 = new char[strlen(rhs._pdata2) + 1]();  
			strcpy(_pdata2, rhs._pdata2);  
		}  
		return *this;  
	}  