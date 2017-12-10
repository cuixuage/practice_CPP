 ///
 /// @file    ostream_iterator.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-08-02 11:07:08
 ///
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::ostream_iterator;


int main(void)
{
	//cout << "sizeof(cout) = " << sizeof(cout) << endl;

	ostream_iterator<int> osi(cout, " ");

	vector<int> numbers{1, 2, 3, 4, 5, 6};

#if 0
	for(auto it = numbers.begin(); it != numbers.end(); ++it)
	{
		cout << *it << " ";
	}
#endif

	copy(numbers.begin(), numbers.end(), osi);
	cout << endl;
	return 0;
}
