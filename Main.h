//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdGlobal.hpp>
#include <IdSocketHandle.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPServer.hpp>

#include "Server.h"
#include "Client.h"
//---------------------------------------------------------------------------
class TFormSe : public TForm
{
__published:	// IDE-managed Components
	TIdUDPServer *IdUDPServer1;
	void __fastcall IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
		  TIdSocketHandle *ABinding);
private:	// User declarations
public:		// User declarations
	__fastcall TFormSe(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSe *FormSe;
//---------------------------------------------------------------------------
#endif

