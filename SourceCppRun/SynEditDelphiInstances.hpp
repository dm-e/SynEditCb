// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SynEditDelphiInstances.pas' rev: 35.00 (Windows)

#ifndef SyneditdelphiinstancesHPP
#define SyneditdelphiinstancesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <Vcl.Controls.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "SynEditDelphiInstances"

namespace Syneditdelphiinstances
{
//-- forward type declarations -----------------------------------------------
struct TSynFoldRange;
struct TLineFoldInfo;
struct TBufferCoord;
class DELPHICLASS TSynUndoItem;
class DELPHICLASS TSynFoldRangesCmp;
class DELPHICLASS TLineFoldInfoCmp;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TSynFoldRange
{
public:
	int FromLine;
	int ToLine;
	int FoldType;
	int Indent;
	bool Collapsed;
	
private:
	int __fastcall GetLinesCollapsed();
	
public:
	void __fastcall Move(int Count);
	__property int LinesCollapsed = {read=GetLinesCollapsed};
	__fastcall TSynFoldRange(int AFromLine, int AToLine, int AFoldType, int AIndent, bool ACollapsed);
	TSynFoldRange() {}
};


typedef TSynFoldRange *PSynFoldRange;

enum DECLSPEC_DENUM TFoldOpenClose : unsigned char { focOpen, focClose };

struct DECLSPEC_DRECORD TLineFoldInfo
{
public:
	int Line;
	TFoldOpenClose FoldOpenClose;
	int FoldType;
	int Indent;
	__fastcall TLineFoldInfo(int ALine, TFoldOpenClose AFoldOpenClose, int AFoldType, int AIndent);
	TLineFoldInfo() {}
};


struct DECLSPEC_DRECORD TBufferCoord
{
public:
	int Char;
	int Line;
	static bool __fastcall _op_Equality(const TBufferCoord &a, const TBufferCoord &b);
	static bool __fastcall _op_Inequality(const TBufferCoord &a, const TBufferCoord &b);
	static bool __fastcall _op_LessThan(const TBufferCoord &a, const TBufferCoord &b);
	static bool __fastcall _op_LessThanOrEqual(const TBufferCoord &a, const TBufferCoord &b);
	static bool __fastcall _op_GreaterThan(const TBufferCoord &a, const TBufferCoord &b);
	static bool __fastcall _op_GreaterThanOrEqual(const TBufferCoord &a, const TBufferCoord &b);
	static TBufferCoord __fastcall Min(const TBufferCoord &a, const TBufferCoord &b);
	static TBufferCoord __fastcall Max(const TBufferCoord &a, const TBufferCoord &b);
	
	friend bool operator ==(const TBufferCoord &a, const TBufferCoord &b) { return TBufferCoord::_op_Equality(a, b); }
	friend bool operator !=(const TBufferCoord &a, const TBufferCoord &b) { return TBufferCoord::_op_Inequality(a, b); }
	friend bool operator <(const TBufferCoord &a, const TBufferCoord &b) { return TBufferCoord::_op_LessThan(a, b); }
	friend bool operator <=(const TBufferCoord &a, const TBufferCoord &b) { return TBufferCoord::_op_LessThanOrEqual(a, b); }
	friend bool operator >(const TBufferCoord &a, const TBufferCoord &b) { return TBufferCoord::_op_GreaterThan(a, b); }
	friend bool operator >=(const TBufferCoord &a, const TBufferCoord &b) { return TBufferCoord::_op_GreaterThanOrEqual(a, b); }
};


#pragma pack(push,4)
class PASCALIMPLEMENTATION TSynUndoItem : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int ChangeNumber;
	TBufferCoord FCaret;
	bool GroupBreak;
	virtual void __fastcall Undo(Vcl::Controls::TCustomControl* Editor) = 0 ;
	virtual void __fastcall Redo(Vcl::Controls::TCustomControl* Editor) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TSynUndoItem() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSynUndoItem() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TSynFoldRangesCmp : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	int __fastcall Compare(const TSynFoldRange &Left, const TSynFoldRange &Right);
public:
	/* TObject.Create */ inline __fastcall TSynFoldRangesCmp() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSynFoldRangesCmp() { }
	
private:
	void *__IComparer__1;	// System::Generics::Defaults::IComparer__1<TSynFoldRange> 
	
public:
	operator System::Generics::Defaults::IComparer__1<TSynFoldRange>*(void) { return (System::Generics::Defaults::IComparer__1<TSynFoldRange>*)&__IComparer__1; }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION TLineFoldInfoCmp : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	int __fastcall Compare(const TLineFoldInfo &Left, const TLineFoldInfo &Right);
public:
	/* TObject.Create */ inline __fastcall TLineFoldInfoCmp() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TLineFoldInfoCmp() { }
	
private:
	void *__IComparer__1;	// System::Generics::Defaults::IComparer__1<TLineFoldInfo> 
	
public:
	operator System::Generics::Defaults::IComparer__1<TLineFoldInfo>*(void) { return (System::Generics::Defaults::IComparer__1<TLineFoldInfo>*)&__IComparer__1; }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Generics::Collections::TList__1<TSynFoldRange>* __fastcall CreateFoldRangeList();
extern DELPHI_PACKAGE System::Generics::Collections::TList__1<TLineFoldInfo>* __fastcall CreateFoldInfoList();
extern DELPHI_PACKAGE void __fastcall AddToFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange &ARange);
extern DELPHI_PACKAGE bool __fastcall BinarySearchInFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange &ARange, int &AIndex);
extern DELPHI_PACKAGE void __fastcall InsertIntoLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, int AIndex, const TLineFoldInfo &AInfo);
extern DELPHI_PACKAGE bool __fastcall BinarySearchInLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, const TLineFoldInfo &AInfo, int &AIndex);
}	/* namespace Syneditdelphiinstances */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYNEDITDELPHIINSTANCES)
using namespace Syneditdelphiinstances;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SyneditdelphiinstancesHPP
