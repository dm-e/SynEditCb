#ifndef SynURIOpenerH
#define SynURIOpenerH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Vcl.Controls.hpp>
#include "SynEditTypes.h"
#include "SynEdit.h"
#include "SynHighlighterURI.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Synuriopener
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynURIOpener.pas, released 2003-09-25.
The Initial Author of this file is Ma�l H�rz.
Unicode translation by Ma�l H�rz.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

You may retrieve the latest version of SynEdit from the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/
/*
@abstract(Plugin for SynEdit to make links (URIs) clickable)
@author(Ma�l H�rz)
@created(2003)
@lastmod(2004-03-19)
The SynURIOpener unit extends SynEdit to make links highlighted by SynURISyn
clickable.

http://www.mh-net.de.vu
*/

class TSynURIOpener : public System::Classes::TComponent
{
private:
	bool FControlDown;
	bool FCtrlActivatesLinks;
	Synedit::TCustomSynEdit* FEditor;
	int fMouseDownX;
	int fMouseDownY;
	Synhighlighteruri::TSynURISyn* FURIHighlighter;
	System::Classes::TStringList* FVisitedURIs;
	void __fastcall OpenLink(String URI, int LinkType);
	bool __fastcall MouseInSynEdit();
protected:
	void __fastcall NewKeyDown(TObject* Sender, WORD& key, System::Classes::TShiftState Shift);
	void __fastcall NewKeyUp(TObject* Sender, WORD& key, System::Classes::TShiftState Shift);
	void __fastcall NewMouseCursor(TObject* Sender, const Synedit::TBufferCoord& aLineCharPos, TCursor& aCursor);
	void __fastcall NewMouseDown(TObject* Sender, TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall NewMouseUp(TObject* Sender, TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall SetEditor(Synedit::TCustomSynEdit* const Value);
	void __fastcall SetURIHighlighter(Synhighlighteruri::TSynURISyn* const Value);
public:
	typedef System::Classes::TComponent inherited;	
	#include "SynURIOpener_friends.inc"
	__fastcall TSynURIOpener(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynURIOpener();
	bool __fastcall VisitedURI(String URI);
__published:
	__property bool CtrlActivatesLinks = { read = FCtrlActivatesLinks, write = FCtrlActivatesLinks, default = true };
	__property TCustomSynEdit* Editor = { read = FEditor, write = SetEditor };
	__property TSynURISyn* URIHighlighter = { read = FURIHighlighter, write = SetURIHighlighter };
};

void SynURIOpener_initialization();


}  // namespace SynURIOpener

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synuriopener;
#endif


#endif // SynURIOpenerH

