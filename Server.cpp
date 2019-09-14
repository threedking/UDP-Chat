//---------------------------------------------------------------------------

#pragma hdrstop

#include "Server.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Server::Server(){
this->SendingManagerInstance=&SendingManager::getInstance();
}
//---------------------------------------------------------------------------
void Server::SetIdUDPServer(TIdUDPServer* newIdUDPServer){
this->SendingManagerInstance->SetIdUDPServer(newIdUDPServer);
}
//---------------------------------------------------------------------------
bool Server::TurnOn(){
this->IsOn=this->SendingManagerInstance->TurnOn();
return this->IsOn;
}
//---------------------------------------------------------------------------
void Server::TurnOff(){
//TODO разослать всем уведомление
this->SendingManagerInstance->TurnOff();
this->IsOn=false;
this->ModelUsers.DeleteAllData();
this->ModelMessages.DeleteAllData();
}
//---------------------------------------------------------------------------
bool Server::GetIsOn(){
return this->IsOn;
}
//---------------------------------------------------------------------------
void Server::SetName(String newName){
if(newName.Length()>0 && newName.Length()<15){
	this->Name=newName;
}
}
//---------------------------------------------------------------------------
String Server::GetName(){
return this->Name;
}
//---------------------------------------------------------------------------
void Server::Request(String FromIP,String Data){
std::thread NewThread(this->WorkOnRequest,FromIP,Data);
NewThread.detach();
}
//---------------------------------------------------------------------------
void Server::WorkOnRequest(String FromIP,String Data){
int RequestN=0,Result=0;
std::size_t pos;
User Sender;

std::string Mess=AnsiString(Data).c_str();

if(Data.Length()<1){
	return;
}
pos=Mess.find("@cl!");
if(pos!=std::string::npos){
	pos+=4;
	RequestN=StrToInt(Mess[pos+2]);
}

switch (RequestN) {
case 1:
	Result=this->Request_SendServerInfo(FromIP);
break;
case 2:
	pos=Mess.find("2N=");
	if(pos!=std::string::npos){
		pos+=3;
		User Sender(AnsiString(FromIP).c_str(),Mess.substr(pos));
		Result=this->Request_AddUserToChat(Sender);
	}
break;
case 3:
	Result=this->Request_SendAllMessages(FromIP);
break;
case 4:
	pos=Mess.find("4X=");
	if(pos!=std::string::npos){
		pos+=3;
		int X=StrToInt(Mess.substr(pos).c_str());
		Result=this->Request_SendXMessages(FromIP,X);
	}
break;
case 5:{
	std::multiset<User> fset(this->ModelUsers.GetAllData());
	for(auto &it : fset){
		if(it.GetIP() == AnsiString(FromIP).c_str()){
			if(it.GetIsOnline()){
			Sender=it;
			break;
			}
		}
	}

	pos=Mess.find("5M=");
	if(pos!=std::string::npos){
		pos+=3;
	}
	MessageSe Message(Mess.substr(pos),&Sender);
	Result=this->Request_AddMessageToChat(Message);
}
break;
case 6:{
	std::multiset<User> fset2(this->ModelUsers.GetAllData());
	for(auto &it : fset2){
		if(it.GetIP() == AnsiString(FromIP).c_str()){
			if(it.GetIsOnline()){
			Sender=it;
			}
		}
	}
	Result=this->Request_SetUserOffline(Sender);
}
break;
default:
break;
}
}
//---------------------------------------------------------------------------
unsigned short int Server::Request_SendServerInfo(String& SendToIP){
return this->SendingManagerInstance->Send(SendToIP,"@se!1N="+this->Name);
}
//---------------------------------------------------------------------------
unsigned short int Server::Request_AddUserToChat(User& newUser){
this->ModelUsers.AddData(newUser);
return this->SendingManagerInstance->Send((newUser.GetIP()).c_str(),"@se!2");
}
//---------------------------------------------------------------------------
unsigned short int Server::Request_SendAllMessages(String& SendToIP){
std::multiset<MessageSe> Data=this->ModelMessages.GetAllData();
bool err=0;
for(auto &it : Data){
	err=this->SendingManagerInstance->Send(SendToIP,String("@se!3M=")+(it.GetText()).c_str());
	if(err!=0){
		return err;
	}
}
return 0;
}
//---------------------------------------------------------------------------
unsigned short int Server::Request_SendXMessages(String& SendToIP,int X){
std::multiset<MessageSe> Data=this->ModelMessages.GetFewOfLastData(X);
bool err=0;
for(auto &it : Data){
	err=this->SendingManagerInstance->Send(SendToIP,String("@se!3M=")+(it.GetText()).c_str());
	if(err!=0){
		return err;
	}
}
return 0;
}
//---------------------------------------------------------------------------
unsigned short int Server::Request_AddMessageToChat(MessageSe& newMessage){
this->ModelMessages.AddData(newMessage);
return 0;
}
//---------------------------------------------------------------------------
unsigned short int Server::Request_SetUserOffline(User& newUser){
this->ModelUsers.DeleteOne(newUser);
newUser.SetIsOnline(false);
this->ModelUsers.AddData(newUser);
return 0;
}
//---------------------------------------------------------------------------
/*
	-Получение запроса имени серва
	-Получение запроса на добавление пользователя(добавление в бд)
	-Получение запроса на отправку всех сообщений
	-Получение запроса на отправку последних X сообщений
	-Получение нового сообщения(добавление в модель)
	-Получение уведомления о выходе из чата(пометить пользователя неактивным в моделе)

	@cl!1
	@cl!2N=
	@cl!3
	@cl!4X=
	@cl!5M=
	@cl!6

	-Отправка имени конкретному пользователю
	-Отправка подтверждения об успешном добавлении(в любом случае. банов нет) конкретному пользователю
	-Отправка сообщения пользователю


	@se!1
	@se!2
	@se!3M=
*/
