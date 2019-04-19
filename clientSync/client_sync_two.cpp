
#include <stdio.h>

#include "boost/asio.hpp"

#include <iostream>

//����Ҫģ��telenet �Ĺ��ܣ� ѡ���ȡ�ر�
/*
ֱ�׵�˵�����Ƕ�getaddrinfo()������������䡣�����˵���ǽ�������

ϸ�����£�
boost::asio::ip::tcp::resolver resolver(asioService);
boost::asio::ip::tcp::resolver::query queryEndpoints(boost::asio::ip::host_name(),"80");
boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(queryEndpoints);
;
for(boost::asio::ip::tcp::resolver::iterator iterNull;
endpoint_iterator != iterNull;
endpoint_iterator++)
{
std::cout << endpoint_iterator->endpoint() << std::endl;
}

����Ĵ�������ô�������ͣ�

boost::asio::ip::tcp::resolver

boost::asio::ip::tcp::resolver::query

boost::asio::ip::tcp::resolver::iterator

resolver���ߵ���getaddrinfo()����

boost::asio::ip::tcp::resolver::query�������getaddrinfo()��Ҫ�Ĳ���

boost::asio::ip::tcp::resolver::iterator�������getaddrinfo()�Ľ��

��������ϵ�ǳ���winsock sdk��stl˼��
*/

using boost::asio::ip::tcp;

int main(int argc, char * argv[])
{

	//1.����һ��IOservice
	boost::asio::io_service io_service;
	boost::asio::ip::address addr;
	addr.from_string("10.10.6.91");

	//2.����һ��endpoint
	//boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("10.10.6.91"), 8868);//����Ŀ���ַ����
	boost::asio::ip::tcp::endpoint ep(addr, 8868);//����Ŀ���ַ����

	////2. ����һ��resolver
	//tcp::resolver resolver(io_service);

	////����һ����ѯ�˿ڶ���
	//tcp::resolver::query query("10.10.6.91", "8868");

	////4. ��resolver����Ͳ�ѯ��ȡ���õķ�������ַ
	//tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	//tcp::resolver::iterator end;

	//����һ��socket����

	tcp::socket socket(io_service);


	//����connect������
	boost::system::error_code error = boost::asio::error::host_not_found;

	socket.connect(ep, error);

	/*while (error && endpoint_iterator != end)
	{
	socket.close();
	socket.connect(*endpoint_iterator++, error);
	}*/

	if (error) //���һ��Ҳû�����ӳɹ������׳��쳣
	{
		printf("Connect  host addr error \n");
		exit;
	}

	char buf[512];
	//receive service list from server
	size_t len = socket.read_some(boost::asio::buffer(buf), error);

	buf[len] = '\0';

	std::cout << buf;

	std::string selection;

	std::cin >> selection;

	//send selection to server
	boost::asio::write(socket, boost::asio::buffer(selection),boost::asio::transfer_all(), error);

	//recive
	len = socket.read_some(boost::asio::buffer(buf), error);
	buf[len] = '\0';

	std::cout << buf;

	return 0;
}