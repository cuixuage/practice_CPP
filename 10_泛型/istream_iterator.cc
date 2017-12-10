
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;
using std::copy;


int main(void)
{
	vector<int> numbers;
	numbers.reserve(100);

	istream_iterator<int> isi(cin);

	//begin()  end()  读取元素，修改元素
	//copy(isi, istream_iterator<int>(), numbers.begin());//vector没有空间，所以会出错
	//push_back(); //size()或capacity() 产生影响 
	
	copy(isi, istream_iterator<int>(), std::back_inserter(numbers));

	//c++11 
	for(auto & elem : numbers)
	{
		cout << elem << " ";
	}
	cout << endl;

#if 0
	ostream_iterator<int> osi(cout, "\n");

	copy(numbers.begin(), numbers.end(), osi);
#endif
	
	return 0;
}
