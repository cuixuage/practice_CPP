**�����࿽�����Ƴ�Ա**   
���:  
��������󿽱����ƶ������Աʱ��Ҳ��Ҫ�������ƶ����ಿ�����ݳ�Ա  

�ܽ�:  
�����ิ�ƺ�����������������ݳ�Ա�����ิ�ƺ���ֻ�ܸ�����ಿ�ֵ����ݳ�Ա  
ע:   
������\�������ʾ���帴�ƺ���(��������operator =),���������࿽���ƶ���������Ҫ��ʾ���û��࿽���ƶ�����  


����:  
����:  
	Base & operator=(const Base & rhs)   
	{  
		cout << "Base & operator=(const Base&)" << endl;   
		if(this != &rhs)  		//˼���� �������캯�����߿�����ֵ������ ��������&���������� 
		{  
			delete [] _pdata1;  
			_pdata1 = new char[strlen(rhs._pdata1) + 1]();   
			strcpy(_pdata1, rhs._pdata1);   
		}  
		return *this;  
	}  

������:  
	Derived & operator=(const Derived & rhs)  
	{  
		cout << "Derived & operator=(const Derived & rhs)" << endl;  
		if(this != &rhs)  
		{  
			Base::operator=(rhs);					//�������  �ֶ���ʽ���û������Ӧ�����ƶ�����  
													//��Ҳ�� ������Derived��������ת��Ϊ����Base����ȥ��ʼ�����ಿ�ֳ�Ա   									
			delete [] _pdata2;  
			_pdata2 = new char[strlen(rhs._pdata2) + 1]();  
			strcpy(_pdata2, rhs._pdata2);  
		}  
		return *this;  
	}  