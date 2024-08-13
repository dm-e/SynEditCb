/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynAutoCorrect.pas, released 2001-10-05.
Author of this file is Aaron Chan.
Unicode translation by Maël Hörz.
All Rights Reserved.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynAutoCorrect.pas,v 1.13.2.7 2008/09/14 16:24:57 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------*/

/*********************************************************/
/*                                                       */
/*       Aerodynamica Components                         */
/*       SynAutoCorrect 2.x                              */
/*                                                       */
/*       Copyright (c) 1996-2003, Aerodynamica Software  */
/*                                                       */
/*       Author: Aaron Chan                              */
/*       Portions by Greg Nixon and Jan Fiala            */
/*                                                       */
/*********************************************************/

/*
  @author: Aaron Chan
  @url: http://aerodynamica.idz.net
  @comp-url: http://aerodynamica.idz.net/products.asp?id=SynAC_2
  @email: aerodynamica@idz.net
  @last-updated: 12/04/03
  @history:

    ! comment     * changed     + added
    - removed     @ bug-fixed   # todo

    12/04/2003
      - removed integrated sound support.
      * changed keyboard and mouse handling to use SynEdit plugin system.

    11/04/04 - Release 2.21:
      @ Fixed support for correction after delimiters.
      * SOUND_SUPPORT undefined by default.

    24/03/03 - Release 2.2:
      @ Fixed "Stack Overflow" bug and memory leak (fixed by Danail Traichev).

    30/09/02 - Release 2.1:
      @ Fixed bug when user KeyDown and MouseDown events weren't fired.
      + Added INI_FILES and REGISTRY compiler defines (to minimize code size
        if you don't need these features).
      * Further tidy-up of code.
      * Quite a few minor bug-fixes and tweaks.
      * Items editor enhanced.
      * Improved demo.
      * Registry and INI file entries are saved in a new and improved way, which
        overcomes some limitations set by the old method. If you still want to
        use the old method, define OLD_SAVE_METHOD.

    31/07/02 - Revision 2.01:
      @ Fixed bug which occured when undefining SOUND_SUPPORT (reported by
        Stefan Ascher).

    30/07/02 - First public release of version 2.0:
      @ MANY bugs fixed and small tweaks everywhere in the code (some
        courtesy of Jan Fiala).
      + Ability to play an optional WAVE file (or beep) on correction.
      + Options set.
      * New demo.
*/
#ifndef SynAutoCorrectH
#define SynAutoCorrectH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <System.Win.Registry.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "SynEditMiscProcs.h"
#include "SynEditTypes.h"
#include "SynEditKeyCmds.h"
#include "SynEdit.h"
#include "SynEditMiscClasses.h"
#include "SynUnicode.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.IniFiles.hpp>

namespace Synautocorrect
{



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
enum TAsSynAutoCorrectOption {ascoCorrectOnMouseDown,
                              ascoIgnoreCase,
                              ascoMaintainCase };
typedef System::Set<TAsSynAutoCorrectOption, TAsSynAutoCorrectOption::ascoCorrectOnMouseDown, TAsSynAutoCorrectOption::ascoMaintainCase> TAsSynAutoCorrectOptions;
enum TAutoCorrectAction {aaCorrect,
                         aaAbort };
typedef void __fastcall (__closure *TAutoCorrectEvent) (TObject*, const String, const String, int, int, TAutoCorrectAction&);

class TCustomSynAutoCorrect : public System::Classes::TComponent
{
private:
    /* Private declarations */

    /* Published properties and events */
	Synedit::TCustomSynEdit* FEditor;
	bool FEnabled;
	TStrings* FItems;
	WideChar FItemSepChar;
	TAsSynAutoCorrectOptions fOptions;
	TAutoCorrectEvent FOnAutoCorrect;
	TNotifyEvent FOnCorrected;

    /* Private variables and methods */
	int FPrevLine;
	int __fastcall CorrectItemStart(String EditLine, String SearchString, int StartPos, bool MatchCase, bool WholeWord);
	bool __fastcall FindAndCorrect(String& EditLine, String Original, String Correction, int& CurrentX);
	String __fastcall PreviousToken();

    /* Accessor methods */
	TStrings* __fastcall GetItems();
	void __fastcall SetItems(TStrings* const Value);
protected:
    /* Protected declarations */
	virtual void __fastcall DefineProperties(TFiler* Filer);
	virtual void __fastcall KeyboardHandler(TObject* Sender, bool AfterProcessing, bool& Handled, Synedittypes::TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData);
	virtual void __fastcall MouseDownHandler(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(TComponent* AComponent, TOperation Operation);
	void __fastcall SetEditor(Synedit::TCustomSynEdit* Value);
public:
    /* Public declarations */
	typedef System::Classes::TComponent inherited;
	#include "SynAutoCorrect_friends.inc"
	__fastcall TCustomSynAutoCorrect(TComponent* AOwner);
	virtual __fastcall ~TCustomSynAutoCorrect();
	void __fastcall Add(String AOriginal, String ACorrection);
	bool __fastcall AutoCorrectAll();
	void __fastcall Delete(int AIndex);
	void __fastcall Edit(int AIndex, String ANewOriginal, String ANewCorrection);
	void __fastcall LoadFromINI(String AFileName, String ASection);
	void __fastcall SaveToINI(String AFileName, String ASection);
	void __fastcall LoadFromRegistry(DWORD ARoot, String AKey);
	void __fastcall SaveToRegistry(DWORD ARoot, String AKey);
	bool __fastcall LoadFromList(String AFileName);
	void __fastcall SaveToList(String AFileName);

    /* Utility functions */
	String __fastcall HalfString(String Str, bool GetFirstHalf);
    /* Published declarations */
	__property bool Enabled = { read = FEnabled, write = FEnabled, default = true };
	__property Synedit::TCustomSynEdit* Editor = { read = FEditor, write = SetEditor };
	__property TStrings* Items = { read = GetItems, write = SetItems };
	__property WideChar ItemSepChar = { read = FItemSepChar, write = FItemSepChar, default = L'\x09' };
	__property TAsSynAutoCorrectOptions Options = { read = fOptions, write = fOptions, default = /*# ascoIgnoreCase, ascoMaintainCase */ 0 };
	__property TAutoCorrectEvent OnAutoCorrect = { read = FOnAutoCorrect, write = FOnAutoCorrect };
	__property TNotifyEvent OnCorrected = { read = FOnCorrected, write = FOnCorrected };
};

class TSynAutoCorrect : public TCustomSynAutoCorrect
{
__published:
public:
    /* Published declarations */
	__property  Enabled;
	__property  Editor;
	__property  Items;
	__property  ItemSepChar;
	__property  Options;
	__property  OnAutoCorrect;
	__property  OnCorrected;
public:
	typedef TCustomSynAutoCorrect inherited;
	#include "SynAutoCorrect_friends.inc"
	__fastcall TSynAutoCorrect(TComponent* AOwner);
};


}  // namespace SynAutoCorrect

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synautocorrect;
#endif

#endif // SynAutoCorrectH

