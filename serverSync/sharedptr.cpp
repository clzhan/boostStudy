#if 0
#include <stdio.h>
#include <memory>
#include <string>
#include <iostream>
class Parent
{
public:
	Parent()
	{
		printf("%s \n", __FUNCTION__);
	}
	~Parent()
	{
		printf("%s \n", __FUNCTION__);
	}
};



/*
shared_ptr允许多个该智能指针共享第“拥有”同一堆分配对象的内存，
这通过引用计数（reference counting）实现，会记录有多少个shared_ptr共同指向一个对象，
一旦最后一个这样的指针被销毁，也就是一旦某个对象的引用计数变为0，这个对象会被自动删除
*/
int  main(int argc, char * argv[])
{
	//可以指定lamda释放
	std::shared_ptr<Parent> p(new Parent(), 
		[](Parent* p){
		printf("%s \n", __FUNCTION__);
		delete p; 
	}
	);
	std::shared_ptr<Parent> p_test(new Parent());

	//

	std::shared_ptr<Parent> p2 = p;
	std::cout << "p2 cout: " << p2.use_count() << std::endl; // 打印引用计数
	std::cout << "p cout: " << p.use_count() << std::endl; // 打印引用计数

	p.reset(); // 显示让引用计数减一
	std::cout << "count: " << p2.use_count() << std::endl; // 打印引用计数




	return 0;
}
#endif