#include <iostream>  
#include <fstream>  
#include <string>  
#include <map> 
#define inputfilename "./The_Holy_Bible.txt"
#define outputfilename "./output_file.txt"
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;
//统计 the holy bible文件的词频
// map key value保存,并对于空格符分离的字符串进行 去除标点、转为小写、去除数字等等操作

class WordStatistic
{
public:
	void readFile(const std::string filename);
	void writeFile(const std::string filename);
private:
	map<string,int> my_map;
	void erasePunct(string &s);             //去除标点
	void stringToLower(string &s);          //转为小写
	bool isAllDigit(const std::string &s);  //去除数字
	
};
void WordStatistic::erasePunct(string &s)
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
void WordStatistic::stringToLower(string &s)
{
    for(string::iterator it = s.begin();
        it != s.end();
        ++it)
    {
        if(isupper(*it))
            *it = tolower(*it);
    }
}
bool WordStatistic::isAllDigit(const std::string &s)
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
void WordStatistic::readFile(const std::string filename){
    ifstream ifs(filename.c_str());               
    string  temp; 
	while(ifs>>temp){
		erasePunct(temp);         //去除标点
		stringToLower(temp);      //转为小写
		if(isAllDigit(temp))      //去除数字
			continue;
		my_map[temp]++;
	}
	cout<<"read ok"<<endl;
}
void WordStatistic::writeFile(const std::string filename){
	ofstream ofs(filename.c_str());
	string line;
	map<string, int>::const_iterator map_it;     
    for (map_it=my_map.begin(); map_it!=my_map.end();map_it++)     
    {     
        ofs<< map_it->first << "  " << map_it->second <<endl;     
    } 
	ofs.close();
	cout << "write ok" << endl;
}	
int main(int ac,char** av){
	WordStatistic wd;
	wd.readFile(inputfilename);
	wd.writeFile(outputfilename);
	return 0;
}
		