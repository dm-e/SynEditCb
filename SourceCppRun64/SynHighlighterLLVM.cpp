
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterLLVM.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterllvm
{
#define Synhighlighterllvm__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterllvm__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterllvm__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterllvm__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterllvm__4 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterllvm__5 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterllvm__6 (TSysCharSet() <<  \
										48 << 49 << 50 << 51 << 52 << 53 <<  \
										54 << 55 << 56 << 57)
#define Synhighlighterllvm__7 (TSysCharSet() << 'e' << 'E')
#define Synhighlighterllvm__8 (TSysCharSet() << 'x' << 'X')


  // as this language is case-insensitive keywords *must* be in lowercase
const UnicodeString Keywords[217/*# range 0..216*/] = {L"acq_rel", L"acquire", L"add", L"addrspace", L"alias", L"align", L"alignstack", L"alloca", L"alwaysinline", L"and"
																				, L"appending", L"arcp", L"arm_aapcs_vfpcc", L"arm_aapcscc", L"arm_apcscc", L"ashr", L"asm", L"atomic", L"atomicrmw", L"available_externally"
																				, L"bitcast", L"blockaddress", L"br", L"byval", L"c", L"call", L"catch", L"cc", L"ccc", L"cleanup", L"cmpxchg"
																				, L"coldcc", L"common", L"constant", L"datalayout", L"declare", L"default", L"define", L"deplibs", L"dllexport", L"dllimport"
																				, L"double", L"eq", L"exact", L"except", L"extern_weak", L"external", L"extractelement", L"extractvalue", L"fadd", L"false"
																				, L"fast", L"fastcc", L"fcmp", L"fdiv", L"fence", L"filter", L"float", L"fmul", L"fp128", L"fpext", L"fptosi", L"fptoui", L"fptrunc"
																				, L"free", L"frem", L"fsub", L"gc", L"getelementptr", L"global", L"half", L"hidden", L"icmp", L"inbounds", L"indirectbr", L"initialexec"
																				, L"inlinehint", L"inreg", L"insertelement", L"insertvalue", L"intel_ocl_bicc", L"inteldialect", L"internal", L"inttoptr"
																				, L"invoke", L"label", L"landingpad", L"linker_private", L"linker_private_weak", L"linker_private_weak_def_auto", L"linkonce"
																				, L"linkonce_odr", L"linkonce_odr_auto_hide", L"load", L"localdynamic", L"localexec", L"lshr", L"malloc", L"max"
																				, L"metadata", L"min", L"minsize", L"module", L"monotonic", L"msp430_intrcc", L"mul", L"naked", L"nand", L"ne", L"nest", L"ninf"
																				, L"nnan", L"noalias", L"nocapture", L"noimplicitfloat", L"noinline", L"nonlazybind", L"noredzone", L"noreturn", L"nounwind"
																				, L"nsw", L"nsz", L"null", L"nuw", L"oeq", L"oge", L"ogt", L"ole", L"olt", L"one", L"opaque", L"optsize", L"or", L"ord", L"personality"
																				, L"phi", L"ppc_fp128", L"private", L"protected", L"ptrtoint", L"ptx_device", L"ptx_kernel", L"readnone", L"readonly"
																				, L"release", L"resume", L"ret", L"returns_twice", L"sanitize_address", L"sanitize_memory", L"sanitize_thread", L"sdiv"
																				, L"section", L"select", L"seq_cst", L"sext", L"sge", L"sgt", L"shl", L"shufflevector", L"sideeffect", L"signext", L"singlethread", L"sitofp"
																				, L"sle", L"slt", L"spir_func", L"spir_kernel", L"srem", L"sret", L"ssp", L"sspreq", L"sspstrong", L"store", L"sub", L"switch"
																				, L"tail", L"target", L"thread_local", L"to", L"triple", L"true", L"trunc", L"type", L"udiv", L"ueq", L"uge", L"ugt", L"uitofp"
																				, L"ule", L"ult", L"umax", L"umin", L"undef", L"une", L"unnamed_addr", L"uno", L"unordered", L"unreachable", L"unwind", L"urem"
																				, L"uwtable", L"va_arg", L"void", L"volatile", L"weak", L"weak_odr", L"x86_fastcallcc", L"x86_fp80", L"x86_mmx", L"x86_stdcallcc", L"x86_thiscallcc"
																				, L"xchg", L"xor", L"zeroext", L"zeroinitializer", L"zext"};
const int KeyIndices[1553/*# range 0..1552*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 124, -1, -1, 64, 40, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 9, -1, -1, -1, -1, -1, 183, -1, -1, -1, 168, -1, -1, 79, -1, -1, -1, -1, 186, -1, -1, -1, -1, -1, 209, 37, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 166, -1, -1, -1
																				, -1, -1, -1, -1, 211, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 100, 62, -1, -1, -1, -1, -1, -1, 91, -1, -1
																				, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, 182, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 169, -1, -1, -1, -1, 26, 78, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, 116, 143, 93, -1, -1, -1, -1, -1, 165, -1, -1, 132, -1, -1, -1, -1, 195, -1, -1, -1, -1, 41, -1, -1, -1, -1, -1, 173, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, 36, -1, -1, -1, -1, -1, -1, -1, -1, -1, 119, -1, -1, 146, -1, -1, -1, -1, -1, -1, 205, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 120, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 151, -1, -1, -1, -1, -1, -1, -1, -1, 85, -1, -1, -1, -1, 207, -1, -1, -1, 111, -1, -1, -1, -1, -1, -1, 128, -1, -1, -1, -1, 106, -1
																				, -1, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 89, -1, -1, 161, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, -1, 24, -1, -1, -1, -1, -1, 10, -1, 133, -1, -1, 122, 65, -1, -1, 53, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 170, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 197, 144, -1, -1, -1, -1, -1, -1
																				, 57, -1, -1, -1, -1, 189, -1, -1, -1, -1, -1, -1, -1, 159, -1, -1, -1, -1, -1, -1, -1, -1, 59, -1, 35, -1, -1, 131, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, 147
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 77, -1, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 141, -1, -1, -1, -1, -1, 188, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 202, -1
																				, -1, -1, -1, -1, 32, -1, -1, -1, -1, 187, -1, -1, -1, -1, -1, -1, -1, -1, -1, 191, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, 74, -1, -1, -1, -1, -1, -1, -1, -1, 81, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 39, -1, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, 199, 185, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 55, 129, -1, 12, -1, -1, -1, 54, -1, 215
																				, -1, -1, -1, -1, -1, -1, -1, 115, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 94, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 145, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 75, -1, -1, -1, 138, -1, -1, 160, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, 162
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 180, -1, -1, -1, -1, -1, -1, -1, -1, 153, -1, -1, -1, -1, -1, -1, -1, 203, 88, -1, -1, -1, 42, -1, 50, -1, -1, 45, 80, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, 137, -1, -1, 73, 167, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 130, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, 71, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, -1, 90, -1, -1, -1, -1, -1, -1, 201, -1, -1, -1, -1, -1, -1, -1, -1
																				, 113, -1, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 156, -1, -1, -1, -1, -1, -1, -1, -1, -1, 61, -1, -1, 5, -1, 3, -1, 190, -1, -1, -1, -1, -1, -1, -1, 212, -1, -1
																				, 174, -1, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 178, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 83, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 87, -1
																				, -1, -1, -1, -1, -1, 98, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 193, -1, -1, -1, 21, -1, -1, 121, -1, -1, 214, -1, 84, 70, -1, -1, 47, -1, -1, -1, -1, -1, 38, -1, 16, -1, -1, -1, -1, -1, -1, 125, -1
																				, -1, -1, -1, -1, -1, 134, 181, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 154, 123, -1, -1, -1, -1, -1, 216, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, 206, -1, -1, -1, -1, -1, -1, -1, -1, 49, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1, 30, 213, -1, -1, -1, -1, -1, 46, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 118, -1, -1, -1, -1, -1, -1, -1, -1, 68, -1, -1, 136, -1, -1, -1, -1, -1, -1, -1, 6, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 135, -1
																				, -1, -1, 66, 105, -1, -1, 198, -1, -1, -1, -1, -1, -1, -1, -1, 172, -1, 19, -1, -1, 114, -1, -1, -1, -1, -1, -1, 175, -1, -1, -1, -1, -1, -1, -1, -1, 117, 194, -1, -1, 72, -1, -1, -1, -1, -1, 152
																				, -1, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, 15, -1, 171, -1, -1, 192, -1, 200, -1, -1, 148, -1, -1, 86, 76, 63, -1, 14, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 67, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1, 155, 184, -1, 97
																				, -1, -1, -1, -1, 149, -1, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, 163, -1, -1, -1, -1, -1, 210, -1, 44, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, -1, -1, -1, 108, -1, -1, -1, -1, -1, -1, 157, -1, -1, 142, -1, 7, 51, -1, 177, -1, -1, -1, -1, 69, -1, -1, -1, -1, -1, -1, -1, 22, -1, 127, 204, -1, -1, 158, -1, -1, -1, -1, -1, -1, -1
																				, -1, -1, -1, 140, -1, 179, -1, -1, -1, 58, -1, -1, 208, 139, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 92, 43, -1, -1, 110, 0, -1, -1, -1, 96, -1
																				, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 112, 126, 95, -1, -1, -1, -1, -1, 13, -1
																				, -1, -1, -1, -1, -1, 150, -1, -1, -1, -1, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 103, -1, -1, -1, -1, -1, -1, -1, -1, -1, 101, -1, 60};

__fastcall TSynLLVMIRSyn::TSynLLVMIRSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkBoolean),
			fBooleanAttri(nullptr),
			fCommentAttri(nullptr),
			fConstantAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInstructionAttri(nullptr),
			fKeyAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fLabelAttri(nullptr),
			fNumberAttri(nullptr),
			fTypesAttri(nullptr)
{
	FCaseSensitive = true;
	fBooleanAttri = new TSynHighlighterAttributes(SYNS_AttrBoolean, SYNS_FriendlyAttrBoolean);
	fBooleanAttri->Foreground = clNavy;
	addAttribute(fBooleanAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Foreground = (TColor) 0xB0A060;
	fCommentAttri->Style = Synhighlighterllvm__0;
	addAttribute(fCommentAttri);
	fConstantAttri = new TSynHighlighterAttributes(SYNS_AttrConstant, SYNS_FriendlyAttrConstant);
	fConstantAttri->Foreground = clNavy;
	addAttribute(fConstantAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	fIdentifierAttri->Foreground = (TColor) 0xD560BB;
	addAttribute(fIdentifierAttri);
	fInstructionAttri = new TSynHighlighterAttributes(SYNS_AttrInstructions, SYNS_FriendlyAttrInstructions);
	fInstructionAttri->Foreground = (TColor) 0x207000;
	fInstructionAttri->Style = Synhighlighterllvm__1;
	addAttribute(fInstructionAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Foreground = (TColor) 0x207000;
	fKeyAttri->Style = Synhighlighterllvm__2;
	addAttribute(fKeyAttri);
	fLabelAttri = new TSynHighlighterAttributes(SYNS_AttrLabel, SYNS_FriendlyAttrLabel);
	fLabelAttri->Foreground = (TColor) 0x702000;
	fLabelAttri->Style = Synhighlighterllvm__3;
	addAttribute(fLabelAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	fNumberAttri->Foreground = (TColor) 0x70A040;
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	fStringAttri->Foreground = (TColor) 0xA07040;
	addAttribute(fStringAttri);
	fTypesAttri = new TSynHighlighterAttributes(SYNS_AttrBasicTypes, SYNS_FriendlyAttrBasicTypes);
	fTypesAttri->Foreground = (TColor) 0x002090;
	fTypesAttri->Style = Synhighlighterllvm__4;
	addAttribute(fTypesAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterLLVMIR;
}

void __fastcall TSynLLVMIRSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 1552 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[1458] = FuncKey; // acq95rel
	fIdentFuncTable[659] = FuncKey; // acquire
	fIdentFuncTable[843] = FuncInstruction; // add
	fIdentFuncTable[916] = FuncKey; // addrspace
	fIdentFuncTable[1346] = FuncKey; // alias
	fIdentFuncTable[914] = FuncKey; // align
	fIdentFuncTable[1158] = FuncKey; // alignstack
	fIdentFuncTable[1385] = FuncInstruction; // alloca
	fIdentFuncTable[107] = FuncKey; // alwaysinline
	fIdentFuncTable[44] = FuncInstruction; // and
	fIdentFuncTable[372] = FuncKey; // appending
	fIdentFuncTable[32] = FuncInstruction; // arcp
	fIdentFuncTable[624] = FuncKey; // arm95aapcs95vfpcc
	fIdentFuncTable[1512] = FuncKey; // arm95aapcscc
	fIdentFuncTable[1261] = FuncKey; // arm95apcscc
	fIdentFuncTable[1244] = FuncInstruction; // ashr
	fIdentFuncTable[1019] = FuncKey; // asm
	fIdentFuncTable[359] = FuncKey; // atomic
	fIdentFuncTable[557] = FuncInstruction; // atomicrmw
	fIdentFuncTable[1191] = FuncKey; // available95externally
	fIdentFuncTable[1489] = FuncInstruction; // bitcast
	fIdentFuncTable[999] = FuncKey; // blockaddress
	fIdentFuncTable[1401] = FuncInstruction; // br
	fIdentFuncTable[337] = FuncKey; // byval
	fIdentFuncTable[366] = FuncKey; // c
	fIdentFuncTable[598] = FuncInstruction; // call
	fIdentFuncTable[179] = FuncKey; // catch
	fIdentFuncTable[1308] = FuncKey; // cc
	fIdentFuncTable[932] = FuncKey; // ccc
	fIdentFuncTable[1241] = FuncKey; // cleanup
	fIdentFuncTable[1115] = FuncInstruction; // cmpxchg
	fIdentFuncTable[1111] = FuncKey; // coldcc
	fIdentFuncTable[536] = FuncKey; // common
	fIdentFuncTable[145] = FuncKey; // constant
	fIdentFuncTable[723] = FuncKey; // datalayout
	fIdentFuncTable[458] = FuncKey; // declare
	fIdentFuncTable[238] = FuncKey; // default
	fIdentFuncTable[69] = FuncKey; // define
	fIdentFuncTable[1017] = FuncKey; // deplibs
	fIdentFuncTable[589] = FuncKey; // dllexport
	fIdentFuncTable[20] = FuncKey; // dllimport
	fIdentFuncTable[217] = FuncType; // double
	fIdentFuncTable[767] = FuncInstruction; // eq
	fIdentFuncTable[1454] = FuncInstruction; // exact
	fIdentFuncTable[1359] = FuncKey; // except
	fIdentFuncTable[772] = FuncKey; // extern95weak
	fIdentFuncTable[1122] = FuncKey; // external
	fIdentFuncTable[1011] = FuncInstruction; // extractelement
	fIdentFuncTable[889] = FuncInstruction; // extractvalue
	fIdentFuncTable[1090] = FuncInstruction; // fadd
	fIdentFuncTable[769] = FuncBoolean; // false
	fIdentFuncTable[1386] = FuncInstruction; // fast
	fIdentFuncTable[856] = FuncKey; // fastcc
	fIdentFuncTable[381] = FuncInstruction; // fcmp
	fIdentFuncTable[628] = FuncInstruction; // fdiv
	fIdentFuncTable[621] = FuncInstruction; // fence
	fIdentFuncTable[1525] = FuncKey; // filter
	fIdentFuncTable[434] = FuncType; // float
	fIdentFuncTable[1424] = FuncInstruction; // fmul
	fIdentFuncTable[456] = FuncType; // fp128
	fIdentFuncTable[1552] = FuncInstruction; // fpext
	fIdentFuncTable[911] = FuncInstruction; // fptosi
	fIdentFuncTable[130] = FuncInstruction; // fptoui
	fIdentFuncTable[1259] = FuncInstruction; // fptrunc
	fIdentFuncTable[19] = FuncInstruction; // free
	fIdentFuncTable[378] = FuncInstruction; // frem
	fIdentFuncTable[1176] = FuncInstruction; // fsub
	fIdentFuncTable[1299] = FuncKey; // gc
	fIdentFuncTable[1147] = FuncInstruction; // getelementptr
	fIdentFuncTable[1393] = FuncKey; // global
	fIdentFuncTable[1008] = FuncType; // half
	fIdentFuncTable[846] = FuncKey; // hidden
	fIdentFuncTable[1214] = FuncInstruction; // icmp
	fIdentFuncTable[789] = FuncInstruction; // inbounds
	fIdentFuncTable[563] = FuncInstruction; // indirectbr
	fIdentFuncTable[708] = FuncKey; // initialexec
	fIdentFuncTable[1258] = FuncKey; // inlinehint
	fIdentFuncTable[493] = FuncKey; // inreg
	fIdentFuncTable[180] = FuncInstruction; // insertelement
	fIdentFuncTable[57] = FuncInstruction; // insertvalue
	fIdentFuncTable[773] = FuncKey; // intel95ocl95bicc
	fIdentFuncTable[572] = FuncKey; // inteldialect
	fIdentFuncTable[828] = FuncKey; // internal
	fIdentFuncTable[965] = FuncInstruction; // inttoptr
	fIdentFuncTable[1007] = FuncInstruction; // invoke
	fIdentFuncTable[313] = FuncType; // label
	fIdentFuncTable[1257] = FuncInstruction; // landingpad
	fIdentFuncTable[977] = FuncKey; // linker95private
	fIdentFuncTable[763] = FuncKey; // linker95private95weak
	fIdentFuncTable[348] = FuncKey; // linker95private95weak95def95auto
	fIdentFuncTable[863] = FuncKey; // linkonce
	fIdentFuncTable[137] = FuncKey; // linkonce95odr
	fIdentFuncTable[1453] = FuncKey; // linkonce95odr95auto95hide
	fIdentFuncTable[198] = FuncInstruction; // load
	fIdentFuncTable[671] = FuncKey; // localdynamic
	fIdentFuncTable[1506] = FuncKey; // localexec
	fIdentFuncTable[1462] = FuncInstruction; // lshr
	fIdentFuncTable[1317] = FuncInstruction; // malloc
	fIdentFuncTable[984] = FuncInstruction; // max
	fIdentFuncTable[476] = FuncType; // metadata
	fIdentFuncTable[129] = FuncInstruction; // min
	fIdentFuncTable[1550] = FuncKey; // minsize
	fIdentFuncTable[1159] = FuncKey; // module
	fIdentFuncTable[1540] = FuncKey; // monotonic
	fIdentFuncTable[1103] = FuncKey; // msp43095intrcc
	fIdentFuncTable[1177] = FuncInstruction; // mul
	fIdentFuncTable[334] = FuncKey; // naked
	fIdentFuncTable[1229] = FuncInstruction; // nand
	fIdentFuncTable[1373] = FuncInstruction; // ne
	fIdentFuncTable[646] = FuncKey; // nest
	fIdentFuncTable[1457] = FuncInstruction; // ninf
	fIdentFuncTable[322] = FuncInstruction; // nnan
	fIdentFuncTable[1504] = FuncKey; // noalias
	fIdentFuncTable[879] = FuncKey; // nocapture
	fIdentFuncTable[1194] = FuncKey; // noimplicitfloat
	fIdentFuncTable[638] = FuncKey; // noinline
	fIdentFuncTable[196] = FuncKey; // nonlazybind
	fIdentFuncTable[1210] = FuncKey; // noredzone
	fIdentFuncTable[1138] = FuncKey; // noreturn
	fIdentFuncTable[248] = FuncKey; // nounwind
	fIdentFuncTable[285] = FuncInstruction; // nsw
	fIdentFuncTable[1002] = FuncInstruction; // nsz
	fIdentFuncTable[377] = FuncConstant; // null
	fIdentFuncTable[1057] = FuncInstruction; // nuw
	fIdentFuncTable[16] = FuncInstruction; // oeq
	fIdentFuncTable[1026] = FuncInstruction; // oge
	fIdentFuncTable[1505] = FuncInstruction; // ogt
	fIdentFuncTable[1403] = FuncInstruction; // ole
	fIdentFuncTable[329] = FuncInstruction; // olt
	fIdentFuncTable[622] = FuncInstruction; // one
	fIdentFuncTable[801] = FuncType; // opaque
	fIdentFuncTable[461] = FuncKey; // optsize
	fIdentFuncTable[207] = FuncInstruction; // or
	fIdentFuncTable[374] = FuncInstruction; // ord
	fIdentFuncTable[1033] = FuncKey; // personality
	fIdentFuncTable[1172] = FuncInstruction; // phi
	fIdentFuncTable[1150] = FuncType; // ppc95fp128
	fIdentFuncTable[786] = FuncKey; // private
	fIdentFuncTable[712] = FuncKey; // protected
	fIdentFuncTable[1428] = FuncInstruction; // ptrtoint
	fIdentFuncTable[1418] = FuncKey; // ptx95device
	fIdentFuncTable[507] = FuncKey; // ptx95kernel
	fIdentFuncTable[1383] = FuncKey; // readnone
	fIdentFuncTable[197] = FuncKey; // readonly
	fIdentFuncTable[427] = FuncKey; // release
	fIdentFuncTable[697] = FuncInstruction; // resume
	fIdentFuncTable[251] = FuncInstruction; // ret
	fIdentFuncTable[482] = FuncKey; // returns95twice
	fIdentFuncTable[1254] = FuncKey; // sanitize95address
	fIdentFuncTable[1322] = FuncKey; // sanitize95memory
	fIdentFuncTable[1519] = FuncKey; // sanitize95thread
	fIdentFuncTable[304] = FuncInstruction; // sdiv
	fIdentFuncTable[1220] = FuncKey; // section
	fIdentFuncTable[754] = FuncInstruction; // select
	fIdentFuncTable[1056] = FuncKey; // seq95cst
	fIdentFuncTable[1314] = FuncInstruction; // sext
	fIdentFuncTable[901] = FuncInstruction; // sge
	fIdentFuncTable[1380] = FuncInstruction; // sgt
	fIdentFuncTable[1407] = FuncInstruction; // shl
	fIdentFuncTable[447] = FuncInstruction; // shufflevector
	fIdentFuncTable[715] = FuncKey; // sideeffect
	fIdentFuncTable[351] = FuncKey; // signext
	fIdentFuncTable[729] = FuncKey; // singlethread
	fIdentFuncTable[1351] = FuncInstruction; // sitofp
	fIdentFuncTable[1278] = FuncInstruction; // sle
	fIdentFuncTable[204] = FuncInstruction; // slt
	fIdentFuncTable[86] = FuncInstruction; // spir95func
	fIdentFuncTable[790] = FuncInstruction; // spir95kernel
	fIdentFuncTable[54] = FuncInstruction; // srem
	fIdentFuncTable[174] = FuncKey; // sret
	fIdentFuncTable[397] = FuncKey; // ssp
	fIdentFuncTable[1246] = FuncKey; // sspreq
	fIdentFuncTable[1189] = FuncKey; // sspstrong
	fIdentFuncTable[223] = FuncInstruction; // store
	fIdentFuncTable[929] = FuncInstruction; // sub
	fIdentFuncTable[1201] = FuncInstruction; // switch
	fIdentFuncTable[1324] = FuncKey; // tail
	fIdentFuncTable[1388] = FuncKey; // target
	fIdentFuncTable[952] = FuncKey; // thread95local
	fIdentFuncTable[1420] = FuncKey; // to
	fIdentFuncTable[745] = FuncKey; // triple
	fIdentFuncTable[1034] = FuncBoolean; // true
	fIdentFuncTable[152] = FuncInstruction; // trunc
	fIdentFuncTable[50] = FuncInstruction; // type
	fIdentFuncTable[1315] = FuncInstruction; // udiv
	fIdentFuncTable[605] = FuncInstruction; // ueq
	fIdentFuncTable[62] = FuncInstruction; // uge
	fIdentFuncTable[541] = FuncInstruction; // ugt
	fIdentFuncTable[513] = FuncInstruction; // uitofp
	fIdentFuncTable[439] = FuncInstruction; // ule
	fIdentFuncTable[918] = FuncInstruction; // ult
	fIdentFuncTable[551] = FuncInstruction; // umax
	fIdentFuncTable[1249] = FuncInstruction; // umin
	fIdentFuncTable[995] = FuncConstant; // undef
	fIdentFuncTable[1211] = FuncInstruction; // une
	fIdentFuncTable[212] = FuncKey; // unnamed95addr
	fIdentFuncTable[495] = FuncInstruction; // uno
	fIdentFuncTable[426] = FuncKey; // unordered
	fIdentFuncTable[1180] = FuncInstruction; // unreachable
	fIdentFuncTable[604] = FuncInstruction; // unwind
	fIdentFuncTable[1251] = FuncInstruction; // urem
	fIdentFuncTable[870] = FuncKey; // uwtable
	fIdentFuncTable[530] = FuncInstruction; // va95arg
	fIdentFuncTable[762] = FuncType; // void
	fIdentFuncTable[1404] = FuncKey; // volatile
	fIdentFuncTable[258] = FuncKey; // weak
	fIdentFuncTable[1081] = FuncKey; // weak95odr
	fIdentFuncTable[318] = FuncKey; // x8695fastcallcc
	fIdentFuncTable[1427] = FuncType; // x8695fp80
	fIdentFuncTable[68] = FuncType; // x8695mmx
	fIdentFuncTable[1357] = FuncKey; // x8695stdcallcc
	fIdentFuncTable[94] = FuncKey; // x8695thiscallcc
	fIdentFuncTable[926] = FuncInstruction; // xchg
	fIdentFuncTable[1116] = FuncInstruction; // xor
	fIdentFuncTable[1005] = FuncKey; // zeroext
	fIdentFuncTable[630] = FuncConstant; // zeroinitializer
	fIdentFuncTable[1063] = FuncInstruction; // zext
}

/*$Q-*/

unsigned int __fastcall TSynLLVMIRSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 359 + int((*Str)) * 239);
		++Str;
	}
	result = (unsigned int) (result % 1553);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynLLVMIRSyn::FuncBoolean(int Index)
{
	TtkTokenKind result = tkBoolean;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBoolean;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::FuncConstant(int Index)
{
	TtkTokenKind result = tkBoolean;
	if(IsCurrentToken(Keywords[Index]))
		result = tkConstant;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::FuncInstruction(int Index)
{
	TtkTokenKind result = tkBoolean;
	if(IsCurrentToken(Keywords[Index]))
		result = tkInstruction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::FuncKey(int Index)
{
	TtkTokenKind result = tkBoolean;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::FuncType(int Index)
{
	TtkTokenKind result = tkBoolean;
	if(IsCurrentToken(Keywords[Index]))
		result = tkType;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkBoolean;
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkBoolean;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 1552 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynLLVMIRSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynLLVMIRSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynLLVMIRSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynLLVMIRSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynLLVMIRSyn::IntegerTypeProc()
{
	switch(fLine[Succ(Run)])
	{
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		{
			FTokenID = tkType;
			do
			{
				++Run;
				switch(fLine[Run])
				{
					case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
					;
					break;
					default:
					return;
					break;
				}
			}
			while(!IsLineEnd(Run));
		}
		break;
		default:
		IdentProc();
		break;
	}
}

void __fastcall TSynLLVMIRSyn::AtTypeProc()
{

  // @ = global identifiers
	FTokenID = tkUnknown;
	++Run;
	if(IsLineEnd(Run))
		return;
	switch(fLine[Run])
	{
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		FTokenID = tkUnnamedIdentifier;
		break;
		case L'-':
		case L'_':
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		FTokenID = tkIdentifier;
		break;
		case L'\"':
		{
			++Run;
			StringProc();
			FTokenID = tkIdentifier;
			return;
		}
		default:
		  ;
		break;
	}
	do
	{
		++Run;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'-':
			case L'_':
			case L'.':
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			;
			break;
			default:
			return;
			break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynLLVMIRSyn::PercentTypeProc()
{

  // % = local identifiers
	FTokenID = tkUnknown;
	++Run;
	if(IsLineEnd(Run))
		return;
	switch(fLine[Run])
	{
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		FTokenID = tkUnnamedIdentifier;
		break;
		case L'-':
		case L'_':
		case L'.':
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		FTokenID = tkIdentifier;
		break;
		case L'\"':
		{
			++Run;
			StringProc();
			FTokenID = tkIdentifier;
			return;
		}
		default:
		  ;
		break;
	}
	do
	{
		++Run;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'-':
			case L'_':
			case L'.':
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			;
			break;
			default:
			return;
			break;
		}
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynLLVMIRSyn::SingleCommentOpenProc()
{
	++Run;
	FRange = rsSingleComment;
	SingleCommentProc();
	FTokenID = tkComment;
}

void __fastcall TSynLLVMIRSyn::SingleCommentProc()
{
	FTokenID = tkComment;
	while(!IsLineEnd(Run))
		++Run;
}

void __fastcall TSynLLVMIRSyn::StringOpenProc()
{
	++Run;
	FRange = rsString;
	StringProc();
	FTokenID = tkString;
}

void __fastcall TSynLLVMIRSyn::StringProc()
{
	switch(fLine[Run])
	{
		case L'\x00':
		NullProc();
		break;
		case L'\x0a':
		LFProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		default:
		{
			FTokenID = tkString;
			do
			{
				if(fLine[Run] == L'\"')
				{
					Run += 1;
					FRange = rsUnKnown;
					break;
				}
				if(!IsLineEnd(Run))
					++Run;
			}
			while(!IsLineEnd(Run));
		}
		break;
	}
}

void __fastcall TSynLLVMIRSyn::NumberProc()
{

	auto IsNumberChar = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'.':
			case L'x':
			case L'X':
			case L'-':
			case L'+':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};

	auto IsDigitPlusMinusChar = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'+':
			case L'-':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};

	auto IsHexDigit = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case 65: case 66: case 67: case 68: case 69: case 70:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};

	auto IsAlphaUncerscore = [&](int Run) -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	int idx1 = 0; // token[1]
	int i = 0;
	idx1 = Run;
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar(Run))
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Succ(Run)] == L'.')
				goto label0;
			else
			{
				if(FTokenID != tkHex)
					FTokenID = tkFloat;
				else
 // invalid
				{
					FTokenID = tkUnknown;
					return;
				}
			}
			break;
			case L'-':
			case L'+':
			{
				if(FTokenID != tkFloat) // number <> float. an arithmetic operator
					return;
				if(!CharInSet(fLine[Pred(Run)], Synhighlighterllvm__5))
					return; // number = float, but no exponent. an arithmetic operator
				if(!IsDigitPlusMinusChar(Succ(Run))) // invalid
				{
					++Run;
					FTokenID = tkUnknown;
					return;
				}
			}
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			;
			break;
			case 97: case 98: case 99: case 100:
			case L'f':
			case 65: case 66: case 67: case 68:
			case L'F':
			if(FTokenID != tkHex)
				goto label1;
			break;
			case L'e':
			case L'E':
			if(FTokenID != tkHex)
			{
				if(CharInSet(fLine[Pred(Run)], Synhighlighterllvm__6)) // exponent
				{
					int stop = 0;
					for(stop = Pred(Run), i = idx1; i <= stop; i++)
					{
						if(CharInSet(fLine[i], Synhighlighterllvm__7)) // too many exponents
						{
							FTokenID = tkUnknown;
							return;
						}
					}
					if(!IsDigitPlusMinusChar(Succ(Run)))
						goto label2;
					else
						FTokenID = tkFloat;
				}
				else
				goto label3;
			}
			break;
			case L'x':
			case L'X':
			if((Run == Succ(idx1)) && (fLine[idx1] == L'0') && IsHexDigit(Succ(Run)))   // 0x... 'x' must be second char
  // 0x...
 // 0x... must be continued with a number
				FTokenID = tkHex;
			else
 // invalid char
			{
				if(!IsIdentChar(fLine[Succ(Run)]) && CharInSet(fLine[Succ(idx1)], Synhighlighterllvm__8))
				{
					++Run; // highlight 'x' too
					FTokenID = tkUnknown;
				}
				goto label4;
			}
			break;
			default:
			  ;
			break;
		} // case
		++Run;
	} // while
	label0:;
	label1:;
	label2:;
	label3:;
	label4:;
	if(IsAlphaUncerscore(Run))
		FTokenID = tkUnknown;
}

void __fastcall TSynLLVMIRSyn::IdentProc()
{
	FTokenID = IdentKind(fLine + Run);
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
	if(fLine[Run] == L':')
	{
		FTokenID = tkLabel;
		++Run;
	}
}

void __fastcall TSynLLVMIRSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynLLVMIRSyn::Next()
{
	fTokenPos = Run;
	switch(FRange)
	{
		case rsString:
		StringProc();
		break;
		default:
		switch(fLine[Run])
		{
			case L'\x00':
			NullProc();
			break;
			case L'\x0a':
			LFProc();
			break;
			case L'\x0d':
			CRProc();
			break;
			case L';':
			SingleCommentOpenProc();
			break;
			case L'\"':
			StringOpenProc();
			break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
			case L'\x0b':
			case L'\x0c':
			case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
			 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
			SpaceProc();
			break;
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			NumberProc();
			break;
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104:
			case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115:
			 case 116: case 117: case 118: case 119: case 120: case 121: case 122:
			case L'_':
			IdentProc();
			break;
			case L'i':
			IntegerTypeProc();
			break;
			case L'@':
			AtTypeProc();
			break;
			case L'%':
			PercentTypeProc();
			break;
			default:
			UnknownProc();
			break;
		}
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynLLVMIRSyn::GetDefaultAttribute(int Index)
{
	TSynHighlighterAttributes* result = nullptr;
	switch(Index)
	{
		case SYN_ATTR_COMMENT:
		result = fCommentAttri;
		break;
		case SYN_ATTR_IDENTIFIER:
		result = fIdentifierAttri;
		break;
		case SYN_ATTR_KEYWORD:
		result = fKeyAttri;
		break;
		case SYN_ATTR_STRING:
		result = fStringAttri;
		break;
		case SYN_ATTR_WHITESPACE:
		result = fSpaceAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynLLVMIRSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

UnicodeString __fastcall TSynLLVMIRSyn::GetKeyWords(int TokenKind)
{
	UnicodeString result;
	result = L"acq_rel,acquire,add,addrspace,alias,align,alignstack,alloca,alwaysinl"
	           L"ine,and,appending,arcp,arm_aapcs_vfpcc,arm_aapcscc,arm_apcscc,ashr,asm"
	           L",atomic,atomicrmw,available_externally,bitcast,blockaddress,br,byval,c"
	           L",call,catch,cc,ccc,cleanup,cmpxchg,coldcc,common,constant,datalayout,d"
	           L"eclare,default,define,deplibs,dllexport,dllimport,double,eq,exact,exce"
	           L"pt,extern_weak,external,extractelement,extractvalue,fadd,false,fast,fa"
	           L"stcc,fcmp,fdiv,fence,filter,float,fmul,fp128,fpext,fptosi,fptoui,fptru"
	           L"nc,free,frem,fsub,gc,getelementptr,global,half,hidden,icmp,inbounds,in"
	           L"directbr,initialexec,inlinehint,inreg,insertelement,insertvalue,intel_"
	           L"ocl_bicc,inteldialect,internal,inttoptr,invoke,label,landingpad,linker"
	           L"_private,linker_private_weak,linker_private_weak_def_auto,linkonce,lin"
	           L"konce_odr,linkonce_odr_auto_hide,load,localdynamic,localexec,lshr,mall"
	           L"oc,max,metadata,min,minsize,module,monotonic,msp430_intrcc,mul,naked,n"
	           L"and,ne,nest,ninf,nnan,noalias,nocapture,noimplicitfloat,noinline,nonla"
	           L"zybind,noredzone,noreturn,nounwind,nsw,nsz,null,nuw,oeq,oge,ogt,ole,ol"
	           L"t,one,opaque,optsize,or,ord,personality,phi,ppc_fp128,private,protecte"
	           L"d,ptrtoint,ptx_device,ptx_kernel,readnone,readonly,release,resume,ret,"
	           L"returns_twice,sanitize_address,sanitize_memory,sanitize_thread,sdiv,se"
	           L"ction,select,seq_cst,sext,sge,sgt,shl,shufflevector,sideeffect,signext"
	           L",singlethread,sitofp,sle,slt,spir_func,spir_kernel,srem,sret,ssp,sspre"
	           L"q,sspstrong,store,sub,switch,tail,target,thread_local,to,triple,true,t"
	           L"runc,type,udiv,ueq,uge,ugt,uitofp,ule,ult,umax,umin,undef,une,unnamed_"
	           L"addr,uno,unordered,unreachable,unwind,urem,uwtable,va_arg,void,volatil"
	           L"e,weak,weak_odr,x86_fastcallcc,x86_fp80,x86_mmx,x86_stdcallcc,x86_this"
	           L"callcc,xchg,xor,zeroext,zeroinitializer,zext";
	return result;
}

TtkTokenKind __fastcall TSynLLVMIRSyn::GetTokenID()
{
	TtkTokenKind result = tkBoolean;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynLLVMIRSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkBoolean:
		result = fBooleanAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkConstant:
		result = fConstantAttri;
		break;
		case tkIdentifier:
		case tkUnnamedIdentifier:
		result = fIdentifierAttri;
		break;
		case tkInstruction:
		result = fInstructionAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkLabel:
		result = fLabelAttri;
		break;
		case tkNumber:
		case tkFloat:
		case tkHex:
		result = fNumberAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkType:
		result = fTypesAttri;
		break;
		case tkUnknown:
		result = fIdentifierAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynLLVMIRSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

bool __fastcall TSynLLVMIRSyn::IsIdentChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case L'_':
		case L'.':
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}

UnicodeString __fastcall TSynLLVMIRSyn::GetSampleSource()
{
	UnicodeString result;
	result = L"; Declare the string constant as global constant"
	           L"\x0a\x0d"
	           L"@.msg = "
	           L"internal constant [13 x i8] c\"Hello World!\\00\""
	           L"\x0a\x0d"
	           L"\x0a\x0d"
	           L"; External declaration of puts function"
	           L"\x0a\x0d"
	           L"declare i32 "
	           L"@puts(i8*)"
	           L"\x0a\x0d"
	           L"\x0a\x0d"
	           L"; Definition of main function"
	           L"\x0a\x0d"
	           L"define i32 @main() {"
	           L"\x0a\x0d"
	           L"entry:"
	           L"\x0a\x0d"
	           L"\x09"
	           L"; Convert [13 x i8]* to i8 *..."
	           L"\x0a\x0d"
	           L"\x09"
	           L"%cast210 = getelementptr inbounds ([13 x i8]* @.msg, i32 0, i32 0)"
	           L"\x0a\x0d"
	           L"\x0a\x0d"
	           L"\x09"
	           L"; Call puts function to write out the string to "
	           L"stdout"
	           L"\x0a\x0d"
	           L"\x09"
	           L"call i32 @puts(i8* %cast210)"
	           L"\x0a\x0d"
	           L"\x09"
	           L"ret i32 0"
	           L"\x0a\x0d"
	           L"}";
	return result;
}

bool __fastcall TSynLLVMIRSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterLLVMIR;
	return result;
}

/*#static*/
UnicodeString __fastcall TSynLLVMIRSyn::GetFriendlyLanguageName()
{
	UnicodeString result;
	result = SYNS_FriendlyLangLLVMIR;
	return result;
}

/*#static*/
String __fastcall TSynLLVMIRSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangLLVMIR;
	return result;
}

void __fastcall TSynLLVMIRSyn::ResetRange()
{
	FRange = rsUnKnown;
}

void __fastcall TSynLLVMIRSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void* __fastcall TSynLLVMIRSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}
static bool SynHighlighterLLVM_Initialized = false;

void SynHighlighterLLVM_initialization()
{
	if(SynHighlighterLLVM_Initialized)
		return;
	
	SynHighlighterLLVM_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynLLVMIRSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterLLVM

