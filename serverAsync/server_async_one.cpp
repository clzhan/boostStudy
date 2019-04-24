
#include <stdio.h>

#include "boost/asio.hpp"

#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

class Connection: public std::enable_shared_from_this<Connection>
{
public:
    Connection(boost::asio::io_service & service)
        : socket(service)
    {
    }
	~Connection()
	{
		printf("%s \n", __FUNCTION__);
	}
	void do_read()
    {
        auto self(shared_from_this());
		memset(buf, 0, 512);                                                //注意 重置buf
        socket.async_read_some(boost::asio::buffer(buf),
			[this, self](boost::system::error_code error, std::size_t length)
		{
			if (!error)
			{
				//再原封不动写回去	
					this->do_write();
			}
		} );
    }
	void do_write()
	{
		auto self(shared_from_this());
		boost::asio::async_write(socket, boost::asio::buffer(buf),
			[this, self](boost::system::error_code  error, std::size_t length)
		{
			if (!error)
			{
				this->do_read();
			}
		});
	}
	tcp::socket & getSocket()
	{
		return socket;
	}
private:
    tcp::socket socket;
    char buf[512];
};


using ConnectionPtr = std::shared_ptr<Connection>;

class Server
{
public:
    Server(boost::asio::io_service &  service) :
        acceptor(service, tcp::endpoint(tcp::v4(), 8868))
    {
		Start();
    }

private:
    void Start()
    {
		ConnectionPtr conn(new Connection(acceptor.get_io_service()));
		acceptor.async_accept(conn->getSocket(), [this, conn](boost::system::error_code  error){
			if (!error)
			{
				tcp::socket & socket = conn->getSocket();
				printf("remote addr %s  %d\n", socket.remote_endpoint().address().to_string().c_str(), socket.remote_endpoint().port());
				conn->do_read();
				this->Start();
			}
		});
    }

private:
    tcp::acceptor acceptor;
};

int main(int argc, char * argv[])
{
    //1.创建一个IOservice
    boost::asio::io_service io_service;
   // boost::asio::ip::address addr;
   // addr.from_string("10.10.6.91");
    //2.构建一个endpoint
    //boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("10.10.6.91"), 8868);//创建目标地址对象
    //boost::asio::ip::tcp::endpoint ep(addr, 8868);//创建目标地址对象

	Server server(io_service);
	io_service.run(); //与同步I/O 不同， 异步I/O要调用run


    return 0;
}