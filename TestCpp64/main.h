//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "SynEdit.h"

using namespace Synedit;

class CWSSynHighlighter;
//---------------------------------------------------------------------------
class TSyneditTest_frm : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	void __fastcall FormCreate(TObject *Sender);
private:	// Benutzer-Deklarationen
	TSynEdit *SynEdit1;
	CWSSynHighlighter*  m_pWSSynHighlighter;
public:		// Benutzer-Deklarationen
	__fastcall TSyneditTest_frm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSyneditTest_frm *SyneditTest_frm;
//---------------------------------------------------------------------------
#endif
