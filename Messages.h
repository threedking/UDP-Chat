//---------------------------------------------------------------------------
#ifndef MessagesH
#define MessagesH

#include "Users.h"
#include <ctime>
#include <algorithm>
#include <chrono>
//---------------------------------------------------------------------------
class Message{
protected:
	static int MAXTextLength;
	unsigned int ID=0;//Ќазначает только сервер. 0 - не назначено

	std::string Text="";
	std::time_t Time;

	void SetText(std::string newText);
public:
	static bool CheckSingleLetter(unsigned short Key);

	Message(std::string newText);

	std::string GetText()const;
	std::time_t GetTime()const;
	int GetID()const;

	bool operator<(const Message& Other)const;
	bool operator==(const Message& Other)const;
};
int Message::MAXTextLength=100;
//---------------------------------------------------------------------------
class MessageSe: public Message{
protected:
	static int Count;

	User* Sender=NULL;
public:
	MessageSe(std::string newText, User* newSender);

	const User* GetSender()const;
	std::string GetSenderName()const;
	std::string GetSenderIP()const;
};
int MessageSe::Count=0;
//---------------------------------------------------------------------------
class MessageCl: public Message{
protected:
	std::string SenderName;
public:
	MessageCl(std::string newText, std::string SenderName);

	std::string GetSenderName()const;
};
//---------------------------------------------------------------------------
#endif
