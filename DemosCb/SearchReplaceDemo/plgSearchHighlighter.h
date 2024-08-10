#ifndef plgSearchHighlighterH
#define plgSearchHighlighterH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include "SynEdit.h"
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynEditPlugins.h"



class TSearchTextHightlighterSynEditPlugin : public TSynEditPlugin
{

public:
	typedef TSynEditPlugin inherited;
private:
	TSynHighlighterAttributes* FAttribute;
protected:
	virtual void __fastcall AfterPaint(TCanvas* ACanvas, const TRect& AClip, int FirstLine, int LastLine);
public:
	virtual void __fastcall AfterConstruction();
	virtual __fastcall ~TSearchTextHightlighterSynEditPlugin();
	__property TSynHighlighterAttributes* Attribute = { read = FAttribute, write = FAttribute };
	__fastcall TSearchTextHightlighterSynEditPlugin(TCustomSynEdit* AOwner);
	__fastcall TSearchTextHightlighterSynEditPlugin(TCustomSynEdit* AOwner, TPlugInHandlers AHandlers);
	__fastcall TSearchTextHightlighterSynEditPlugin();
};

#endif // plgSearchHighlighterH

