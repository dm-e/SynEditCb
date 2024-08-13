//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSyneditTest_frm *SyneditTest_frm;


//---------------------------------------------------------------------------
__fastcall TSyneditTest_frm::TSyneditTest_frm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSyneditTest_frm::FormCreate(TObject *Sender)
{
	SynEdit1 = new TSynEdit(this);
  SynEdit1->Parent = this;
	SynEdit1->Align = alClient;
	
	//m_pWSSynHighlighter = new CWSSynHighlighter(this);
	//SynEdit1->Highlighter = m_pWSSynHighlighter;

	SynEdit1->ClearAll();
	//SynEdit1->Text = m_pWSSynHighlighter->SampleSource;
}
//---------------------------------------------------------------------------

