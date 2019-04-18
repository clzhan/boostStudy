#if 0
#include <stdio.h>

//[](){}
//[] 捕捉本地参数  https://www.cnblogs.com/DswCnblog/p/5629165.html ， 可以时引用捕捉和值捕捉
//(), 参数
//{} 函数体

int main(int argc, char * argv[])
{
	int a = 0; 
	int b = 1; 
	int c = 2;
	auto lamda = [](int &a, int &b, int &c){
		printf("%s \n", __FUNCTION__);
		printf("a:%d, b:%d, c:%d\n", a, b, c);
	};
	lamda(a, b, c);

	return 0;
}
#endif