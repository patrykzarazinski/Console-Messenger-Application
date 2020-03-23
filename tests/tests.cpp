#include "socket.h"
#include <iostream>
#include <gtest/gtest.h>
#include <string>

Socket serwer(const_cast<char *>("127.0.0.1"), 5000, 1);

class socketTest : public testing::Test
{
	public:

	Socket client;

	socketTest():client(const_cast<char *>("127.0.0.1"), 5000, 2){}
	void SetUp()
	{	
		std::cout << "Before test" << std::endl;
		client >> "Some data";
	}
	void TearDown()
	{
		std::cout << "After test" << std::endl;
	}
	~socketTest(){}
};


TEST_F(socketTest, dataReceive_1) 
{ 
	std::string s;
	ASSERT_EQ(1, serwer.receive(s, serwer.s_accept()));
}

TEST_F(socketTest, dataReceive_2) 
{ 
	std::string s;
	ASSERT_EQ(1, serwer.receive(s, serwer.s_accept()));
}

TEST_F(socketTest, dataReceive_3) 
{ 
	std::string s;
	int user = serwer.s_accept();

	ASSERT_EQ(1, serwer.receive(s, user));
	std:: cout << s << std::endl;
	send(user, s.c_str(), s.size() + 1, 0);
	ASSERT_EQ(1, client.receive(s));
	std:: cout << s << std::endl;
}

TEST_F(socketTest, dataReceive_4) 
{ 
	std::string s;
	std::string to_Client = "test";
	int user = serwer.s_accept();

	ASSERT_EQ(1, serwer.receive(s, user));
	std:: cout << s << std::endl;
	send(user, s.c_str(), s.size() + 1, 0);
	std::cout << to_Client << std::endl;
	ASSERT_EQ(1, client.receive(to_Client));
	std:: cout << to_Client << std::endl;
}