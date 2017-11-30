#include <iostream>
#include <memory>
using std::cout;
using std::endl;

template <typename T>
class Vector{
public:
	Vector();
	~Vector();
	void push_back(const T &);
	void pop_back();
	void clear();
	const T &operator[] (int idx) const;
	
	int size() const{						//Ԫ�ظ���
		return _firstFree - _elems;
	}
	int capacity() const{					//�������
		return _end - _elems;
	}

private:
	void reallocate();   //push_backʱ��� size() == capacity()��

private:
	static std::allocator<T> _alloc;   //�ռ����ӿڲ�ľ�̬����
	T * _elems;
	T * _firstFree;
	T * _end;
};

template <typename T>
Vector<T>::Vector()
:_elems(0)
,_firstFree(0)
,_end(0){
	cout << "Vector() ok" <<endl;
}

template <typename T>
Vector<T>::~Vector(){
	if(_elems){
		while(_elems != _firstFree)
			_alloc.destroy(--_firstFree);				//���Լ�; destroy(p) ɾ��ָ��pָ�����T
		_alloc.deallocate(_elems,capacity());			//deallocate(p,n)  �ͷ�p��ʼn��������ڴ�(�ȶ�ÿһ��Ԫ�ؽ���destory)
	}
	cout<< "~Vector() ok"<<endl;
}

template <typename T>
void Vector<T>::push_back(const T & value){
	if( size() == capacity() )
		reallocate();
												//ֱ�Ӵ�����һ��T ����
	_alloc.construct(_firstFree++ , value);     //Ԫ�ص���� ʵ�ʵ��ö�λ���ʽnew((void*)Pointer)T(value)
}

template <typename T>
void Vector<T>::pop_back(){
	if(size()>0){
		_alloc.destroy(--_firstFree);			
	}
}

template <typename T>
const T & Vector<T>::operator[] (int idx) const {
	return _elems[idx];
}

/*
�ɿռ�����ת�Ƶ��¿ռ�
����1:
uninitialized_copy(b,e,b2);
allocator���溯�� ����δ��ʼ����b2�ڴ� ʹ��b,e����iterator֮���Ԫ�ؿ������

����2:
T * newelems = _alloc.allocate(newcapacity);
for(size_t i=0; i!=this->size();++i){
	_alloc.construct(newelems++,std::move(*_elems++));

*/
template <typename T>
void Vector<T>::reallocate(){
	//�����¿ռ��С
	int oldcapacity = capacity();
	int newcapacity = (oldcapacity == 0 ? 1 : oldcapacity * 2);
	
	//1.�����¿ռ�
	T * newelems = _alloc.allocate(newcapacity);
	if(_elems){
		//2.ԭʼ�ռ�  uninitialized_copy( InputIt first, InputIt last, ForwardIt d_first );
		std::uninitialized_copy(_elems,_firstFree,newelems);
		//3.����ԭ�ռ����
		while(_elems != _firstFree)
			_alloc.destroy( --_firstFree);
		//4.����ԭ�ռ�
		_alloc.deallocate(_elems,oldcapacity);
	}
	//5.����Ϊ�¿ռ�   ��if������
	_elems = newelems;
	_firstFree = newelems + oldcapacity;
	_end = newelems + newcapacity;
	
}

template <typename T>
void Vector<T>::clear(){
	while(_elems != _firstFree)
		_alloc.destroy(--_firstFree);
	_alloc.deallocate(_elems,capacity());
	cout<< "clear ok"<<endl;
}


template <typename T>
std::allocator<T> Vector<T>:: _alloc;    //static ���������ʼ��

void display(const Vector<int> & vec)
{
	cout << "vec's size = " << vec.size() << endl;
	cout << "vec's capa = " << vec.capacity() << endl;
}

void print(const Vector<int> & vec)
{
	for(int idx = 0; idx < vec.size(); ++idx)
	{
		cout << vec[idx] << " ";
	}
}

int main(void)
{
	Vector<int> vec;
	//*******************************size() capacity()����
	display(vec);
	vec.push_back(1);
	display(vec);
	vec.push_back(2);
	display(vec);
	vec.push_back(3);
	display(vec);
	vec.push_back(4);
	display(vec);
	vec.push_back(5);
	display(vec);
	vec.push_back(6);
	display(vec);
	vec.push_back(7);
	display(vec);
	cout << endl;
	print(vec);
	cout << endl;
	//
	return 0;
}

/*allocator ��ʵ���Զ���Vectorģ��

��Ϥ: 
ģ���� static std::allocator<T> alloc; ��Ҫ��̬����
static: allocate(n)��deallocate(p,n)  �ڴ�ķ�����ͷ�     

static: construct(p,args)��destroy(p)  ����������ɾ��

����: 
reallcote
1.�Զ����ڴ治��ʱ�����·������Ŀռ�
2.��ԭ�ռ�����ƶ�move ���¿ռ�(����copy) | ����ֱ��ʹ��uninitialized_copy
3.�ͷ�ԭ�ռ���Դ
*/


/*
    Vectorģ��
     ______________________________
    |_|_|_|_|_|____________________|
     ��         ��                    ��
   _elems   _first_free            _end
   
           
    T * _elems;      //ָ�������еĵ�һ��Ԫ��
    T * _first_free; //ָ�����һ��ʵ��Ԫ��֮����Ǹ�Ԫ��
    T * _end;        //ָ�����鱾��֮���λ��
*/
