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
public:
	TSynEdit* SynTest;
	TSynEdit* SynEdit1;
	TButton* Button3;
	TSynCompletionProposal* scpParams;
	TFontDialog* FontDialog1;
	void __fastcall scpParamsExecute(SynCompletionType Kind, TObject* Sender, UnicodeString& AString, int& x, int& y, bool& CanExecute);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall Button3Click(TObject* Sender);
private:
    /* Private declarations */
	TStringList* LookupList;
public:
    /* Public declarations */
	typedef TForm inherited;
	__fastcall TForm1(TComponent* AOwner, int Dummy);
protected:
	//# please uncomment for main forms
	//# void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
		//# {inherited::CreateParams(Params); Params.ExStyle = Params.ExStyle | WS_EX_APPWINDOW;}
};
extern PACKAGE TForm1* Form1;

#endif // FormMain_ctParamsH

