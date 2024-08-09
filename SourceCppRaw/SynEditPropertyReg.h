/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditPropertyReg.pas, released 2000-04-07.
The Original Code is based on mwEditPropertyReg.pas, part of the
mwEdit component suite.
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

$Id: SynEditPropertyReg.pas,v 1.17.2.6 2008/09/14 16:24:59 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditPropertyRegH
#define SynEditPropertyRegH

#include <System.hpp>
#include "d2c_system.h"

#include "DesignIntf.hpp"
#include "DesignEditors.hpp"
#include "VCLEditors.hpp"
#include "StrEdit.hpp"
#include "SynUnicode.h"
#include <System.Classes.hpp>

namespace Syneditpropertyreg
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

class TSynEditFontProperty : public Vcleditors::TFontProperty
{
	#include "SynEditPropertyReg_friends.inc"
public:
	typedef Vcleditors::TFontProperty inherited;
	virtual void __fastcall Edit();
	__fastcall TSynEditFontProperty(IDesigner* const ADesigner, int APropCount);
	__fastcall TSynEditFontProperty();
};

class TSynEditCommandProperty : public Designeditors::TIntegerProperty
{
	#include "SynEditPropertyReg_friends.inc"
public:
	typedef Designeditors::TIntegerProperty inherited;
	virtual void __fastcall Edit();
	virtual TPropertyAttributes __fastcall GetAttributes();
	virtual String __fastcall GetValue();
	virtual void __fastcall GetValues(TGetStrProc Proc);
	virtual void __fastcall SetValue(const String Value);
	__fastcall TSynEditCommandProperty(IDesigner* const ADesigner, int APropCount);
	__fastcall TSynEditCommandProperty();
};

class TSynEditKeystrokesProperty : public Designeditors::TClassProperty
{
	#include "SynEditPropertyReg_friends.inc"
public:
	typedef Designeditors::TClassProperty inherited;
	virtual void __fastcall Edit();
	virtual TPropertyAttributes __fastcall GetAttributes();
	__fastcall TSynEditKeystrokesProperty(IDesigner* const ADesigner, int APropCount);
	__fastcall TSynEditKeystrokesProperty();
};

class TSynEditPrintMarginsProperty : public Designeditors::TClassProperty
{
	#include "SynEditPropertyReg_friends.inc"
public:
	typedef Designeditors::TClassProperty inherited;
	virtual void __fastcall Edit();
	virtual TPropertyAttributes __fastcall GetAttributes();
	__fastcall TSynEditPrintMarginsProperty(IDesigner* const ADesigner, int APropCount);
	__fastcall TSynEditPrintMarginsProperty();
};

class TAutoCorrectionProperty : public Designeditors::TPropertyEditor
{
	#include "SynEditPropertyReg_friends.inc"
public:
	typedef Designeditors::TPropertyEditor inherited;
	virtual void __fastcall Edit();
	virtual TPropertyAttributes __fastcall GetAttributes();
	virtual String __fastcall GetValue();
	__fastcall TAutoCorrectionProperty(IDesigner* const ADesigner, int APropCount);
	__fastcall TAutoCorrectionProperty();
};

class TSynAutoCorrectComponentEditor : public Designeditors::TDefaultEditor
{
	#include "SynEditPropertyReg_friends.inc"
public:
	typedef Designeditors::TDefaultEditor inherited;
	virtual void __fastcall Edit();
	virtual void __fastcall ExecuteVerb(int Index);
	virtual String __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount();
	__fastcall TSynAutoCorrectComponentEditor(TComponent* AComponent, IDesigner* ADesigner);
	__fastcall TSynAutoCorrectComponentEditor();
};
void __fastcall Register();


}  // namespace SynEditPropertyReg

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditpropertyreg;
#endif

#endif // SynEditPropertyRegH

