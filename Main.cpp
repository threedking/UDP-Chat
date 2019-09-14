//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSe *FormSe;
Server* ServerInstance=&Server::getInstance();
//---------------------------------------------------------------------------
__fastcall TFormSe::TFormSe(TComponent* Owner)
	: TForm(Owner)
{
ServerInstance->SetIdUDPServer(FormSe->IdUDPServer1);
}
//---------------------------------------------------------------------------
void __fastcall TFormSe::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding)
{
ServerInstance->Request(ABinding->PeerIP,BytesToString(AData));
}
//---------------------------------------------------------------------------

