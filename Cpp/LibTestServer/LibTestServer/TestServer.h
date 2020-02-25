//#pragma once
//
//#include "stdafx.h"
//
//class server
//{
//public:
//    server(boost::asio::io_service& io_service, short port)
//        : io_service_(io_service),
//        acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
//    {
//        RumdaLib::CSession* new_session = new RumdaLib::CSession(io_service_);
//        acceptor_.async_accept(new_session->socket(),
//            boost::bind(&server::handle_accept, this, new_session,
//                boost::asio::placeholders::error));
//    }
//
//    void handle_accept(RumdaLib::CSession* new_session,
//        const boost::system::error_code& error)
//    {
//        if (!error)
//        {
//            new_session->start();
//            new_session = new RumdaLib::CSession(io_service_);
//            acceptor_.async_accept(new_session->socket(),
//                boost::bind(&server::handle_accept, this, new_session,
//                    boost::asio::placeholders::error));
//        }
//        else
//        {
//            delete new_session;
//        }
//    }
//
//private:
//    boost::asio::io_service& io_service_;
//    boost::asio::ip::tcp::acceptor acceptor_;
//};