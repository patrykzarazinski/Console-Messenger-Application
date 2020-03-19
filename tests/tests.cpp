#include "socket.h"
#include <gtest/gtest.h>
#include<string>


//Positive tests


TEST(SocketInitialization_positive, positive_1) 
{ 
    Socket test(const_cast<char *>("127.0.0.1"), 5000);

    int n = 5000;
    std::string s = "127.0.0.1";

    EXPECT_EQ(ntohs(test.get_serwerAddress().sin_port), n); // ntohs(), because port is in network byte order
    EXPECT_STREQ(inet_ntoa(test.get_serwerAddress().sin_addr), s.c_str()); // inet_ntoa(), same as above network to ascii
}

TEST(SocketInitialization_positive, positive_2) 
{ 
    Socket test(const_cast<char *>("127.55.55.55"), 5555);

    int n = 5555;
    std::string s = "127.55.55.55";

    EXPECT_EQ(ntohs(test.get_serwerAddress().sin_port), n); // ntohs(), because port is in network byte order
    EXPECT_STREQ(inet_ntoa(test.get_serwerAddress().sin_addr), s.c_str()); // inet_ntoa(), same as above network to ascii
}


//Negative tests


TEST(SocketInitialization_negative, negative_1) // different port and IP
{ 
    Socket test(const_cast<char *>("127.0.0.1"), 5000);

    int n = 4000 ;
    std::string s = "127.100.100.100";

    EXPECT_EQ(ntohs(test.get_serwerAddress().sin_port), n); // ntohs(), because port is in network byte order
    EXPECT_STREQ(inet_ntoa(test.get_serwerAddress().sin_addr), s.c_str()); // inet_ntoa(), same as above network to ascii
}

TEST(SocketInitialization_negative, negative_2) // different port and IP
{ 
    Socket test(const_cast<char *>("127.0.0.1"), 5000);

    int n = 1000 ;
    std::string s = "120.0.0.1";

    EXPECT_EQ(ntohs(test.get_serwerAddress().sin_port), n); // ntohs(), because port is in network byte order
    EXPECT_STREQ(inet_ntoa(test.get_serwerAddress().sin_addr), s.c_str()); // inet_ntoa(), same as above network to ascii
}

TEST(SocketInitialization_negative, negative_3) // same port, different IP
{ 
    Socket test(const_cast<char *>("127.0.0.1"), 5000);

    int n = 5000 ;
    std::string s = "120.0.0.1";

    EXPECT_EQ(ntohs(test.get_serwerAddress().sin_port), n); // ntohs(), because port is in network byte order
    EXPECT_STREQ(inet_ntoa(test.get_serwerAddress().sin_addr), s.c_str()); // inet_ntoa(), same as above network to ascii
}

TEST(SocketInitialization_negative, negative_4) // same IP, different port
{ 
    Socket test(const_cast<char *>("127.0.0.1"), 5000);

    int n = 1000 ;
    std::string s = "127.0.0.1";

    EXPECT_EQ(ntohs(test.get_serwerAddress().sin_port), n); // ntohs(), because port is in network byte order
    EXPECT_STREQ(inet_ntoa(test.get_serwerAddress().sin_addr), s.c_str()); // inet_ntoa(), same as above network to ascii
}
