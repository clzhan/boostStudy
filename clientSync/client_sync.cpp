
#include <stdio.h>

#include "boost/asio.hpp"

#include <iostream>

//这里要模仿telenet 的功能， 选择读取关闭

using boost::asio::ip::tcp;

int main(int argc, char * argv[])
{

	//1.创建一个IOservice
	boost::asio::io_service io_service;

	//2. 创建一个resolver
	tcp::resolver resolver(io_service);

	//创建一个查询端口对象
	tcp::resolver::query query("10.10.6.91", "8868");

	//4. 用resolver对象和查询获取可用的服务器地址
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::resolver::iterator end;

	//创建一个socket对象

	tcp::socket socket(io_service);


	//连接connect服务器
	boost::system::error_code error = boost::asio::error::host_not_found;

	while (error && endpoint_iterator != end)
	{
		socket.close();
		socket.connect(*endpoint_iterator++, error);
	}

	if (error) //如果一个也没有连接成功，则抛出异常
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