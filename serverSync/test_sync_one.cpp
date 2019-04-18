# if 0
#include "boost/asio.hpp"
#include "boost/asio/buffer.hpp"
#include <stdio.h>

using boost::asio::ip::tcp;


const char * serviceList = "\n\t Services\n"
"\t**********************\n"
"\t[1] Get current time.\n"
"Please pick a services[1]:";


std::string getServiceContent(int selection)
{
	std::string content;
	switch (selection)
	{
	case 1:
	{
		time_t t = time(NULL);
		content = ctime(&t);
		break;
	}
	default:
		content = "Sorry, No This selection!\n";
		break;
	}

	return content;
}

int main(int argc, char * argv[])
{

	//建立一个io_service
	boost::asio::io_service io_service;

	// 具体的服务器地址与端口
	boost::asio::ip::tcp::endpoint endpotion(boost::asio::ip::tcp::v4(), 8868);

	//建议个acceptor
	tcp::acceptor acceptor(io_service, endpotion);

	//打印一下本地的监听地址和端口
	printf("local accepter addr %s port %d\n", acceptor.local_endpoint().address().to_string().c_str(), acceptor.local_endpoint().port());

	for (;;)
	{
		//建议一个socket对象
		// 一个临时的socket对象
		tcp::socket socket(io_service);
		//阻塞的
		acceptor.accept(socket);
		
		printf("remote addr %s port:%d\n", socket.remote_endpoint().address().to_string().c_str(), socket.remote_endpoint().port());

		//接收到数据之后，发送自己的服务, ignored_error 不让服务器抛异常需要
		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(serviceList, strlen(serviceList)), boost::asio::transfer_all(), ignored_error);

		//2. 要从服务器收到要启用哪种服务
		char selection[20];
		size_t n = socket.read_some(boost::asio::buffer(selection), ignored_error);

		//发送服务
		std::string response = getServiceContent(atoi(selection));

		boost::asio::write(socket, boost::asio::buffer(response), boost::asio::transfer_all(), ignored_error);

	}

	return 0;
}
#endif
