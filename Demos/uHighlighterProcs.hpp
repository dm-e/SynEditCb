// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'uHighlighterProcs.pas' rev: 35.00 (Windows)

#ifndef UhighlighterprocsHPP
#define UhighlighterprocsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <SynEditHighlighter.hpp>

//-- user supplied -----------------------------------------------------------

namespace Uhighlighterprocs
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall GetHighlighters(System::Classes::TComponent* AOwner, System::Classes::TStringList* AHighlighters, bool AppendToList);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetHighlightersFilter(System::Classes::TStringList* AHighlighters);
extern DELPHI_PACKAGE Synedithighlighter::TSynCustomHighlighter* __fastcall GetHighlighterFromFileExt(System::Classes::TStringList* AHighlighters, System::UnicodeString Extension);
}	/* namespace Uhighlighterprocs */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_UHIGHLIGHTERPROCS)
using namespace Uhighlighterprocs;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UhighlighterprocsHPP
