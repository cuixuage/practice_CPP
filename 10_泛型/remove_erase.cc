#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
using std::cout;
using std::endl;
using std::replace;
using std::vector;
using std::string;
using std::ostream_iterator;

int test0(void)
{
	vector<int> numbers{1, 2, 3, 4, 5, 6};

	std::less<int> lt; 
	//lt(lhs, rhs);

	replace_if(numbers.begin(), numbers.end(), std::bind2nd(lt, 3), 7);    // 比3大的数值均替换为7

	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));

	return 0;
}

//remove-erase惯用法
//在遍历容器的过程中，不建议做删除或添加元素的操作，
//因为有可能导致迭代器失效
int test1(void)
{
	vector<int> numbers{0,1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	numbers[3] = numbers[5] = numbers[10] = 99;
#if 0
	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	numbers.erase(std::remove(numbers.begin(), numbers.end(), 99), numbers.end());
	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
#endif

	auto it = std::remove(numbers.begin(), numbers.end(), 99);
	//std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	numbers.erase(it, numbers.end());
	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));

	
	return 0;
}


void test2()
{
	vector<string> vec;

	vec.push_back("this is A");

	bool flag = true;
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
		cout << "vec's capacity = " << vec.capacity() << endl;
		cout << *it << endl;//第二次获取元素时，该迭代器已失效
		if(flag)
		{
			vec.push_back("this is B");//在这里发生了扩容
			flag = false;
		}
	}
	
}

int main(void)
{
	test1();
	//test2();
	return 0;
}

/*
标准库函数  remove First version***************
template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
    first = std::find(first, last, value);
    if (first != last)
        for(ForwardIt i = first; ++i != last; )
            if (!(*i == value))
                *first++ = std::move(*i);
    return first;
}
*/

/***************************example    remove  remove_if
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
 
int main()
{
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '),
               str1.end());
    std::cout << str1 << '\n';
 
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), 
                              str2.end(),
                              [](char x){return std::isspace(x);}),			//remove_if 第三个参数是函数
               str2.end());
    std::cout << str2 << '\n';
}

Output:
Textwithsomespaces
Textwithsomewhitespaces
*/