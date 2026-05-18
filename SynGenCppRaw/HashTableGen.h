#ifndef HashTableGenH
#define HashTableGenH

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
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>




/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $

class TFrmHashTableGen : public TForm
{
__published:
public:
	TLabel* LabelParams;
	TLabel* LabelD;
	TLabel* LabelC;
	TLabel* LabelM;
	TLabel* Label1;
	TLabel* Label2;
	TLabel* LabelPercentage;
	TProgressBar* ProgressBar1;
	TMemo* EditD;
	TMemo* EditC;
	TMemo* EditM;
	TButton* ButtonFindHash;
	void __fastcall ButtonFindHashClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormDestroy(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
private:
	TList* FKeyList;
public:
	typedef TForm inherited;
	#include "HashTableGen_friends.inc"
	void __fastcall AssignKeyWords(TList* KeyList, bool CaseSensitive);
	String __fastcall GetHashKeyFunctionSource(String ClassName);
	String __fastcall GetKeyWordConstantsSource(bool CaseSensitive);
	int __fastcall KeyIndicesCount();
	__fastcall TFrmHashTableGen(TComponent* AOwner, int Dummy);
protected:
	//# please uncomment for main forms
	//# void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params)
		//# {inherited::CreateParams(Params); Params.ExStyle = Params.ExStyle | WS_EX_APPWINDOW;}
};
const int MaxTableSize = 100000;

class THashKeyList : public System::TObject
{
	#include "HashTableGen_friends.inc"
public:
	typedef System::TObject inherited;
private:
	int FMaxHashKey;
	bool FHashKeys[(MaxTableSize - 1) + 1/*# range 0..MaxTableSize-1*/];
public:
	bool __fastcall Add(int HashKey);
	void __fastcall Clear();
	__fastcall THashKeyList();
};
extern PACKAGE TFrmHashTableGen* FrmHashTableGen;
#endif // HashTableGenH

