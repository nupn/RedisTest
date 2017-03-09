#include <stdio.h>
#include <string>
#include "redispp.h"
#ifdef _WIN32
#include <Windows.h>
#endif

using namespace redispp;
using namespace std;

const char* TEST_PORT = "7000";
const char* TEST_HOST = "13.124.3.11";
const char* TEST_UNIX_DOMAIN_SOCKET = "/tmp/redis.sock";

int main(int argc, char* argv[])
{
#ifdef _WIN32
	WSADATA wsaData;
	WORD version;
	version = MAKEWORD(2, 0);
	WSAStartup(version, &wsaData);
#endif

#ifdef UNIX_DOMAIN_SOCKET
	Connection conn(TEST_UNIX_DOMAIN_SOCKET, "");
#else
	Connection conn(TEST_HOST, TEST_PORT, "dudah2");
#endif

	conn.set("hello", "world");
	StringReply stringReply = conn.get("hello");
	stringReply.result().is_initialized();
	printf("%s", ((std::string)conn.get("hello")).c_str());
	
	//BOOST_CHECK((bool)conn.exists("hello"));
	//BOOST_CHECK((bool)conn.del("hello"));
	//BOOST_CHECK(!conn.exists("hello"));
	//BOOST_CHECK(!conn.del("hello"));
	return 0;
}
