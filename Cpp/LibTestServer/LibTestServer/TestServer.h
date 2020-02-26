#pragma once

#include "stdafx.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

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


class server
{
public:
    server(boost::asio::io_service& io_service, short port)
        : io_service_(io_service),
        acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        CSession* new_session = new CSession(io_service_);
        acceptor_.async_accept(new_session->socket(),
            boost::bind(&server::handle_accept, this, new_session,
                boost::asio::placeholders::error));
    }

    void handle_accept(CSession* new_session,
        const boost::system::error_code& error)
    {
        if (!error)
        {
            new_session->start();
            new_session = new CSession(io_service_);
            acceptor_.async_accept(new_session->socket(),
                boost::bind(&server::handle_accept, this, new_session,
                    boost::asio::placeholders::error));
        }
        else
        {
            delete new_session;
        }
    }

private:
    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};