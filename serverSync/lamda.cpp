#if 0
#include <stdio.h>

//[](){}
//[] ��׽���ز���  https://www.cnblogs.com/DswCnblog/p/5629165.html �� ����ʱ���ò�׽��ֵ��׽
//(), ����
//{} ������

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