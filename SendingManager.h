//---------------------------------------------------------------------------

#ifndef SendingManagerH
#define SendingManagerH
#include <IdUDPServer.hpp>
#include <mutex>
//---------------------------------------------------------------------------
class SendingManager{
private:
	SendingManager(){}
	SendingManager(const SendingManager&)=delete;
	SendingManager& operator=(SendingManager&)= delete;

	TIdUDPServer* IdUDPServer=NULL;
	std::mutex Mutex;
public:
	static int g;
	static SendingManager& getInstance() {
		static SendingManager instance;
		return instance;
	}
	void SetIdUDPServer(TIdUDPServer* newIdUDPServer);
	unsigned short int Send(UnicodeString IPSendTo,UnicodeString Message);
	bool TurnOn();
	void TurnOff();
	bool GetActive();
};
//---------------------------------------------------------------------------
#endif
