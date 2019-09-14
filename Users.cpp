//---------------------------------------------------------------------------

#pragma hdrstop

#include "Users.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
User::User(std::string newIP, std::string newName){
this->SetIP(newIP);
this->SetName(newName);
}
//---------------------------------------------------------------------------
void User::SetIP(std::string newIP){
if(newIP.size() > 0){
	this->IP=newIP;
}
}
//---------------------------------------------------------------------------
void User::SetName(std::string newName){
if(newName.size() > 0){//TODO еще ограничения
	this->Name=newName;
}
}
//---------------------------------------------------------------------------
void User::SetIsOnline(bool newIsOnline){
this->IsOnline=newIsOnline;
}
//---------------------------------------------------------------------------
std::string User::GetIP()const{
return this->IP;
}
//---------------------------------------------------------------------------
std::string User::GetName()const{
return this->Name;
}
//---------------------------------------------------------------------------
bool User::GetIsOnline()const{
return this->IsOnline;
}
//---------------------------------------------------------------------------
bool User::operator<(const User& Other)const{
return this->Name < Other.Name;
}
//---------------------------------------------------------------------------
bool User::operator==(const User& Other)const{
return (this->Name == Other.Name) && (this->IP == Other.IP);
}
//---------------------------------------------------------------------------
