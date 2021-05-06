#include <string>
#include <thread>
#include <Poco/Net/DNS.h>
#include "RoomManager.h"
#include "ToLobbyPacketHandler.h"
#include "LobbyServer.h"

int main()
{
	network::LobbyServer svr(20000);
	svr.Initialize();
	svr.Run();

// 	game::RoomManager roomManager(30000, 40000);
// 	auto room1 = roomManager.Create(1);
// 	std::thread th1([&room1]() { room1->Run(); });
// 
// 	auto room2 = roomManager.Create(1);
// 	std::thread th2([&room2]() { room2->Run(); });
// 
// 	th1.join();
// 	th2.join();
}
