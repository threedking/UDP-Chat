//---------------------------------------------------------------------------
#pragma hdrstop

#include "Messages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Message::Message(std::string newText){
//this->Time=std::chrono::high_resolution_clock::now();
this->Time= std::time(NULL);
this->SetText(newText);
}
//---------------------------------------------------------------------------
void Message::SetText(std::string newText){
if(newText.size() > 0){
	newText.erase(std::remove_if(newText.begin(), newText.end(), Message::CheckSingleLetter), newText.end());
	if(newText.size() > 0){
		this->Text=newText;
	}
}
}
//---------------------------------------------------------------------------
std::string Message::GetText()const{
return this->Text;
}
//---------------------------------------------------------------------------
std::time_t Message::GetTime()const{
return this->Time;
}
//---------------------------------------------------------------------------
int Message::GetID()const{
return this->ID;
}
//---------------------------------------------------------------------------
bool Message::CheckSingleLetter(unsigned short Key){
return !( (Key >= 32) && (Key <=126) );
}
//---------------------------------------------------------------------------
bool Message::operator<(const Message& Other)const{
if(this->Time == Other.Time){
    return this->ID < Other.ID;
}
return this->Time < Other.Time;
}
//---------------------------------------------------------------------------
bool Message::operator==(const Message& Other)const{
return (this->Time == Other.Time) && (this->Text == Other.Text) && (this->ID == Other.ID);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
MessageSe::MessageSe(std::string newText, User* newSender):Message(newText){
MessageSe::Count++;
this->ID=MessageSe::Count;
this->Sender=newSender;
}
//---------------------------------------------------------------------------
const User* MessageSe::GetSender()const{
return this->Sender;
}
//---------------------------------------------------------------------------
std::string MessageSe::GetSenderName()const{
return this->Sender->GetName();
}
//---------------------------------------------------------------------------
std::string MessageSe::GetSenderIP()const{
return this->Sender->GetIP();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
MessageCl::MessageCl(std::string newText, std::string SenderName):Message(newText){
this->SenderName=SenderName;
}
//---------------------------------------------------------------------------
std::string MessageCl::GetSenderName()const{
return this->SenderName;
}
//---------------------------------------------------------------------------
