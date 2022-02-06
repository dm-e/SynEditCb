#ifndef FormMain_ctCodeH
#define FormMain_ctCodeH

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
#include <Vcl.ComCtrls.hpp>


const int cCaseSensitive = 1;
const int cAnsiStrings = 2;
const int cPrettyText = 3;
const int cInsertList = 4;
const int cMatchedText = 5;

class TForm1 : public TForm
{
__published:
	TPageControl* PageControl1;
	TTabSheet* CodeCompletion;
	TTabSheet* TabSheet2;
	TMemo* mmoInsert;
	TMemo* mmoItem;
	TLabel* Label1;
	TLabel* Label2;
	TButton* Button1;
	TButton* Button2;
	TEdit* edBiggestWord;
	TLabel* Label3;
	TCheckBox* cbCase;
	TCheckBox* cbPrettyText;
	TCheckBox* cbUseInsertList;
	TCheckBox* cbLimitToMatchedText;
	TEdit* edTitle;
	TLabel* Label4;
	TButton* Button3;
	TButton* Button4;
	TFontDialog* FontDialog1;
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall CheckBoxClick(TObject* Sender);
	void __fastcall edBiggestWordChange(TObject* Sender);
	void __fastcall Button1Click(TObject* Sender);
	void __fastcall Button2Click(TObject* Sender);
	void __fastcall edTitleChange(TObject* Sender);
	void __fastcall Button3Click(TObject* Sender);
	void __fastcall Button4Click(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:
	TSynCompletionProposal* scpDemo;
	TSynEdit* SynTest;
	TSynEdit* SynEdit1;
public:
    /* Public declarations */
	typedef TForm inherited;	
	__fastcall TForm1(TComponent* AOwner);
};
extern PACKAGE TForm1* Form1;
#endif // FormMain_ctCodeH
