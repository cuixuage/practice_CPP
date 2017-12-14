**模版**  

**容器**  
序列式: vector list deque
关联式: set multiset map multimap  

**迭代器**  
迭代器适配器: insertor iostream  

**某些泛型**
for_each find erase+remove sort+unique+erase 
例如:   str1.erase(std::remove(str1.begin(), str1.end(), ' '),  
               str1.end());      

**函数适配器**  
bind    
得到一个新的可调用对象  
注：  
占位符; 实际调用对象默认是值传递，拷贝对象。如果需要地址传递，需要ref或者cref函数  