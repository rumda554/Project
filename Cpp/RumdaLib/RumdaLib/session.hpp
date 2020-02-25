#pragma once

namespace RumdaLib
{
	class CSession
	{
	public:
		CSession(boost::asio::io_service& io_service)
			: socket_(io_service)
		{
		}

		boost::asio::ip::tcp::socket& socket()
		{
			return socket_;
		}

		void start()
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&CSession::read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}

		void read(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				boost::asio::async_write(socket_,
					boost::asio::buffer(data_, bytes_transferred),
					boost::bind(&CSession::write, this,
						boost::asio::placeholders::error));
			}
			else
			{
				delete this;
			}
		}

		void write(const boost::system::error_code& error)
		{
			if (!error)
			{
				socket_.async_read_some(boost::asio::buffer(data_, max_length),
					boost::bind(&CSession::read, this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				delete this;
			}
		}

	private:
		boost::asio::ip::tcp::socket socket_;
		enum { max_length = 1024 };
		char data_[max_length];
	};
}



// https://www.boost.org/doc/libs/1_63_0/doc/html/boost_asio/example/cpp11/allocation/server.cpp
// https://www.boost.org/doc/libs/1_63_0/doc/html/boost_asio/example/cpp11/chat/chat_server.cpp

// https://www.boost.org/doc/libs/1_36_0/doc/html/boost_asio/example/echo/async_tcp_echo_server.cpp