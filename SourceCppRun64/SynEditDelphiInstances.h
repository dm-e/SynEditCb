#ifndef SynEditDelphiInstancesH
#define SynEditDelphiInstancesH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <Vcl.Controls.hpp>

namespace Syneditdelphiinstances
{


#pragma link "SynEditDelphiInstances"

  // A single fold
  // Important: FromLine, ToLine are 1-based

struct TSynFoldRange
{
	int FromLine; // Beginning line
	int ToLine; // End line
	int FoldType;  // Could be used by some complex highlighters
	int Indent;   // Only used for Indent based folding (Python)
	bool Collapsed; // Is collapsed?
private:
	int __fastcall GetLinesCollapsed();
public:
	void __fastcall Move(int Count);
	__property int LinesCollapsed = { read = GetLinesCollapsed };
	__fastcall TSynFoldRange(int AFromLine, int AToLine = -1, int AFoldType = 1, int AIndent = -1, bool ACollapsed = false);

	TSynFoldRange() {}
};
typedef TSynFoldRange* PSynFoldRange;
enum TFoldOpenClose {focOpen,
                     focClose };

struct TLineFoldInfo
{
	int Line;
	TFoldOpenClose FoldOpenClose;
	int FoldType;
	int Indent;
	__fastcall TLineFoldInfo(int ALine, TFoldOpenClose AFoldOpenClose = Syneditdelphiinstances::focOpen, int AFoldType = 1, int AIndent = -1);

	TLineFoldInfo() {}
};

struct TBufferCoord
{
	int Char;
	int Line;
	friend bool __fastcall operator == (const TBufferCoord& A, const TBufferCoord& B);
	friend bool __fastcall operator != (const TBufferCoord& A, const TBufferCoord& B);
	friend bool __fastcall operator < (const TBufferCoord& A, const TBufferCoord& B);
	friend bool __fastcall operator <= (const TBufferCoord& A, const TBufferCoord& B);
	friend bool __fastcall operator > (const TBufferCoord& A, const TBufferCoord& B);
	friend bool __fastcall operator >= (const TBufferCoord& A, const TBufferCoord& B);
	static TBufferCoord __fastcall Min(const TBufferCoord& A, const TBufferCoord& B);
	static TBufferCoord __fastcall Max(const TBufferCoord& A, const TBufferCoord& B);
};

class TSynUndoItem : public System::TObject
{
	#include "SynEditDelphiInstances_friends.inc"
public:
	typedef System::TObject inherited;
	int ChangeNumber;
	TBufferCoord FCaret;
	bool GroupBreak;
	virtual void __fastcall Undo(TCustomControl* Editor){} // = 0;
	virtual void __fastcall Redo(TCustomControl* Editor){} // = 0;
	__fastcall TSynUndoItem();
};

class TSynFoldRangesCmp : public System::TCppInterfacedObject<Generics::System::Generics::Defaults::IComparer__1<TSynFoldRange>>
{
	#include "SynEditDelphiInstances_friends.inc"
	//# unimplemented IComparer not found
public:
	typedef System::TCppInterfacedObject<Generics::System::Generics::Defaults::IComparer__1<TSynFoldRange>> inherited;	int __fastcall Compare(const TSynFoldRange& Left, const TSynFoldRange& Right);
	__fastcall TSynFoldRangesCmp();
};

class TLineFoldInfoCmp : public System::TCppInterfacedObject<Generics::System::Generics::Defaults::IComparer__1<TLineFoldInfo>>
{
	#include "SynEditDelphiInstances_friends.inc"
	//# unimplemented IComparer not found
public:
	typedef System::TCppInterfacedObject<Generics::System::Generics::Defaults::IComparer__1<TLineFoldInfo>> inherited;	int __fastcall Compare(const TLineFoldInfo& Left, const TLineFoldInfo& Right);
	__fastcall TLineFoldInfoCmp();
};
System::Generics::Collections::TList__1<TSynFoldRange>* __fastcall CreateFoldRangeList();
System::Generics::Collections::TList__1<TLineFoldInfo>* __fastcall CreateFoldInfoList();
void __fastcall AddToFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange& ARange);
void __fastcall InsertIntoFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, int AIndex, const TSynFoldRange& ARange);
bool __fastcall BinarySearchInFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange& ARange, int& AIndex);

// for SynEditCodeFolding
void __fastcall InsertIntoLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, int AIndex, const TLineFoldInfo& AInfo);
bool __fastcall BinarySearchInLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, const TLineFoldInfo& AInfo, int& AIndex);

void SynEditDelphiInstances_initialization();


}  // namespace SynEditDelphiInstances

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditdelphiinstances;
#endif


#endif // SynEditDelphiInstancesH

