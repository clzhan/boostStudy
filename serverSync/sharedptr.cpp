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
shared_ptr������������ָ�빲��ڡ�ӵ�С�ͬһ�ѷ��������ڴ棬
��ͨ�����ü�����reference counting��ʵ�֣����¼�ж��ٸ�shared_ptr��ָͬ��һ������
һ�����һ��������ָ�뱻���٣�Ҳ����һ��ĳ����������ü�����Ϊ0���������ᱻ�Զ�ɾ��
*/
int  main(int argc, char * argv[])
{
	//����ָ��lamda�ͷ�
	std::shared_ptr<Parent> p(new Parent(), 
		[](Parent* p){
		printf("%s \n", __FUNCTION__);
		delete p; 
	}
	);
	std::shared_ptr<Parent> p_test(new Parent());

	//

	std::shared_ptr<Parent> p2 = p;
	std::cout << "p2 cout: " << p2.use_count() << std::endl; // ��ӡ���ü���
	std::cout << "p cout: " << p.use_count() << std::endl; // ��ӡ���ü���

	p.reset(); // ��ʾ�����ü�����һ
	std::cout << "count: " << p2.use_count() << std::endl; // ��ӡ���ü���




	return 0;
}
#endif