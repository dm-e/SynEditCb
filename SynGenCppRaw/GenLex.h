#ifndef GenLexH
#define GenLexH

#include <System.hpp>
#include "d2c_system.h"

#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include "LongIntList.h"
#include "SynUnicode.h"

namespace Genlex
{

extern unsigned char Identifiers[256/*# range #0..#255*/];
extern int mHashTable[256/*# range #0..#255*/];
enum TIdTokenKind {IdBeginFunc,
                   IdBeginProc,
                   IdBraceOpen,
                   IdChars,
                   IdCharset,
                   IdCRLF,
                   IdEndFunc,
                   IdEndProc,
                   IdIdent,
                   IdIdentifier,
                   IdIdentStart,
                   IdKeys,
                   IdTokenTypes,
                   IdNull,
                   IdSensitive,
                   IdSpace,
                   IdStop,
                   IdEnclosedBy,
                   IdSampleSource,
                   IdUnknown };

class TGenLex : public System::TObject
{
	#include "GenLex_friends.inc"
public:
	typedef TObject inherited;	
private:
	bool fIgnoreComments;
	PWideChar FOrigin;
	typedef void (__closure __fastcall *GenLexProc__0)();
	GenLexProc__0 fProcTable[256/*# range #0..#255*/];
	typedef TIdTokenKind (__closure __fastcall *GenLexProc__1)();
	GenLexProc__1 fFuncTable[256/*# range #0..#255*/];
	int Run;
	int Walker;
	int Running;
	int fStringLen;
	PWideChar fToIdent;
	bool fTokenizing;
	Longintlist::TLongintList* FLinePosList;
	Longintlist::TLongintList* FTokenPositionsList;
	typedef TIdTokenKind (__closure __fastcall *GenLexProc__2)();
	GenLexProc__2 fIdentFuncTable[151/*# range 0..150*/];
	int __fastcall KeyHash(PWideChar ToHash);
	bool __fastcall KeyComp(String AKey);
	TIdTokenKind __fastcall Func49();
	TIdTokenKind __fastcall Func60();
	TIdTokenKind __fastcall Func67();
	TIdTokenKind __fastcall Func75();
	TIdTokenKind __fastcall Func81();
	TIdTokenKind __fastcall Func89();
	TIdTokenKind __fastcall Func104();
	TIdTokenKind __fastcall Func122();
	TIdTokenKind __fastcall Func130();
	TIdTokenKind __fastcall Func147();
	TIdTokenKind __fastcall Func150();
	void __fastcall BraceOpenProc();
	TIdTokenKind __fastcall BraceOpenFunc();
	void __fastcall CRLFProc();
	TIdTokenKind __fastcall CRLFFunc();
	void __fastcall CharsetProc();
	TIdTokenKind __fastcall CharsetFunc();
	void __fastcall IdentProc();
	TIdTokenKind __fastcall IdentFunc();
	void __fastcall NullProc();
	TIdTokenKind __fastcall NullFunc();
	void __fastcall SpaceProc();
	TIdTokenKind __fastcall SpaceFunc();
	void __fastcall StopProc();
	TIdTokenKind __fastcall StopFunc();
	void __fastcall UnknownProc();
	TIdTokenKind __fastcall UnknownFunc();
	TIdTokenKind __fastcall AltFunc();
	void __fastcall InitIdent();
	TIdTokenKind __fastcall IdentKind(PWideChar Maybe);
	void __fastcall SetOrigin(PWideChar NewValue);
	void __fastcall SetRunPos(int Value);
	void __fastcall MakeMethodTables();
	TIdTokenKind __fastcall GetRunId();
	String __fastcall GetRunToken();
protected:
public:
	__fastcall TGenLex();
	virtual __fastcall ~TGenLex();
	void __fastcall Tokenize();
	void __fastcall Next();
	__property bool IgnoreComments = { read = fIgnoreComments, write = fIgnoreComments };
	__property PWideChar Origin = { read = FOrigin, write = SetOrigin };
	__property int RunPos = { read = Run, write = SetRunPos };
	String __fastcall NextToken();
	bool __fastcall Eof();
	__property TIdTokenKind RunId = { read = GetRunId };
	__property String RunToken = { read = GetRunToken };
};

void GenLex_initialization();


}  // namespace GenLex

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Genlex;
#endif


#endif // GenLexH

