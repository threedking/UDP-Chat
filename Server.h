//---------------------------------------------------------------------------
#ifndef ServerH
#define ServerH

#include "Models.h"
#include "SendingManager.h"
#include <thread>
//---------------------------------------------------------------------------
class Server{
private:
	Server();
	Server(const Server&)=delete;
	Server& operator=(Server&)= delete;

	SendingManager* SendingManagerInstance=NULL;
	bool IsOn;
	String Name="Server6106";

	Model<User> ModelUsers;
	Model<MessageSe> ModelMessages;

	void WorkOnRequest(String FromIP,String Data);

	unsigned short int Request_SendServerInfo(String& SendToIP);
	unsigned short int Request_AddUserToChat(User& newUser);
	unsigned short int Request_SendAllMessages(String& SendToIP);
	unsigned short int Request_SendXMessages(String& SendToIP,int X);
	unsigned short int Request_AddMessageToChat(MessageSe& newMessage);
	unsigned short int Request_SetUserOffline(User& newUser);

	unsigned short int SendMessagesToOne(String& SendToIP,std::multiset<MessageSe> &Data);
	unsigned short int SendMessageToAll(Message& newMessage);

public:
	static Server& getInstance() {
		static Server instance;
		return instance;
	}

	void SetIdUDPServer(TIdUDPServer* newIdUDPServer);
	bool TurnOn();
	void TurnOff();
	bool GetIsOn();
	void SetName(String newName);
	String GetName();
	void Request(String FromIP,String Data);
};
//---------------------------------------------------------------------------
#endif
