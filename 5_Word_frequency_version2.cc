//**********************************************版本二  支持单词查询********
/*查询的结果是该单词出现的次数，并列出每次出现所在的行。
如果某单词在同一行中多次出现，程序将只显示该行一次。行号按升序显示。	
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::set;
using std::vector;
using std::ifstream;
using std::stringstream;
#define inputfilename "./The_Holy_Bible.txt"
class TextQuery
{
public:
	TextQuery(){};
	~TextQuery(){};
    void readFile(const string );
    void query(const string &);
private:
    vector<string> _lines;               //按顺序保存每一行内容
    map<string, set<int> > _word2Line;   //保存单词、出现行号
    map<string, int> _wordFreq;          //保存单词出现总次数
	
	void erasePunct(string &s);             //去除标点
	void stringToLower(string &s);          //转为小写
	bool isAllDigit(const string &s);  		//去除数字
};
 void TextQuery::erasePunct(string &s)
{
    string::iterator it = s.begin();
    while(it != s.end())
    {
        if(ispunct(*it))
            it = s.erase(it);
        else
            ++it;
    }
}
void TextQuery::stringToLower(string &s)
{
    for(string::iterator it = s.begin();
        it != s.end();
        ++it)
    {
        if(isupper(*it))
            *it = tolower(*it);
    }
}
bool TextQuery::isAllDigit(const std::string &s)
{
    for(string::const_iterator it = s.begin();
        it != s.end();
        ++it)
    {
        if(!isdigit(*it))
            return false;
    }

    return true;
}
void TextQuery::readFile(const string filename){
	ifstream ifs(filename.c_str());
	string temp;
	stringstream ss;
	while(getline(ifs,temp)){
		_lines.push_back(temp);
	}
	cout<< "readfile ok" <<endl; 
	int count=0;
	for(auto & strline : _lines){
		ss << strline;
		while(ss >> temp){
			erasePunct(temp);         //去除标点
			stringToLower(temp);      //转为小写
			if(isAllDigit(temp))      //去除数字
			continue;	
			_word2Line[temp].insert(count);
			_wordFreq[temp]++;
		}
		count++;	
		ss.clear();     //需要清空 否则每次"\n"仍然处于ss当中??????
	}
}
 
void TextQuery::query(const string & word){
	cout<< "total " << _wordFreq[word] << endl;
	for(auto & i : _word2Line[word]){
		cout<< i << " ";
		cout<<_lines[i]<<endl;
	}
	cout<<endl;
}
 
int main(int ac,char** av){
	 string filename = inputfilename;
	 TextQuery textquery;
	 textquery.readFile(filename);
	 // textquery.query("genesis"); 
	 textquery.query("10");
	 return 0;
 }