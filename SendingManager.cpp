//---------------------------------------------------------------------------

#pragma hdrstop

#include "SendingManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void SendingManager::SetIdUDPServer(TIdUDPServer* newIdUDPServer){
std::lock_guard<std::mutex> lock(this->Mutex);
this->IdUDPServer=newIdUDPServer;
this->IdUDPServer->Active=false;
this->IdUDPServer->DefaultPort=6106;
this->IdUDPServer->Bindings->Clear();
}
//---------------------------------------------------------------------------
unsigned short int SendingManager::Send(UnicodeString IPSendTo,UnicodeString Message){
std::lock_guard<std::mutex> lock(this->Mutex);
if(this->IdUDPServer->Active){
	try {
		this->IdUDPServer->Send(IPSendTo,this->IdUDPServer->DefaultPort,Message);
	} catch (...) {
		return 2;//код ошибка сети
	}
}else{
	return 1;//код сервер не запущен
}
return 0;//код Ок
}
//---------------------------------------------------------------------------
bool SendingManager::TurnOn(){
std::lock_guard<std::mutex> lock(this->Mutex);
if(this->IdUDPServer!=NULL){
	if(!this->IdUDPServer->Active){
		try {
			this->IdUDPServer->Active=true;
		} catch (...) {
			return 0;
		}
	}
	return this->IdUDPServer->Active;
}else{
    return 0;
}
}
//---------------------------------------------------------------------------
void SendingManager::TurnOff(){
std::lock_guard<std::mutex> lock(this->Mutex);
this->IdUDPServer->Active=false;
}
//---------------------------------------------------------------------------
bool SendingManager::GetActive(){
std::lock_guard<std::mutex> lock(this->Mutex);
return this->IdUDPServer->Active;
}
//---------------------------------------------------------------------------
