# if  1
#include "boost/asio.hpp"
#include "boost/asio/buffer.hpp"
#include <stdio.h>
#include <memory>

using boost::asio::ip::tcp;


const char * serviceList = "\n\t Services\n"
"\t**********************\n"
"\t[1] Get current time.\n"
"Please pick a services[1]:";


std::string getServiceContent(int selection)
{
	printf("selection :%d \n", selection);
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

	//����һ��io_service
	boost::asio::io_service io_service;

	// ����ķ�������ַ��˿�
	boost::asio::ip::tcp::endpoint endpotion(boost::asio::ip::tcp::v4(), 8868);

	//�����acceptor
	tcp::acceptor acceptor(io_service, endpotion);

	//��ӡһ�±��صļ�����ַ�Ͷ˿�
	printf("local accepter addr %s port %d\n", acceptor.local_endpoint().address().to_string().c_str(), acceptor.local_endpoint().port());

	using SocketPtr = std::shared_ptr<tcp::socket>;

	for (;;)
	{
		//����һ��socket����
		// һ����ʱ��socket����
		//SocketPtr socket(new tcp::socket(io_service), 
		//		[](SocketPtr socket)
		//	{
		//		printf("close.....socket......%s\n", __FUNCTION__);
		//		//socket->close();
		//		//delete socket;
		//	}
		//);
		SocketPtr socket(new tcp::socket(io_service));
		//tcp::socket socket(io_service);
		//������
		acceptor.accept(*socket);

		std::thread t(
			[socket]() //��׽��������ָ�����ü�����+1
			{
				printf("remote addr %s port:%d\n", socket->remote_endpoint().address().to_string().c_str(), socket->remote_endpoint().port());
				boost::system::error_code ignored_error;
				boost::asio::write(*socket, boost::asio::buffer(serviceList, strlen(serviceList)), boost::asio::transfer_all(), ignored_error);

				//2. Ҫ�ӷ������յ�Ҫ�������ַ���
				char selection[20];
				size_t n = socket->read_some(boost::asio::buffer(selection), ignored_error);

				//���ͷ���
				std::string response = getServiceContent(atoi(selection));

				boost::asio::write(*socket, boost::asio::buffer(response), boost::asio::transfer_all(), ignored_error);
			}
		);

		t.detach();

		printf("socket use %d\n", socket.use_count());

		//���յ�����֮�󣬷����Լ��ķ���
	
	}

	return 0;
}

#endif