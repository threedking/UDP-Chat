//---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH

#include "Models.h"
#include "SendingManager.h"
//---------------------------------------------------------------------------
class Client{
private:
	Client();
	Client(const Client&)=delete;
	Client& operator=(Client&)= delete;

	SendingManager* SendingManagerInstance=NULL;
	bool IsOnline;
	String Name="Client6106";
	Model<MessageCl> ModelMessages;

public:
	static Client& getInstance() {
		static Client instance;
		return instance;
	}
	void SetIdUDPServer(TIdUDPServer* newIdUDPServer);
};
//---------------------------------------------------------------------------
#endif
