#include <iostream>
#include <Poco/Net/DNS.h>
#include <Poco/Net/IPAddress.h>
#include <Poco/Net/NetException.h>
#include <Poco/Logger.h>
#include <string>

int main()
{
    std::cout << Poco::Net::DNS::hostName() << std::endl;
}
