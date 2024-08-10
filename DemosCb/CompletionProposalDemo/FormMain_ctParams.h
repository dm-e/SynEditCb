#ifndef FormMain_ctParamsH
#define FormMain_ctParamsH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "SynCompletionProposal.h"
#include <Vcl.StdCtrls.hpp>
#include "SynEdit.h"



class TForm1 : public TForm
{
__published:
	TButton* Button3;
	TFontDialog* FontDialog1;
	void __fastcall scpParamsExecute(SynCompletionType Kind, TObject* Sender, UnicodeString& AString, int& X, int& Y, bool& CanExecute);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall Button3Click(TObject* Sender);
private:
	TSynEdit* SynTest;
	TSynEdit* SynEdit1;
	TStringList* LookupList;
	TSynCompletionProposal* scpParams;
public:
    /* Public declarations */
	typedef TForm inherited;
	__fastcall TForm1(TComponent* AOwner);
};
extern PACKAGE TForm1* Form1;

#endif // FormMain_ctParamsH

