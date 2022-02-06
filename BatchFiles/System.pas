
(*
    Copyright of the basic file version
    -----------------------------------

    Explanation: in the following license "library" means
    the following files: 
    
    System.pas / d2c_system.pas
    System.h
    d2c_sysconst.h
    d2c_syscurr.h d2c_syscurr.cpp
    d2c_sysdate.h d2c_sysdate.cpp
    d2c_sysexcept.h d2c_sysexcept.cpp
    d2c_sysfile.h, d2c_sysfile.cpp 
    d2c_sysstring.h d2c_sysstring.cpp
    d2c_systypes.h
    d2c_varrec.h
    d2c_smallstring.h
    Windows.pas
    Sysutils.pas
    Sysutils.h Sysutils.cpp

    AS THEY ARE CONTAINED IN THE FREE TRIAL VERSION OF Delphi2Cpp.

    This library is derived from the FreePascal library:

    http://www.freepascal.org/

    FreePascal is published under the terms of GNU Lesser General
    Public License and the same terms apply to this library.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with d2c_sysfile.h/cpp; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



    Copyright of the extended file version
    --------------------------------------


    The terms of the license above don't apply to extended versions
    of these files, which are distributed with commercial versions of 
    Delphi2Cpp. Individual licenses are applied to them. 
    The library doesn't depend on the commercial extensions and the 
    the commercial extensions only originates from the author
    Dr. Detlef Meyer-Eltz or might use code which has no copyright restrictions

    Copyright (C) <2011>  <Dr. Detlef Meyer-Eltz>

    The extended version of this file is authorized for unlimited use in any 
    Delphi2Cpp project.
	     
	  http://www.texttransformer.com/Delphi2Cpp_en.html

*)


unit System;

interface

//error at test of single files 
//uses Windows; 


const MaxInt = High(Integer);
const MaxLongInt = High(LongInt);

// http://docs.embarcadero.com/products/rad_studio/delphiAndcpp2009/HelpUpdate2/EN/html/delphivclwin32/System.html
//procedure Abs(X);
procedure Abs(X: Integer);
function AcquireExceptionObject: Pointer;
procedure AddModuleUnloadProc(Proc: TModuleUnloadProc); overload;
procedure AddModuleUnloadProc(Proc: TModuleUnloadProcLW); overload;
function Addr(var X): Pointer;
function AllocMem(Size: Cardinal): Pointer;
function AnsiToUtf8(const S: string): RawByteString;
//procedure Append(var F: Text);
procedure Append(F: Text);
function ArcTan(const X: Extended): Extended;
procedure Assert(expr: Boolean); overload;
procedure Assert(expr: Boolean; const msg: string); overload;
function Assigned(const P): Boolean;
//procedure AssignFile(var F; FileName: string);
procedure AssignFile(F: File; FileName: string);
function AttemptToUseSharedMemoryManager: Boolean;
function BeginThread(SecurityAttributes: Pointer; StackSize: LongWord; ThreadFunc: TThreadFunc; Parameter: Pointer; CreationFlags: LongWord; var ThreadId: LongWord): Integer;
//procedure BlockRead(var F: File; var Buf; Count: Integer); overload;
//procedure BlockRead(var F: File; var Buf; Count: Integer; var AmtTransferred: Integer); overload;
//procedure BlockWrite(var f: File; var Buf; Count: Integer); overload;
//procedure BlockWrite(var f: File; var Buf; Count: Integer; var AmtTransferred: Integer); overload;
procedure BlockRead(F: File; var Buf; Count: Integer); overload;
procedure BlockRead(F: File; var Buf; Count: Integer; var AmtTransferred: Integer); overload;
procedure BlockWrite(f: File; var Buf; Count: Integer); overload;
procedure BlockWrite(f: File; var Buf; Count: Integer; var AmtTransferred: Integer); overload;
//procedure Break;
procedure ChDir(const S: string); overload;
procedure ChDir(P: PChar); overload;
procedure CheckSafecallResult(hr: HRESULT);
function Chr(X: Byte): Char;
//procedure Close(var F);
//procedure CloseFile(var F);
procedure Close(F: File);
procedure CloseFile(F: File);
function CompToCurrency(Value: Comp): Currency; cdecl;
function CompToDouble(Value: Comp): Double; cdecl;
function Concat(s1: string): string; overload;
function Concat(s1: string; s2: string): string; overload;
function Concat(s1: string; s2: string; s3: string): string; overload;
//procedure Continue;
//function Copy(S; Index: Integer; Count: Integer): array; overload;
function Copy(S : String; Index: Integer; Count: Integer): array; overload;
function Cos(const X: Extended): Extended;
procedure CurrencyToComp(Value: Currency; var Result: Comp); cdecl;
procedure Dec(var X); overload;
procedure Dec(var X; N: Longint); overload;
procedure Delete(var S: string; Index: Integer; Count: Integer);
procedure Dispose(var P: Pointer);
procedure DoubleToComp(Value: Double; var Result: Comp); cdecl;
procedure DynArrayClear(var a: Pointer; typeInfo: Pointer);
function DynArrayDim(typeInfo: PDynArrayTypeInfo): Integer;
procedure DynArraySetLength(var a: Pointer; typeInfo: Pointer; dimCnt: Longint; lengthVec: PLongint);
procedure EndThread(ExitCode: Integer);
procedure EnumModules(Func: TEnumModuleFunc; Data: Pointer); overload;
procedure EnumModules(Func: TEnumModuleFuncLW; Data: Pointer); overload;
procedure EnumResourceModules(Func: TEnumModuleFunc; Data: Pointer); overload;
procedure EnumResourceModules(Func: TEnumModuleFuncLW; Data: Pointer); overload;
function Eof: Boolean; overload;
//function Eof(var F): Boolean; overload;
function Eof(F: File): Boolean; overload;
function Eof(F: Text): Boolean; overload;
function Eoln: Boolean; overload;
//function Eoln(var F: Text): Boolean; overload;
function Eoln(F: Text): Boolean; overload;
//procedure Erase(var F);
procedure Erase(F: File);
procedure Error(errorCode: TRuntimeError);
function ExceptAddr: Pointer;
function ExceptObject: TObject;
// todo procedure Exclude(var S: set of T; I: T);
procedure Exit;
function Exp(X: Real): Real;
function Exp(const X: Extended): Extended;
//function FilePos(var F): Longint;
//function FileSize(var F): Integer;
function FilePos(F: File): Longint;
function FileSize(F: File): Integer;
procedure FillChar(var X; Count: Integer; Value: Byte);
procedure Finalize(var V); overload;
procedure Finalize(var V; Count: Integer); overload;
function FindClassHInstance(ClassType: TClass): LongWord;
function FindDynaInst(var vmt; ID: Integer): Pointer;
function FindHInstance(Address: Pointer): LongWord;
function FindResourceHInstance(Instance: LongWord): LongWord;
function Flush(var t: Text): Integer;
procedure FPower10;
function Frac(const X: Extended): Extended;
procedure FreeMem(var P: Pointer); overload;
procedure FreeMem(var P: Pointer; Size: Integer); overload;
function FreeMemory(P: Pointer): Integer; cdecl;
function Get8087CW: Word;
procedure GetDir(D: Byte; var S: string);
function GetHeapStatus: THeapStatus; deprecated; platform;
function GetLastError: Integer; stdcall;
procedure GetMem(var P: Pointer; Size: Integer);
function GetMemory(Size: Integer): Pointer; cdecl;
procedure GetMemoryManager(var MemMgr: TMemoryManager); overload; deprecated;
procedure GetMemoryManager(var MemMgrEx: TMemoryManagerEx); overload;
procedure GetMemoryManagerState(var AMemoryManagerState: TMemoryManagerState);
procedure GetMemoryMap(var AMemoryMap: TMemoryMap);
function GetMinimumBlockAlignment: TMinimumBlockAlignment;
function GetModuleFileName(Module: HMODULE; Buffer: PChar; BufLen: Integer): Integer;
procedure GetVariantManager(var VarMgr: TVariantManager); deprecated;
procedure Halt; overload;
procedure Halt(Exitcode: Integer); overload;
//function Hi(X): Byte;
function Hi(X: Integer): Byte;
//procedure High(X);
procedure Inc(var X); overload;
procedure Inc(var X; N: Longint); overload;
// todo procedure Include(var S: set of T; I: T);
procedure Initialize(var V); overload;
procedure Initialize(var V; Count: Integer); overload;
procedure Insert(Source: string; var S: string; Index: Integer);
function Int(const X: Extended): Extended;
function IOResult: Integer;
function IsMemoryManagerSet: Boolean;
//function Length(S): Integer;
function Length(S: String): Integer;
function Ln(const X: Extended): Extended;
//function Lo(X): Byte;
function Lo(X: Integer): Byte;
function LoadResourceModule(ModuleName: PChar; CheckOwner: Boolean = True): LongWord;
//function LoadResourceString(rsrc: ResourceString const * const): String;
function LoadResourceString(rsrc: String): String;
function LoadResString(ResStringRec: PResStringRec): string;
//procedure Low(X);
procedure Low(X: Integer);
procedure Mark; deprecated;
procedure MemoryBarrier;
procedure MkDir(const S: string); overload;
procedure MkDir(P: PChar); overload;
function MonitorEnter(AObject: TObject; Timeout: Cardinal = INFINITE): Boolean;
procedure MonitorExit(AObject: TObject);
procedure MonitorPulse(AObject: TObject);
procedure MonitorPulseAll(AObject: TObject);
function MonitorTryEnter(AObject: TObject): Boolean;
function MonitorWait(AObject: TObject; Timeout: Cardinal): Boolean;

// line 2431
procedure Move(const Source; var Dest; Count: Integer);
procedure MoveChars(const Source; var Dest; Length: Integer);
function ParamCount: Integer;
function ParamStr(Index: Integer): string;
procedure RmDir(const S: string); overload;
procedure RmDir(P: PChar); overload;

// line 2440
{ random functions }
procedure Randomize;
function Random(const ARange: Integer): Integer; overload;
function Random: Extended; overload;

// line 2606
function PUCS4Chars(const S: UCS4String): PUCS4Char;
function RaiseList: Pointer; deprecated;


// line 2661
{ OLE string support procedures and functions }

function OleStrToString(Source: PWideChar): UnicodeString;
procedure OleStrToStrVar(Source: PWideChar; var Dest: AnsiString); overload;
procedure OleStrToStrVar(Source: PWideChar; var Dest: UnicodeString); overload;

// line 3790
{ string utilities }
function Pos(const substr: UnicodeString; const str: UnicodeString): Integer; overload;
function Pos(const substr: RawByteString; const str: RawByteString): Integer; overload;
function Pos(const substr: WideString; const str: WideString): Integer; overload;


// builtin functions (dme)
function Round(const Number : Extended ): Int64; // dme
procedure New(var P: Pointer); // dme
function Odd(X: Integer): Boolean; // dme
procedure Ord(X: Integer); // dme
procedure Pred(X: Integer); // dme
function Ptr(Address: Integer): Pointer; // dme
//procedure Read(F; V1); overload;
//procedure Read(F; V1; Vn); overload;
//procedure Read(F: Text; V1); overload;
//procedure Read(F: Text; V1; Vn); overload;
procedure Read(F: File; V1: String); overload;
procedure Read(F: File; V1: String; Vn: String); overload;
procedure Read(F: Text; V1: String); overload;
procedure Read(F: Text; V1: String; Vn: String); overload;
//procedure ReadLn(V1); overload;
//procedure ReadLn(V1; Vn); overload;
procedure ReadLn(V1: String); overload;
procedure ReadLn(V1: String; Vn: String); overload;
//procedure ReadLn(var F: Text; V1); overload;
//procedure ReadLn(var F: Text; V1; Vn); overload;
procedure ReadLn(F: Text; V1: String); overload;
procedure ReadLn(F: Text; V1: String; Vn: String); overload;
procedure ReallocMem(var P: Pointer; Size: Integer);
function ReallocMemory(P: Pointer; Size: Integer): Pointer; cdecl;
function RegisterExpectedMemoryLeak(P: Pointer): boolean;
procedure RegisterModule(LibModule: PLibModule);
procedure Release; deprecated;
procedure ReleaseExceptionObject;
procedure RemoveModuleUnloadProc(Proc: TModuleUnloadProc); overload;
procedure RemoveModuleUnloadProc(Proc: TModuleUnloadProcLW); overload;
//procedure Rename(var F; Newname: string); overload;
//procedure Rename(var F; Newname: PChar); overload;
//procedure Reset(var F); overload;
//procedure Reset(var F; RecSize: Word); overload;
//procedure Reset(var F: File); overload;
//procedure Reset(var F: File; RecSize: Word); overload;
//procedure Rewrite(var F: File); overload;
//procedure Rewrite(var F: File; Recsize: Word); overload;
procedure Rename(F: File; Newname: string); overload;
procedure Rename(F: File; Newname: PChar); overload;
procedure Reset(F: File); overload;
procedure Reset(F: File; RecSize: Word); overload;
procedure Reset(F: File); overload;
procedure Reset(F: File; RecSize: Word); overload;
procedure Rewrite(F: File); overload;
procedure Rewrite(F: File; Recsize: Word); overload;
function Round(X: Extended): Int64;
procedure RunError; overload;
procedure RunError(Errorcode: Byte); overload;
//procedure Seek(var F; N: Longint);
procedure Seek(F: File; N: Longint);
function SeekEof: Boolean; overload;
//function SeekEof(var F: Text): Boolean; overload;
function SeekEof(F: Text): Boolean; overload;
function SeekEoln: Boolean; overload;
//function SeekEoln(var F: Text): Boolean; overload;
function SeekEoln(F: Text): Boolean; overload;
procedure Set8087CW(NewCW: Word);
procedure SetCodePage(var S: RawByteString; CodePage: Word; Convert: Boolean = True);
procedure SetInOutRes(NewValue: Integer);
procedure SetLastError(ErrorCode: Integer); stdcall;
//procedure SetLength(var S; NewLength: Integer);
procedure SetLength(S: String; NewLength: Integer);
procedure SetLineBreakStyle(var T: Text; Style: TTextLineBreakStyle);
procedure SetMemoryManager(const MemMgr: TMemoryManager); overload; deprecated;
procedure SetMemoryManager(const MemMgrEx: TMemoryManagerEx); overload;
procedure SetMinimumBlockAlignment(AMinimumBlockAlignment: TMinimumBlockAlignment);
procedure SetMultiByteConversionCodePage(CodePage: Integer);
function SetRaiseList(NewPtr: Pointer): Pointer; deprecated;
procedure SetString(var s: string; buffer: PChar; len: Integer);
//procedure SetTextBuf(var F: Text; var Buf); overload;
//procedure SetTextBuf(var F: Text; var Buf; Size: Integer); overload;
procedure SetTextBuf(F: Text; var Buf); overload;
procedure SetTextBuf(F: Text; var Buf; Size: Integer); overload;
procedure SetVariantManager(const VarMgr: TVariantManager); deprecated;
function ShareMemoryManager: Boolean;
function Sin(const X: Extended): Extended;
//function SizeOf(X): Integer;
function SizeOf(X: Integer): Integer;
// todo function Slice(var A: array; Count: Integer): array;
function Sqr(X: Extended): Extended; overload;
function Sqr(X: Integer): Integer; overload;
function Sqrt(const X: Extended): Extended;
procedure Str(X: Width; var S); overload;
procedure Str(X: Decimals; var S); overload;
function StringCodePage(const S: UnicodeString): Word; overload;
function StringCodePage(const S: RawByteString): Word; overload;
function StringElementSize(const S: UnicodeString): Word; overload;
function StringElementSize(const S: RawByteString): Word; overload;
function StringOfChar(ch: AnsiChar; Count: Integer): AnsiString; overload;
function StringOfChar(ch: WideChar; Count: Integer): UnicodeString; overload;
function StringRefCount(const S: UnicodeString): Longint; overload;
function StringRefCount(const S: RawByteString): Longint; overload;
function StringToOleStr(const Source: AnsiString): PWideChar; overload;
function StringToOleStr(const Source: UnicodeString): PWideChar; overload;
function StringToWideChar(const Source: UnicodeString; Dest: PWideChar; DestSize: Integer): PWideChar;
//procedure Succ(X);
//procedure Swap(X);
procedure Succ(X: Integer);
//procedure Swap(X: Integer);
function Swap(X: Integer): Integer;
function Swap(X: Word): Word;
function SysAllocMem(Size: Cardinal): Pointer;
function SysRegisterExpectedMemoryLeak(P: Pointer): Boolean;
function SysFreeMem(P: Pointer): Integer;
function SysGetMem(Size: Integer): Pointer;
function SysReallocMem(P: Pointer; Size: Integer): Pointer;
function SysRegisterExpectedMemoryLeak(P: Pointer): Boolean;
function SysUnregisterExpectedMemoryLeak(P: Pointer): Boolean;
procedure TextStart; deprecated;
function Trunc(X: Extended): Int64;
//procedure Truncate(var F);
procedure Truncate(F: File);
function UCS4StringToUnicodeString(const S: UCS4String): UnicodeString;
function UCS4StringToWideString(const S: UCS4String): WideString;
function UnicodeStringToUCS4String(const S: UnicodeString): UCS4String;
function UnicodeToUtf8(Dest: PChar; MaxDestBytes: Cardinal; Source: PWideChar; SourceChars: Cardinal): Cardinal; overload;
function UnicodeToUtf8(Dest: PChar; Source: PWideChar; MaxBytes: Integer): Integer; overload; deprecated;
function UnicodeToUtf8(Dest: PAnsiChar; Source: PWideChar; MaxBytes: Integer): Integer; overload; deprecated;
function UnicodeToUtf8(Dest: PAnsiChar; MaxDestBytes: Cardinal; Source: PWideChar; SourceChars: Cardinal): Cardinal; overload;
procedure UniqueString(var str: AnsiString); overload;
procedure UniqueString(var str: WideString); overload;
procedure UniqueString(var str: UnicodeString); overload;
function UTF8ToUnicodeString(const S: RawByteString): UnicodeString; overload;
function UTF8ToUnicodeString(const S: ShortString): UnicodeString; overload;
function UTF8ToUnicodeString(const S: PAnsiChar): UnicodeString; overload;
function UTF8ToWideString(const S: RawByteString): WideString;
//procedure Val(S: String; var V; var Code: Integer);
procedure Val(S: String; var V: AnsiChar; var Code: Integer);
procedure Val(S: String; var V: ShortInt; var Code: Integer);
procedure Val(S: String; var V: SmallInt; var Code: Integer);
procedure Val(S: String; var V: Word; var Code: Integer);
procedure Val(S: String; var V: Cardinal; var Code: Integer);
procedure Val(S: String; var V: Integer; var Code: Integer);
procedure Val(S: String; var V: Int64; var Code: Integer);
procedure Val(S: String; var V: UInt64; var Code: Integer);
procedure Val(S: String; var V: Single; var Code: Integer);
procedure Val(S: String; var V: Double; var Code: Integer);
procedure Val(S: String; var V : Extended; var Code: Integer);
procedure VarArrayRedim(A: Variant; HighBound: Integer);
procedure VarClear(V: Variant);
function WideCharLenToString(Source: PWideChar; SourceLen: Integer): UnicodeString;
procedure WideCharLenToStrVar(Source: PWideChar; SourceLen: Integer; var Dest: UnicodeString); overload;
procedure WideCharLenToStrVar(Source: PWideChar; SourceLen: Integer; var Dest: AnsiString); overload;
function WideCharToString(Source: PWideChar): UnicodeString;
procedure WideCharToStrVar(Source: PWideChar; var Dest: UnicodeString);
function WideStringToUCS4String(const S: WideString): UCS4String;
//procedure Write(P1); overload;
//procedure Write(P1; Pn); overload;
procedure Write(P1: String); overload;
procedure Write(P1: String; Pn: String); overload;
//procedure Write(var F: Text; P1); overload;
//procedure Write(var F: Text; P1; Pn); overload;
procedure Write(F: Text; P1: String); overload;
procedure Write(F: Text; P1: String; Pn: String); overload;
//procedure WriteLn(P1); overload;
//procedure WriteLn(P1; Pn); overload;
procedure WriteLn(P1: String); overload;
procedure WriteLn(P1: String; Pn: String); overload;
//procedure WriteLn(var F: Text; P1); overload;
//procedure WriteLn(var F: Text; P1; Pn); overload;
procedure WriteLn(F: Text; P1: String); overload;
procedure WriteLn(F: Text; P1: String; Pn: String); overload;
procedure YieldProcessor;

function charLen(p: PChar) : Integer;


implementation


end.
