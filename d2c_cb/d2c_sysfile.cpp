#include <vcl.h>
#pragma hdrstop

/*
    Copyright (C) <2019>  <Dr. Detlef Meyer-Eltz>
    ---------------------------------------------

    this file is authorized for unlimited use in any
    project created with Delphi2C# or DelphiXE2Cpp11.

    http://www.texttransformer.com/
*/



#include "sysmac.h"
#include "d2c_sysfile.h"
//#include "d2c_system.h"
//#include <Sysutils.hpp>
#include <sstream>
#include <iomanip>
#include <limits>


#undef max

using namespace std;


namespace d2c_system
{

typedef unsigned char* PByte;
const int TextRecNameLength = 256;
const int TextRecBufSize = 256;
const int FilerecNameLength = 255;
HANDLE UnusedHandle = ((HANDLE) - 1 );
HANDLE StdInputHandle = 0;
HANDLE StdOutputHandle = 0;
HANDLE StdErrorHandle = 0;
bool FileNameCaseSensitive = true;
bool CtrlZMarksEOF = true; /* #26 is considered as end of File */
TTextLineBreakStyle DefaultTextLineBreakStyle = tlbsCRLF;

WORD InOutRes = 0;

Set <wchar_t, 0, 255 > AllowDirectorySeparators = ( Set <wchar_t, 0, 255 >() << _T('\\') <<  _T('/') );
Set <wchar_t, 0, 255 > AllowDriveSeparators = ( Set <wchar_t, 0, 255 >() << _T(':') );

TTextRec ErrOutput, Output, Input, Stdout, Stderr;
unsigned char FileMode = 2;


const char ctlbsLF[] = "\x0a";
const char ctlbsCRLF[] = "\x0d\x0a";
const char ctlbsCR[] = "\x0d";


AnsiString wstr2str(const wchar_t* xp)
{
  return AnsiString(xp);
}

AnsiString wstr2str(const WideString& xs)
{
  return xs;
}

#if (__BORLANDC__ >= 0x0610)
AnsiString wstr2str(const UnicodeString& xs)
{
  return xs;
}
#endif

WideString str2wstr(const AnsiString& xs)
{
  return xs;
}

char wchar2char(wchar_t xc)
{
  return (char) xc;
}

wchar_t char2wchar(char xc)
{
   return (wchar_t) xc;
}

void StrCpy(char* pDest, const char* pSource)
{
  strcpy(  pDest, pSource);
}

void StrCpy(wchar_t* pDest, const wchar_t* pSource)
{
  wcscpy(  pDest, pSource);
}

void StrnCpy(char* pDest, const char* pSource, int len)
{
  strncpy(  pDest, pSource, len);
}

void StrnCpy(wchar_t* pDest, const wchar_t* pSource, int len)
{
  wcsncpy(  pDest, pSource, len);
}

char* strcpy_max(char* pDest, const char* pSource, int SourceLen, int High)
{
  int len = ((SourceLen > High) ? High : SourceLen);
  strncpy(  pDest, pSource, len);
  pDest[len] = '\0';
  return pDest;
}

int StrLen(const char* p)
{
  return strlen(p);
}

int StrLen(const wchar_t* p)
{
  return wcslen(p);
}

wchar_t* strcpy_max(wchar_t* pDest, const wchar_t* pSource, int SourceLen, int High)
{
  int len = ((SourceLen > High) ? High : SourceLen);
  wcsncpy(  pDest, pSource, len);
  pDest[len] = L'\0';
  return pDest;
}

bool do_isdevice( HANDLE Handle )
{
  bool result = false;
  result = ( GetFileType( (void*) Handle ) == 2 );
  return result;
}

void do_close( HANDLE h )
{
  if ( do_isdevice( h ) )
    return;
  CloseHandle( (void*) h );
}

void Errno2InOutRes( )
{
  WORD res = 0;
  int* pErrno = NULL;
     /* DO NOT MODIFY UNLESS YOU KNOW EXACTLY WHAT YOU ARE DOING */
  pErrno = &errno;
  switch ( *pErrno )
  {
    case ERROR_WRITE_PROTECT:
    case ERROR_BAD_UNIT:
    case ERROR_NOT_READY:
    case ERROR_BAD_COMMAND:
    case ERROR_CRC:
    case ERROR_BAD_LENGTH:
    case ERROR_SEEK:
    case ERROR_NOT_DOS_DISK:
    case ERROR_SECTOR_NOT_FOUND:
    case ERROR_OUT_OF_PAPER:
    case ERROR_WRITE_FAULT:
    case ERROR_READ_FAULT:
    case ERROR_GEN_FAILURE:
    {
           /* This is the offset to the Win32 to add to directly map  */
           /* to the DOS/TP compatible error codes when in this range */
      res = ((WORD) *pErrno ) + 131;
    }
    break;
    case ERROR_DIR_NOT_EMPTY:
    case ERROR_ALREADY_EXISTS:
    case ERROR_SHARING_VIOLATION:
    {
      res = 5;
    }
    break;
  default:
  {
           /* other error codes can directly be mapped */
    res = ((WORD) *pErrno );
  }
  }
  *pErrno = 0;
  InOutRes = res;
}

int64_t do_seekend( HANDLE Handle )
{
  int64_t result;
  if (( SetFilePointerEx != NULL ) )
  {
    LARGE_INTEGER li;
    li.QuadPart = 0;
    LARGE_INTEGER li2;
    if ( ! ( SetFilePointerEx( (void*) Handle, li, &li2, FILE_END ) ) )
    {
      errno = GetLastError();
      Errno2InOutRes();
    }
    result = li2.QuadPart;
  }
  else
  {
//      do_seekend:=SetFilePointer(handle,0,nil,FILE_END);
//      if do_seekend=-1 then
    result = SetFilePointer( (void*) Handle, 0, NULL, FILE_END );
    if ( result == - 1 )
    {
      errno = GetLastError();
      Errno2InOutRes();
    }
  }
  return result;
}

void DoDirSeparators( char* P )
{
  unsigned int i = 0;
  for ( i = 0; i <= strlen( P ); i++)
    if (P[i] == '\\' || P[i] == '/' )
      P[i] = DirectorySeparator;
}

void DoDirSeparators( wchar_t* P )
{
  unsigned int i = 0;
  for ( i = 0; i <= wcslen( P ); i++)
    if (P[i] == L'\\' || P[i] == L'/' )
      P[i] = DirectorySeparator;
}

void Do_Open( void* f, Char* P, int Flags )
/*
  filerec and textrec have both handle and mode as the first items so
  they could use the same routine for opening/creating.
  when (flags and $100)   the file will be append
  when (flags and $1000)  the file will be truncate/rewritten
  when (flags and $10000) there is no check for close (needed for textfiles)
*/
{
  // in winnt.h const int FILE_SHARE_READ = 0x00000001;
  // in winnt.h const int FILE_SHARE_WRITE = 0x00000002;
  int shflags = 0, oflags = 0, cd = 0;
  SECURITY_ATTRIBUTES security;
  DoDirSeparators( P );
  /* close first if opened */
  if ( ( ( Flags & 0x10000 ) ) == 0 )
  {
    switch ( ((TFileRec*) f )->Mode )
    {
      case fmInput:
      case fmOutput:
      case fmInOut:
        do_close( ((TFileRec*) f )->Handle );
      break;
      case fmClosed:
      break;
    default:
    {
        /*not assigned*/
      InOutRes = 102;
      return;
    }
    }
  }
  /* reset file handle */
  ((TFileRec*) f )->Handle = UnusedHandle;
  /* convert filesharing */
  shflags = 0;
  if ( ( FileMode & fmShareExclusive ) == fmShareExclusive )
    ;/* no sharing */
  else
    if ( ( FileMode == fmShareCompat ) || ( ( ( FileMode & fmShareDenyWrite ) ) == fmShareDenyWrite ) )
      shflags = FILE_SHARE_READ;
    else
      if ( ( ( FileMode & fmShareDenyRead ) ) == fmShareDenyRead )
        shflags = FILE_SHARE_WRITE;
      else
        if ( ( ( FileMode & fmShareDenyNone ) ) == fmShareDenyNone )
          shflags = FILE_SHARE_READ + FILE_SHARE_WRITE;
  /* convert FileMode to filerec modes */
  switch ( Flags & 3 )
  {
    case 0:
    {
      ((TFileRec*) f )->Mode = fmInput;
      oflags = ((int) GENERIC_READ );
    }
    break;
    case 1:
    {
      ((TFileRec*) f )->Mode = fmOutput;
      oflags = ((int) GENERIC_WRITE );
    }
    break;
    case 2:
    {
      ((TFileRec*) f )->Mode = fmInOut;
      oflags = ((int) ( GENERIC_WRITE | GENERIC_READ ) );
    }
    break;
  }
  /* create it ? */
  if ( ( ( Flags & 0x1000 ) ) != 0 )
    cd = CREATE_ALWAYS;
  /* or Append/Open ? */
  else
    cd = OPEN_EXISTING;
  /* empty name is special */
  if ( P[0] == _T('\x00') )
  {
    switch ( ((TFileRec*) f )->Mode )
    {
      case fmInput:
        ((TFileRec*) f )->Handle = StdInputHandle;
      break;
      case fmInOut:
      case /* this is set by rewrite */ fmOutput:
        ((TFileRec*) f )->Handle = StdOutputHandle;
      break;
      case fmAppend:
      {
        ((TFileRec*) f )->Handle = StdOutputHandle;
        ((TFileRec*) f )->Mode = fmOutput; /*fool fmappend*/
      }
      break;
    }
    return;
  }
  security.nLength = sizeof( SECURITY_ATTRIBUTES );
  security.bInheritHandle = true;
  security.lpSecurityDescriptor = NULL;
	((TFileRec*) f )->Handle = CreateFileW(P, oflags, shflags, &security, cd, FILE_ATTRIBUTE_NORMAL, 0 );

	/* append mode */
  if ( ( ( ( Flags & 0x100 ) ) != 0 ) && ( ((TFileRec*) f )->Handle != 0 ) && ( ((TFileRec*) f )->Handle != UnusedHandle ) )
  {
    do_seekend( ((TFileRec*) f )->Handle );
    ((TFileRec*) f )->Mode = fmOutput; /*fool fmappend*/
  }

  /* get errors */
  /* handle -1 is returned sometimes !! (PM) */
  if ( ( ((TFileRec*) f )->Handle == 0 ) || ( ((TFileRec*) f )->Handle == UnusedHandle ) )
  {
    errno = GetLastError();
    Errno2InOutRes();
  }
}

void do_erase( char* P )
{
  DoDirSeparators( P );
   // if DeleteFile(p)=0 then
  if ( /*# windows::*/ DeleteFileA( P ) == ((BOOL) 0 ) )   // dme
  {
    errno = GetLastError();
    if ( errno == 5 )
    {
      if ( ( ( GetFileAttributesA( P ) & FILE_ATTRIBUTE_DIRECTORY ) ) == FILE_ATTRIBUTE_DIRECTORY )
        errno = 2;
    }
    Errno2InOutRes();
  }
}

void do_erase( wchar_t* P )
{
  DoDirSeparators( P );
   // if DeleteFile(p)=0 then
  if ( /*# windows::*/ DeleteFileW( P ) == ((BOOL) 0 ) )   // dme
  {
    errno = GetLastError();
    if ( errno == 5 )
    {
      if ( ( ( GetFileAttributesW( P ) & FILE_ATTRIBUTE_DIRECTORY ) ) == FILE_ATTRIBUTE_DIRECTORY )
        errno = 2;
    }
    Errno2InOutRes();
  }
}

void do_rename( Char* p1, Char* p2 )
{
  DoDirSeparators( p1 );
  DoDirSeparators( p2 );
//  if MoveFile(p1,p2)=0 then
	if ( /*# windows::*/ MoveFileW( p1, p2 ) == ((BOOL) 0 ) )   // dme
  {
    errno = GetLastError();
    Errno2InOutRes();
  }
}


int do_write(HANDLE h, void* addr, int Len )
{
  int result = 0;
  DWORD size = 0;
  if ( WriteFile( (void*) h, addr, Len, &size, NULL ) == ((BOOL) 0 ) )
  {
    errno = GetLastError();
    Errno2InOutRes();
  }
  result = size;
  return result;
}

int do_read( HANDLE h, void* addr, int Len )
{
  int result = 0;
  DWORD _result = 0;
  if ( ReadFile( (void*) h, addr, Len, &_result, NULL ) == ((BOOL) 0 ) )
  {
    errno = GetLastError();
    if ( errno == ERROR_BROKEN_PIPE )
      errno = 0;
    else
      Errno2InOutRes();
  }
  result = _result;
  return result;
}

int64_t do_filepos( HANDLE Handle )
{
  int64_t result;
  int l = 0;
	if (( SetFilePointerEx != NULL ) )
  {
    LARGE_INTEGER li;
    li.QuadPart = 0;
    LARGE_INTEGER liResult;

    if ( ! ( SetFilePointerEx( (void*) Handle, li, &liResult, FILE_CURRENT ) ) )
    {
      errno = GetLastError();
      Errno2InOutRes();
    }
		result = liResult.QuadPart;
  }
  else
  {
    l = SetFilePointer( (void*) Handle, 0, NULL, FILE_CURRENT );
    if ( l == - 1 )
    {
      l = 0;
      errno = GetLastError();
      Errno2InOutRes();
    }
    result = l;
  }
  return result;
}

void do_seek( HANDLE Handle, int64_t Pos )
{
  if (( SetFilePointerEx != NULL ) )
  {
    LARGE_INTEGER li;
    li.QuadPart = 0;
    LARGE_INTEGER liPos;
    liPos.QuadPart = Pos;
    if ( ! ( SetFilePointerEx( (void*) Handle, liPos, &li, FILE_BEGIN ) ) )
    {
      errno = GetLastError();
      Errno2InOutRes();
    }
  }
  else
  {
    if ( SetFilePointer( (void*) Handle, (long) Pos, NULL, FILE_BEGIN ) == ((DWORD) - 1 ) )
    {
      errno = GetLastError();
      Errno2InOutRes();
    }
  }
}
int64_t do_filesize( HANDLE Handle )
{
  int64_t result = 0;
  int64_t aktfilepos = 0;
  aktfilepos = do_filepos( Handle );
  result = do_seekend( Handle );
  do_seek( Handle, aktfilepos );
  return result;
}
void do_truncate( HANDLE Handle, int64_t Pos )
{
  do_seek( Handle, Pos );
  if ( ! ( SetEndOfFile( (void*) Handle ) ) )
  {
    errno = GetLastError();
    Errno2InOutRes();
  }
}

void FileCloseFuncA( TTextRec& t )
{
  do_close( t.Handle );
  t.Handle = UnusedHandle;
}

void FileReadFuncA( TTextRec& t )
{
  t.BufEnd = do_read( t.Handle, t.BufPtr, t.BufSize );
  t.BufPos = 0;
}

void FileWriteFuncA( TTextRec& t )
{
  unsigned int i = 0;
  /* prevent unecessary system call */
  if ( t.BufPos == 0 )
    return;
  i = do_write( t.Handle, t.BufPtr, t.BufPos );
  if ( i != t.BufPos )
    InOutRes = 101;
  t.BufPos = 0;
}

void FileOpenFuncA( TTextRec& t )
{
  int Flags = 0;
  switch ( t.Mode )
  {
    case fmInput:
      Flags = 0x10000;
    break;
    case fmOutput:
      Flags = 0x11001;
    break;
    case fmAppend:
      Flags = 0x10101;
    break;
  default:
  {
    InOutRes = 102;
    return;
  }
  }
  Do_Open( &t, t.Name, Flags );
  t.CloseFunc = (void*) FileCloseFuncA;
  t.FlushFunc = NULL;
  if ( t.Mode == fmInput )
    t.InOutFunc = (void*) FileReadFuncA;
  else
  {
    t.InOutFunc = (void*) FileWriteFuncA;
   /* Only install flushing if its a NOT a file, and only check if there
     was no error opening the file, becuase else we always get a bad
     file handle error 6 (PFV) */
    if ( ( InOutRes == 0 ) && do_isdevice( t.Handle ) )
      t.FlushFunc = (void*) FileWriteFuncA;
  }
}


void CloseFile( TFileRec& f )
/*
  CloseFile file f
*/
{
  if ( InOutRes != 0 )
    return;
  switch ( f.Mode )
  {
    case fmInOut:
    case fmInput:
    case fmOutput:
    {
      do_close( f.Handle );
      f.Mode = fmClosed;
    }
    break;
  default:
    InOutRes = 103;
  }
}


void Close( TFileRec& f )
{
  CloseFile(f);
}

void CloseFile( TTextRec& t )
{
  if ( InOutRes != 0 )
    return;
  switch ( t.Mode )
  {
    case fmInput:
    case fmOutput:
    case fmAppend:
    {
        /* Write pending buffer */
      if ( t.Mode == fmOutput )
        FileFunc( t.InOutFunc )( t );
        /* Only close functions not connected to Stdout.*/
      if ( ( t.Handle != StdInputHandle ) && ( t.Handle != StdOutputHandle ) && ( t.Handle != StdErrorHandle ) )
        FileFunc( t.CloseFunc )( t );
      t.Mode = fmClosed;
        /* Reset buffer for safety */
      t.BufPos = 0;
      t.BufEnd = 0;
    }
    break;
  default:
    InOutRes = 103;
  }
}


void Close( TTextRec& t )
{
  CloseFile(t);
}

void OpenText( TTextRec& t, int Mode, int defHdl )
{
  switch ( t.Mode )
  {
    case fmInput: /*This gives the fastest code*/
    case fmOutput:
    case fmInOut:
      CloseFile( t );
    break;
    case fmClosed:
    break;
  default:
  {
    InOutRes = 102;
    return;
  }
  }
  t.Mode = Mode;
  t.BufPos = 0;
  t.BufEnd = 0;
  FileFunc( t.OpenFunc )( t );
  /* reset the mode to closed when an error has occured */
  if ( InOutRes != 0 )
    t.Mode = fmClosed;
}


int64_t FilePos( TFileRec& f, int l)
/*
  Return current Position In file f in records
*/
{
  int64_t result = 0;
  result = 0;
  if ( InOutRes != 0 )
    return result;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case fmInOut: case fmInput: case fmOutput:
      result = do_filepos( f.Handle ) / l; //((TFileRec*) &f )->RecSize;
    break;
  default:
    InOutRes = 103;
  }
  return result;
}


int64_t FileSize( TFileRec& f )
/*
  Return the size of file f in records
*/
{
  int64_t result = 0;
  result = 0;
  if ( InOutRes != 0 )
    return result;
  switch ( f.Mode )
  {
    case fmInOut: case fmInput: case fmOutput:
    {
      if ( f.RecSize > 0 )
        result = do_filesize( f.Handle ) / f.RecSize;
    }
    break;
  default:
    InOutRes = 103;
  }
  return result;
}



bool Eof( TFileRec& f, int l )
/*
  Return True if we're at the end of the file f, else False is returned
*/
{
  bool result = false;
  result = false;
  if ( InOutRes != 0 )
    return result;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case
    /*Can't use do_ routines because we need record support*/ fmInOut: case fmInput: case fmOutput:
      result = ( FileSize( f ) <= FilePos( f, l ) );
    break;
  default:
    InOutRes = 103;
  }
  return result;
}



bool Eof( TTextRec& t ) 
{
  bool result = false;
  result = true;
  if ( InOutRes != 0 )
    return result; //(true);
  if ( t.Mode != fmInput )
  {
    if ( t.Mode == fmOutput )
      InOutRes = 104;
    else
      InOutRes = 103;
    return result; //(true);
  }
  if ( t.BufPos >= t.BufEnd )
  {
    FileFunc( t.InOutFunc )( t );
    if ( t.BufPos >= t.BufEnd )
      return result; //(true);
  }
  result = CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' );
  return result;
}


bool Eof( ) 
{
  bool result = false;
  result = Eof( Input );
  return result;
}


void Seek( TTypedFile<unsigned char>& f, int64_t Pos )
/*
  Goto record Pos in file f
*/
{
  if ( InOutRes != 0 )
    return;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case fmInOut: case fmInput: case fmOutput:
      do_seek( ((TFileRec*) &f )->Handle, Pos * ((TFileRec*) &f )->RecSize );
    break;
  default:
    InOutRes = 103;
  }
}


void Truncate( TFileRec& f, int RecSize )
/*
  Truncate/Cut file f at the current record Position
*/
{
  if ( InOutRes != 0 )
    return;
  switch ( f.Mode )
  {
    case fmInOut: case fmOutput:
      do_truncate( f.Handle, FilePos( f, RecSize ) * RecSize);
    break;
  default:
    InOutRes = 103;
  }
}


void Erase( TTypedFile<unsigned char>& f )
{
  if ( InOutRes != 0 )
    return;
  if ( ((TFileRec*) &f )->Mode == fmClosed )
    do_erase( (Char*) ( &((TFileRec*) &f )->Name[0] ) );
}

void Rename( TTypedFile<unsigned char>& f, Char* P )
{
  if ( InOutRes != 0 )
    return;
  if ( f.Mode == fmClosed )
  {
    String s = P;
    do_rename( f.Name, (Char*) s.c_str() );
     /* check error code of do_rename */
    if ( InOutRes == 0 )
      StrCpy( f.Name, s.c_str() );
  }
}


void Rename( TTypedFile<unsigned char>& f, const Char* xp )
{
  Char p[ FilerecNameLength + 1 ];
  strcpy_max(p, xp, StrLen(xp), FilerecNameLength);
  Rename( f, p );
}

void Rename( TTypedFile<unsigned char>& f, const AnsiString s )
{
  char P[ FilerecNameLength + 1 ];
  if ( InOutRes != 0 )
    return;
  strcpy_max(P, s.c_str(), s.Length(), FilerecNameLength);
  Rename( f, (const Char*) P );
}

void Rename( TTypedFile<unsigned char>& f, Char c )
{
  char P[ 2/*# range 0..1*/ ];
  if ( InOutRes != 0 )
    return;
  P[0] = c;
  P[1] = '\x00';
  Rename( f, (const Char*) P );
}

void Rename( TTextRec& t, Char* P )
{
  if ( InOutRes != 0 )
    return;
  if ( t.Mode == fmClosed )
  {
    String s = P;
    do_rename( t.Name, (Char*) s.c_str());
     /* check error code of do_rename */
    if ( InOutRes == 0 )
    {
      StrCpy( t.Name, s.c_str() );
    }
  }
}

void Rename( TTextRec& t, const Char* xp )
{
  Char p[ 256 ];
  StrnCpy(p, xp, 255);
  Rename( t, p );
}

void Rename( TTextRec& t, const String s )
{
  Char P[ FilerecNameLength + 1 ];
  if ( InOutRes != 0 )
    return;
  strcpy_max(P, s.c_str(), s.Length(), FilerecNameLength);
  Rename( t, P );
}

void Rename( TTextRec& t, Char c ) 
{
  Char P[ 2/*# range 0..1*/ ];
  if ( InOutRes != 0 )
    return;
  P[0] = c;
  P[1] = _T('\x00');
  Rename( t, P);
}

void Rewrite( TFileRec& f, int l ) 
/*
  Create file f with recordsize of l
*/
{
  if ( InOutRes != 0 )
    return;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case fmInOut: case fmInput: case fmOutput:
      CloseFile( f );
    break;
    case fmClosed:
    break;
  default:
  {
    InOutRes = 102;
    return;
  }
  }
  if ( l == 0 )
    InOutRes = 2;
  else
  {
     /* Reopen with FileMode 2, to be Tp compatible (PFV) */
    Do_Open( &f, f.Name, 0x1002 );
    f.RecSize = l;
  }
}


void Rewrite( TFileRec& f ) 
/*
  Create file with (default) 128 byte records
*/
{
  if ( InOutRes != 0 )
    return;
  Rewrite( f, 128 );
}


void Rewrite( TTextRec& t ) 
{
  if ( InOutRes != 0 )
    return;
  OpenText( t, fmOutput, 1 );
}


void Reset( TFileRec& f, int l ) 
/*
  Open file f with recordsize of l and FileMode
*/
{
  if ( InOutRes != 0 )
    return;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case fmInOut: case fmInput: case fmOutput:
      CloseFile( f );
    break;
    case fmClosed:
    break;
  default:
  {
    InOutRes = 102;
    return;
  }
  }
  if ( l == 0 )
    InOutRes = 2;
  else
  {
    Do_Open( &f, f.Name, FileMode );
    f.RecSize = l;
  }
}


void Reset( TFileRec& f )
/*
  Open file with (default) 128 byte records
*/
{
  if ( InOutRes != 0 )
    return;
  Reset( f, 128 );
}

void Reset( TTextRec& t ) 
{
  if ( InOutRes != 0 )
    return;
  OpenText( t, fmInput, 0 );
}


int GetFileHandle( file& F )
{
  return (int) ((TFileRec*) &F )->Handle;
}


int GetFileHandle( TTextRec& F )
{
  return (int) ((TTextRec*) &F )->Handle;
}


void BlockWrite64( TTypedFile<unsigned char>& f, void* buf, int64_t Count, int64_t& Result ) 
/*
  Write Count records from Buf to file f, return written records in result
*/
{
  Result = 0;
  if ( InOutRes != 0 )
    return;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case fmInOut: 
	case fmOutput:
      Result = do_write( ((TFileRec*) &f )->Handle, buf, (int) Count * ((TFileRec*) &f )->RecSize ) / ((TFileRec*) &f )->RecSize;
    break;
    case fmInput:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}

void BlockWrite( TTypedFile<unsigned char>& f, void* buf, int Count, int64_t& Result ) 
/*
  Write Count records from Buf to file f, return written records in result
*/
{
  BlockWrite64( f, buf, Count, Result );
}


void BlockWrite( TTypedFile<unsigned char>& f, void* buf, int Count, int& Result ) 
/*
  Write Count records from Buf to file f, return written records in result
*/
{
  int64_t l = 0;
  BlockWrite64( f, buf, Count, l );
  Result = (int) l;
}

void BlockWrite( TTypedFile<unsigned char>& f, void* buf, WORD Count, WORD& Result ) 
/*
  Write Count records from Buf to file f, return written records in Result
*/
{
  int64_t l = 0;
  BlockWrite64( f, buf, Count, l );
  Result = (WORD) l;
}

void BlockWrite( TTypedFile<unsigned char>& f, void* buf, unsigned int Count, unsigned int& Result ) 
/*
  Write Count records from Buf to file f, return written records in Result
*/
{
  int64_t l = 0;
  BlockWrite64( f, buf, Count, l );
  Result = (unsigned int) l;
}

void BlockWrite( TTypedFile<unsigned char>& f, void* buf, WORD Count, int& Result ) 
/*
  Write Count records from Buf to file f, return written records in Result
*/
{
  int64_t l = 0;
  BlockWrite64( f, buf, Count, l );
  Result = (int) l;
}

void BlockWrite( TTypedFile<unsigned char>& f, void* buf, int Count ) 
/*
  Write Count records from Buf to file f, if none a Read and Count>0 then
  InOutRes is set
*/
{
  int64_t result = 0;
  BlockWrite64( f, buf, Count, result );
  if ( ( InOutRes == 0 ) && ( result < Count ) && ( Count > 0 ) )
    InOutRes = 101;
}



void BlockRead64( TTypedFile<unsigned char>& f, void* buf, int64_t Count, int64_t& Result )
/*
  Read Count records from file f ro Buf, return number of read records in
  Result
*/
{
  Result = 0;
  if ( InOutRes != 0 )
    return;
  switch ( ((TFileRec*) &f )->Mode )
  {
    case fmInOut: 
	case fmInput:
      Result = do_read( ((TFileRec*) &f )->Handle, buf, (int) Count * ((TFileRec*) &f )->RecSize ) / ((TFileRec*) &f )->RecSize;
    break;
    case fmOutput:
      InOutRes = 104;
    break;
  default:
    InOutRes = 103;
  }
}

void BlockRead( TTypedFile<unsigned char>& f, void* buf, int Count, int64_t& Result ) 
/*
  Read Count records from file f ro Buf, return number of read records in
  Result
*/
{
  BlockRead64( f, buf, Count, Result );
}

void BlockRead( TTypedFile<unsigned char>& f, void* buf, int Count, int& Result ) 
/*
  Read Count records from file f ro Buf, return number of read records in
  Result
*/
{
  int64_t l = 0;
  BlockRead64( f, buf, Count, l );
  Result = (int)l;
}

void BlockRead( TTypedFile<unsigned char>& f, void* buf, WORD Count, WORD& Result ) 
/*
  Read Count records from file f to Buf, return number of read records in
  Result
*/
{
  int64_t l = 0;
  BlockRead64( f, buf, Count, l );
  Result = (WORD) l;
}

void BlockRead( TTypedFile<unsigned char>& f, void* buf, unsigned int Count, unsigned int& Result ) 
/*
  Read Count records from file f to Buf, return number of read records in
  Result
*/
{
  int64_t l = 0;
  BlockRead64( f, buf, Count, l );
  Result = (unsigned int) l;
}

void BlockRead( TTypedFile<unsigned char>& f, void* buf, WORD Count, int& Result ) 
/*
  Read Count records from file f to Buf, return number of read records in
  Result
*/
{
  int64_t l = 0;
  BlockRead64( f, buf, Count, l );
  Result = (int) l;
}


void BlockRead( TTypedFile<unsigned char>& f, void* buf, int64_t Count ) 
/*
  Read Count records from file f to Buf, if none are read and Count>0 then
  InOutRes is set
*/
{
  int64_t result = 0;
  BlockRead64( f, buf, Count, result );
  if ( ( InOutRes == 0 ) && ( result < Count ) && ( Count > 0 ) )
    InOutRes = 100;
}


SmallString<255> fpc_pchar_to_shortstr( char* P )
{
  SmallString<255> result;
  int l = 0;
  SmallString<255> s;
  if ( P == NULL )
    l = 0;
  else
    l = strlen( P );
  if ( l > 255 )
    l = 255;
  if ( l > 0 )
  {
    strncpy(&s[1], P, l);
    s[l] = '\0';
  }
  s[0] = char( l );
  result = s;
  return result;
} 


void AssignFile( TTextRec& t, const String Name )
{
  memset(&t, 0, sizeof(TTextRec));
/* only set things that are not zero */
  t.Handle = UnusedHandle;
  t.Mode = fmClosed;
  t.BufSize = TextRecBufSize;
  t.BufPtr = &t.Buffer[0];
  t.OpenFunc = (void*) FileOpenFuncA;
  switch ( DefaultTextLineBreakStyle )
  {
    case tlbsLF:
      StrCpy(t.LineEnd, ctlbsLF);
    break;
    case tlbsCRLF:
      StrCpy(t.LineEnd, ctlbsCRLF);
    break;
  }
  StrCpy(  t.Name, Name.c_str());
}

void AssignFile( TTextRec& t, Char c )
{
  String s;
  s += c;
  AssignFile( t, s.c_str());
}

void Assign( TTextRec& f, const String Name )
{
  AssignFile(f, Name);
}

void Assign( TTextRec& t, Char c ) 
{
  AssignFile(t, c);
}


void Append( TTextRec& t )
{
  if ( InOutRes != 0 )
    return;
  OpenText( t, fmAppend, 1 );
}

void Flush( TTextRec& t )
{
  if ( InOutRes != 0 )
    return;
  if ( t.Mode != fmOutput )
  {
    if ( t.Mode == fmInput )
      InOutRes = 105;
    else
      InOutRes = 103;
    return;
  }
/* Not the FlushFunc but the InOutFunc should be used, becuase that
  writes the data, FlushFunc doesn't need to be assigned */
  FileFunc( t.InOutFunc )( t );
}


void Erase( TTextRec& t ) 
{
  if ( InOutRes != 0 )
    return;
  if ( t.Mode == fmClosed )
    do_erase( t.Name );
}

bool SeekEof( TTextRec& t ) 
{
  bool result = false;
  int64_t oldfilepos = 0;
  int oldbufpos = 0, oldbufend = 0;
  int reads = 0;
  bool isdevice = false;
  result = true;
  if ( InOutRes != 0 )
    return result; //(true);
  if ( t.Mode != fmInput )
  {
    if ( t.Mode == fmOutput )
      InOutRes = 104;
    else
      InOutRes = 103;
    return result; //(true);
  }
  /* try to save the current position in the file, seekeof() should not move */
  /* the current file position (JM)                                          */
  oldbufpos = t.BufPos;
  oldbufend = t.BufEnd;
  reads = 0;
  oldfilepos = - 1;
  isdevice = do_isdevice( t.Handle );
  do
  {
    if ( t.BufPos >= t.BufEnd )
    {
       /* signal that the we will have to do a seek */
      reads++;
      if ( ! isdevice && ( reads == 1 ) )
      {
        oldfilepos = do_filepos( t.Handle ) - t.BufEnd;
        InOutRes = 0;
      }
      FileFunc( t.InOutFunc )( t );
      if ( t.BufPos >= t.BufEnd )
      {
          /* if we only did a read in which we didn't read anything, the */
          /* old buffer is still valid and we can simply restore the     */
          /* pointers (JM)                                               */
        reads--;
        result = true;
        break;
      }
    }
    switch ( t.BufPtr[t.BufPos] )
    {
      case '\x1a':
        if ( CtrlZMarksEOF )
        {
          result = true;
          break;
        }
      break;
      case '\x0a': case '\x0d': case '\x09': case ' ':
      break;
    default:
    {
      result = false;
      break;
    }
    }
    t.BufPos++;
  }
  while ( ! ( false ) );
  /* restore file position if not working with a device */
	if ( ! isdevice )
	{
    /* if we didn't modify the buffer, simply restore the BufPos and BufEnd  */
    /* (the latter becuase it's now probably set to zero because nothing was */
    /*  was read anymore)                                                    */
    if ( reads == 0 )
    {
      t.BufPos = oldbufpos;
      t.BufEnd = oldbufend;
    }
    /* otherwise return to the old filepos and reset the buffer */
    else
    {
      do_seek( t.Handle, oldfilepos );
      InOutRes = 0;
      FileFunc( t.InOutFunc )( t );
      t.BufPos = oldbufpos;
		}
	}
  return result;
}


bool SeekEof( ) 
{
  bool result = false;
  result = SeekEof( Input );
  return result;
}


bool EoLn( TTextRec& t ) 
{
  bool result = false;
  result = true;
  if ( InOutRes != 0 )
    return result; //(true);
  if ( t.Mode != fmInput )
  {
    if ( t.Mode == fmOutput )
      InOutRes = 104;
    else
      InOutRes = 103;
    return result; //(true);
  }
  if ( t.BufPos >= t.BufEnd )
  {
    FileFunc( t.InOutFunc )( t );
    if ( t.BufPos >= t.BufEnd )
      return result; //(true);
  }
  if ( CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' ) )
    return result; // (true);
  result = ( t.BufPtr[t.BufPos] == '\n' || t.BufPtr[t.BufPos] == '\r' );
  return result;
}


bool EoLn(  ) 
{
  bool result = false;
  result = EoLn( Input );
  return result;
}


bool SeekEoLn( TTextRec& t ) 
{
  bool result = false;
  result = true;
  if ( InOutRes != 0 )
    return result; //(true);
  if ( t.Mode != fmInput )
  {
    if ( t.Mode == fmOutput )
      InOutRes = 104;
    else
      InOutRes = 103;
    return result; //(true);
  }
  do
  {
    if ( t.BufPos >= t.BufEnd )
    {
      FileFunc( t.InOutFunc )( t );
      if ( t.BufPos >= t.BufEnd )
        return result; //(true);
    }
    switch ( t.BufPtr[t.BufPos] )
    {
      case '\x1a':
        if ( CtrlZMarksEOF )
          return result;
      break;// (true);

      case '\x0a': case '\x0d':
        return result;
      //break; //(true);

      case '\x09': case ' ':
      break;
    default:
      result = false;
      return result; //(false);
    }
    t.BufPos++;
  }
  while ( ! ( false ) );
  //return result;
}


bool SeekEoLn(  ) 
{
  bool result = false;
  result = SeekEoLn( Input );
  return result;
}


void SetTextBuf( TTextRec& t, void* buf, int size )

{
  t.BufPtr = (char*) buf;
  t.BufSize = size;
  t.BufPos = 0;
  t.BufEnd = 0;
}


void SetTextLineEnding( TTextRec& t, const AnsiString Ending )
{
  strcpy(t.LineEnd, Ending.c_str());
}


TTextRec* fpc_get_input( )
{
  return &Input;
}


TTextRec* fpc_get_output( )
{
  return &Output;
}


/******************************************************************************
                               Write(Ln)
******************************************************************************/

void fpc_WriteBuffer( TTextRec& t, const void* b, int Len )

{
  char* P = NULL;
  int Left = 0, idx = 0;
  P = (char*) b;
  idx = 0;
  Left = t.BufSize - t.BufPos;
  while ( Len > Left )
  {
    memcpy( &t.BufPtr[t.BufPos], &P[idx], Left );
    Len -= Left;
    idx += Left;
    t.BufPos += Left;
    FileFunc( t.InOutFunc )( t );
    Left = t.BufSize - t.BufPos;
  }
  memcpy( &t.BufPtr[t.BufPos], &P[idx], Len );
  t.BufPos += Len;
}


void fpc_WriteBlanksA( TTextRec& t, int Len )
{
  int Left = 0;
  Left = t.BufSize - t.BufPos;
  while ( Len > Left )
  {
    memset(&t.BufPtr[t.BufPos], ' ', Left);
    Len -= Left;
    t.BufPos += Left;
    FileFunc( t.InOutFunc )( t );
    Left = t.BufSize - t.BufPos;
  }
  memset(&t.BufPtr[t.BufPos], ' ', Len);
  t.BufPos += Len;
}

void fpc_Write_End( TTextRec& t )
{
  if ( t.FlushFunc != NULL )
    FileFunc( t.FlushFunc )( t );
}

void fpc_Writeln_End( TTextRec& t )
{
  if ( InOutRes != 0 )
    return;
  switch ( t.Mode )
  {
    case fmOutput: /* fmAppend gets changed to fmOutPut in do_open (JM) */
    {
        /* Write EOL */
      fpc_WriteBuffer( t, t.LineEnd, StrLen(t.LineEnd) );
        /* Flush */
      if ( t.FlushFunc != NULL )
        FileFunc( t.FlushFunc )( t );
    }
    break;
    case fmInput:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}


void fpc_Write_Text_ShortStr( unsigned int Len, TTextRec& t, const AnsiString s )
{
  if ( InOutRes != 0 )
    return;
  switch ( t.Mode )
  {
    case fmOutput /* fmAppend gets changed to fmOutPut in do_open (JM) */ : // 55218:
    {
      if ( (int) Len > s.Length( ) )
        fpc_WriteBlanksA( t, Len - s.Length( ) );
      fpc_WriteBuffer( t, (char*) s.c_str(), s.Length( ) );
    }
    break;
    case fmInput:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}


int indexbyte( const void* buf, int Len, unsigned char b )
{
  int result = 0;
  PByte psrc = NULL, pend = NULL;
  psrc = (PByte) buf;
  /* simulate assembler implementations behaviour, which is expected */
  /* fpc_pchar_to_ansistr in astrings.inc                           */
  if ( ( Len < 0 ) || ( ((int) psrc ) + Len < ((int) psrc ) ) )
    pend = ((PByte) numeric_limits<DWORD>::max() ) - sizeof( unsigned char );
  else
  pend = (PByte) (psrc + Len);
  while ( ((int) psrc ) < ((int) pend ) )
  {
    if ( *psrc == b )
    {
      result = ((int) psrc ) - ((int) ((PByte) buf ) );
      return result;
    }
    psrc++;
  }
  result = - 1;
  return result;
}


void fpc_Write_Text_Pchar_as_Array( int Len, TTextRec& t, const char* s, int s_maxidx, bool zerobased = true )
{
  int ArrayLen = 0;
  const char* P = NULL;
  if ( InOutRes != 0 )
    return;
  switch ( t.Mode )
  {
    case fmOutput: /* fmAppend gets changed to fmOutPut in do_open (JM) */ 
    {
      P = s;
      if ( zerobased )
      {
            /* can't use StrLen, since that one could try to read past the end */
            /* of the heap (JM)                                                */
        ArrayLen = indexbyte( P, s_maxidx /*# High(s) */ + 1, 0 );
            /* IndexByte returns -1 if not found (JM) */
        if ( ArrayLen == - 1 )
          ArrayLen = s_maxidx /*# High(s) */ + 1;
      }
      else
        ArrayLen = s_maxidx /*# High(s) */ + 1;
      if ( Len > ArrayLen )
        fpc_WriteBlanksA( t, Len - ArrayLen );
      fpc_WriteBuffer( t, P, ArrayLen );
    }
    break;
    case fmInput:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}


void fpc_Write_Text_PChar_As_Pointer( int Len, TTextRec& t, const char* P )
{
  int PCharLen = 0;
  if ( ( P == NULL ) || ( InOutRes != 0 ) )
    return;
  switch ( t.Mode )
  {
    case fmOutput: /* fmAppend gets changed to fmOutPut in do_open (JM) */ // 55218:
    {
      PCharLen = strlen( P );
      if ( Len > PCharLen )
        fpc_WriteBlanksA( t, Len - PCharLen );
      fpc_WriteBuffer( t, P, PCharLen );
    }
    break;
    case fmInput:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}

void fpc_Write_Text_AnsiStr( int Len, TTextRec& t, const AnsiString s )
/*
 Writes a AnsiString to the TTextRec file T
*/
{
  int SLen = 0;
  if ( InOutRes != 0 )
    return;
  switch ( t.Mode )
  {
    case fmOutput :/* fmAppend gets changed to fmOutPut in do_open (JM) */ // 55218:
    {
      SLen = s.Length( );
      if ( Len > SLen )
        fpc_WriteBlanksA( t, Len - SLen );
      if ( SLen > 0 )
        fpc_WriteBuffer( t, s.c_str(), SLen );
    }
    break;
    case /*# fmInput */ 55217:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}


void Write_Str( int Len, TTextRec& t, const AnsiString s ) //IOCheck; [external Name 'FPC_WRITE_TEXT_SHORTSTR'];

{
  fpc_Write_Text_ShortStr( Len, t, s );
}


void fpc_Write_Text_SInt(int Len, TTextRec& t, int l )
{
  AnsiString s;
	if ( InOutRes != 0 )
		return;
	//Str( l, s );
	std::ostringstream oss;
	oss << l;
	s = oss.str().c_str();
  Write_Str( Len, t, s );
}


void fpc_Write_Text_UInt( int Len, TTextRec& t, unsigned int l ) 

{
  AnsiString s;
  if ( InOutRes != 0 )
    return;
	//Str( l, s );
	std::ostringstream oss;
	oss << l;
	s = oss.str().c_str();  Write_Str( Len, t, s );
}


void fpc_write_text_qword( int Len, TTextRec& t, uint64_t q ) 

{
  AnsiString s;
  if ( InOutRes != 0 )
    return;
//	Str( q, s );
	std::ostringstream oss;
	oss << q;
	s = oss.str().c_str();  Write_Str( Len, t, s );
}


void fpc_write_text_int64( int Len, TTextRec& t, int64_t i )
{
  AnsiString s;
  if ( InOutRes != 0 )
    return;
	//Str( i, s );
	std::ostringstream oss;
	oss << i;
	s = oss.str().c_str();  Write_Str( Len, t, s );
}

void StrFormat(long double xd, int xiMinWidth, int xiDecPlaces, AnsiString& xs)
{
	ostringstream oss;
	if(xiMinWidth == 0)
	{
		if(xiDecPlaces == 0)
		 oss << fixed << setprecision(xiDecPlaces) << xd;
		else
		 oss << fixed << showpoint << setprecision(xiDecPlaces) << xd;
	}
	else
		oss << scientific << uppercase << setw(xiMinWidth) << setprecision(xiDecPlaces) << xd;
	xs = oss.str().c_str();
}
/*
void Str(long double xd, int xiMinWidth, AnsiString& xs)
{
  ostringstream oss;
	oss << scientific << uppercase << setw(xiMinWidth) << setprecision(14)  << xd;
  xs = oss.str().c_str();
}

void Str(double xd, AnsiString& xs)
{
	ostringstream oss;
	oss << scientific << uppercase << setprecision(14) << xd;
  xs = oss.str().c_str();
}
*/
void fpc_Write_Text_Float( int rt, int fixkomma, int Len, TTextRec& t, long double r ) 

{
  AnsiString s;
  if ( InOutRes != 0 )
    return;
//  Str_real(Len,fixkomma,r,treal_type(rt),s);
//  Str_real(Len,fixkomma,r,rt_c64bit,s);
  
	std::ostringstream oss;
	if(rt != -1)
  {
		if(fixkomma != -1)
		{
			StrFormat(r, rt, fixkomma, s);
			/*
			if(rt == 0)
			{
				if(rt == 0)
				 oss << fixed << setprecision(fixkomma) << r;
				else
				 oss << fixed << showpoint << setprecision(fixkomma) << r;
			}
			else
				oss << scientific << uppercase << setw(rt) << setprecision(fixkomma) << r;
      */
		}
		else
		{
			//Str(r, rt, s);
			oss << scientific << uppercase << setw(rt) << setprecision(14)  << r;
		}
  }
	else
	{
		//Str(r, s);
		oss << scientific << uppercase << setprecision(14) << r;
	}
	s = oss.str().c_str();

	Write_Str( Len, t, s );
}

void fpc_Write_Text_Currency( int fixkomma, int Len, TTextRec& t, Currency c )
{
  AnsiString s;
  if ( InOutRes != 0 )
    return;
	StrFormat((double) c, Len, fixkomma, s );
  Write_Str( Len, t, s );
}

void fpc_Write_Text_Boolean( int Len, TTextRec& t, bool b )
{
	if ( InOutRes != 0 )
    return;
/* Can't use array[boolean] because b can be >0 ! */
  if ( b )
    Write_Str( Len, t, "TRUE" );
  else
    Write_Str( Len, t, "FALSE" );
}


void fpc_Write_Text_Char( int Len, TTextRec& t, char c )
{
  if ( InOutRes != 0 )
    return;
  if ( t.Mode != fmOutput )
  {
    if ( t.Mode == fmClosed )
      InOutRes = 103;
    else
      InOutRes = 105;
    return;
  }
  if ( Len > 1 )
    fpc_WriteBlanksA( t, Len - 1 );
  if ( t.BufPos >= t.BufSize )
    FileFunc( t.InOutFunc )( t );
  t.BufPtr[t.BufPos] = c;
  t.BufPos++;
}



/******************************************************************************
                                Read(Ln)
******************************************************************************/


bool NextChar( TTextRec& t, AnsiString& s )
{
  bool result = false;
  result = false;
  if ( t.BufPos < t.BufEnd )
    if ( ! ( CtrlZMarksEOF ) || ( t.BufPtr[t.BufPos] != '\x1a' ) )
    {
    /*
     if length(s)<high(s) then
      begin
        inc(s[0]);
        s[length(s)]:=TTextRec(f).BufPtr^[TTextRec(f).BufPos];
      end;  */
      //s[s.length( )] = ((TTextRec*) &f )->BufPtr[((TTextRec*) &f )->BufPos];
      s += t.BufPtr[t.BufPos];
      t.BufPos++;
      if ( t.BufPos >= t.BufEnd )
        FileFunc( t.InOutFunc )( t );
      result = true;
    }
  return result;
}


bool IgnoreSpaces( TTextRec& t )
/*
  Removes all leading spaces,tab,eols from the input buffer, returns true if
  the buffer is empty
*/
{
  bool result = false;
  AnsiString s;
  s = "";
  result = false;
  /* Return false when already at EOF */
  if ( t.BufPos >= t.BufEnd )
    return result;
/* Check performed separately to avoid accessing memory outside buffer */
  if ( CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' ) )
    return result;
  while ( t.BufPtr[t.BufPos] <= ' ' )
  {
    if ( ! NextChar( t, s ) )
      return result;
     /* EOF? */
    if ( t.BufPos >= t.BufEnd )
      break;
    if ( CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' ) )
      break;
  }
  result = true;
  return result;
}



void ReadNumeric( TTextRec& t, AnsiString& s )
/*
  Read numeric input, if buffer is empty then return True
*/
{
  do
  {
    if ( ! NextChar( t, s ) )
      return;
//  until (length(s)=high(s)) or (TTextRec(f).BufPtr^[TTextRec(f).BufPos] <= ' ');
  }
  while ( ! ( t.BufPtr[t.BufPos] <= ' ' ) );
}


bool CheckRead( TTextRec& t )
{
  bool result = false;
  result = false;
/* Check error and if file is open and load buf if empty */
  if ( InOutRes != 0 )
    return result;
  if ( t.Mode != fmInput )
  {
    switch ( t.Mode )
    {
      case fmOutput: case fmAppend:
        InOutRes = 104;
      break;
    default:
      InOutRes = 103;
    }
    return result;
  }
  if ( t.BufPos >= t.BufEnd )
    FileFunc( t.InOutFunc )( t );
  result = true;
  return result;
}



void fpc_Read_End( TTextRec& t )
{
  if ( t.FlushFunc != NULL )
    FileFunc( t.FlushFunc )( t );
}


void fpc_ReadLn_End( TTextRec& t )
{
  char prev = '\0';
  if ( ! CheckRead( t ) )
    return;
  if ( t.BufPos >= t.BufEnd )
    /* Flush if set */
  {
    if ( t.FlushFunc != NULL )
      FileFunc( t.FlushFunc )( t );
    return;
  }
  if ( CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' ) )
    return;
  do
  {
    prev = t.BufPtr[t.BufPos];
    t.BufPos++;
/* no system uses #10#13 as line seperator (#10 = *nix, #13 = Mac, */
/* #13#10 = Dos), so if we've got #10, we can safely exit          */
    if ( prev == '\x0a' )
      return;
    if ( t.BufPos >= t.BufEnd )
    {
      FileFunc( t.InOutFunc )( t );
      if ( t.BufPos >= t.BufEnd )
          /* Flush if set */
      {
        if ( t.FlushFunc != NULL )
          FileFunc( t.FlushFunc )( t );
        return;
      }
    }
    if ( CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' ) )
      return;
    if ( prev == '\x0d' )
     /* is there also a #10 after it? */
    {
      if ( t.BufPtr[t.BufPos] == '\x0a' )
         /* yes, skip that one as well */
        t.BufPos++;
      return;
    }
  }
  while ( ! ( false ) );
}


int ReadPCharLenA( TTextRec& t, char* s, unsigned int maxlen )
{
  int result = 0;
  unsigned int sPos = 0, Len = 0;
  char* P = NULL,* startp = NULL,* maxp = NULL;
  bool end_of_string = false;
  result = 0;
  if ( ! CheckRead( t ) )
    return result;
/* Read maximal until Maxlen is reached */
  sPos = 0;
  end_of_string = false;
  do
  {
    if ( t.BufPos >= t.BufEnd )
    {
      FileFunc( t.InOutFunc )( t );
      if ( t.BufPos >= t.BufEnd )
        break;
    }
    P = &t.BufPtr[t.BufPos];
    if ( sPos + t.BufEnd - t.BufPos > maxlen )
      maxp = &t.BufPtr[t.BufPos + maxlen - sPos];
    else
      maxp = &t.BufPtr[t.BufEnd];
    startp = P;
    char* startp2 = &s[sPos];;
  /* find stop character */
    while ( P < maxp )
    {
        /* Optimization: Do a quick check for a control character first */
      if ( *P < ' ' )
      {
        if ( *P == '\n' || *P == '\r' || ( CtrlZMarksEOF && ( *P == '\x1a' ) ) )
        {
          *startp2 = *P;  // dme
          end_of_string = true;
          break;
        }
      }
      *startp2++ = *P;  // dme
      P++;
    }
  /* calculate read bytes */
    Len = P - startp;
    t.BufPos += Len;
    //memcpy( &s[sPos], startp, Len );
    sPos += Len;
  }
  while ( ! ( ( sPos == maxlen ) || end_of_string ) );
  result = sPos;
  return result;
}


int ReadPCharLen( TTextRec& t, wchar_t* s, unsigned int maxlen )
{
  int result = 0;
  unsigned int sPos = 0, Len = 0;
  char* P = NULL,* startp = NULL,* maxp = NULL;
  bool end_of_string = false;
  result = 0;
  if ( ! CheckRead( t ) )
    return result;
/* Read maximal until Maxlen is reached */
  sPos = 0;
  end_of_string = false;
  do
  {
    if ( t.BufPos >= t.BufEnd )
    {
      FileFunc( t.InOutFunc )( t );
      if ( t.BufPos >= t.BufEnd )
        break;
    }
    P = &t.BufPtr[t.BufPos];
    if ( sPos + t.BufEnd - t.BufPos > maxlen )
      maxp = &t.BufPtr[t.BufPos + maxlen - sPos];
    else
      maxp = &t.BufPtr[t.BufEnd];
    startp = P;
    wchar_t* startp2 = &s[sPos];
  /* find stop character */
    while ( P < maxp )
    {
        /* Optimization: Do a quick check for a control character first */
      if ( *P < ' ' )
      {
        if ( *P == '\n' || *P == '\r' || ( CtrlZMarksEOF && ( *P == '\x1a' ) ) )
        {
          *startp2 = *P;  // dme
          end_of_string = true;
          break;
        }
      }
      *startp2++ = *P;  // dme
      P++;      
    }
  /* calculate read bytes */
    Len = P - startp;
    t.BufPos += Len;
    //MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, startp, Len, &s[sPos], maxlen );
    sPos += Len;
  }
  while ( ! ( ( sPos == maxlen ) || end_of_string ) );
  result = sPos;
  return result;
}



void fpc_Read_Text_ShortStr( TTextRec& t, SmallString<255>& s )
{
  s[0] = char( ReadPCharLenA( t, &s[1], 255 /*# High(s) */ ) );
} 


void fpc_Read_Text_PChar_As_Pointer( TTextRec& t, char* s, int maxlen )
{
  *( s + ReadPCharLenA( t, s, maxlen ) ) = '\x00';
}

void fpc_Read_Text_PChar_As_Pointer( TTextRec& t, wchar_t* s, int maxlen )
{
  *( s + ReadPCharLen( t, s, maxlen ) ) = '\x00';
}


void fpc_Read_Text_PChar_As_Array( TTextRec& t, char* s, int s_maxidx, bool zerobased = false )
{
  int Len = 0;
  Len = ReadPCharLenA( t, (char*) ( &s[0] ), s_maxidx /*# High(s) */ + 1 );
  if ( zerobased && ( Len > s_maxidx /*# High(s) */ ) )
    Len = s_maxidx /*# High(s) */;
  if ( Len <= s_maxidx /*# High(s) */ )
    s[Len] = '\x00';
}

void fpc_Read_Text_PChar_As_Array( TTextRec& t, wchar_t* s, int s_maxidx, bool zerobased = false )
{
  int Len = 0;
  Len = ReadPCharLen( t, s, s_maxidx /*# High(s) */ + 1 );
  if ( zerobased && ( Len > s_maxidx /*# High(s) */ ) )
    Len = s_maxidx /*# High(s) */;
  if ( Len <= s_maxidx /*# High(s) */ )
    s[Len] = '\x00';
}


void fpc_Read_Text_AnsiStr(TTextRec& t, AnsiString& s)
{
  int SLen = 0, Len = 0;
  SLen = 0;
  do
  {
    // resize will reallocate the length.
//    len:=ReadPCharLen(f,pchar(Pointer(S)+slen),255);
    s.SetLength(SLen + 255);
    Len = ReadPCharLenA( t, (char*) s.c_str() + SLen, 255 );
    SLen += Len;
  }
  while ( ! ( Len < 255 ) );
  // Set actual length
    s.SetLength(SLen );

}


void fpc_Read_Text_Char( TTextRec& t, char& c )
{
  c = '\x00';
  if ( ! CheckRead( t ) )
    return;
  if ( t.BufPos >= t.BufEnd )
  {
    c = '\x1a';
    return;
  }
  c = t.BufPtr[t.BufPos];
  t.BufPos++;
}


void fpc_Read_Text_SInt( TTextRec& t, int& l ) //ValSInt);

{
  AnsiString hs;
  int code = 0;
  l = 0;
  if ( ! CheckRead( t ) )
    return;
  hs = "";
  if ( IgnoreSpaces( t ) )
  {
     /* When spaces were found and we are now at EOF,
       then we return 0 */
    if ( t.BufPos >= t.BufEnd )
      return;
    if ( CtrlZMarksEOF && ( t.BufPtr[t.BufPos] == '\x1a' ) )
      return;
    ReadNumeric( t, hs );
  }
  if ( hs.IsEmpty())
    l = 0;
  else
  {
		//Val( hs, l, code );
		std::istringstream iss(hs.c_str());
		iss >> l;

    if ( code != 0 )
      InOutRes = 106;
  }
}



void fpc_Read_Text_UInt( TTextRec& t, unsigned int& u )

{
  AnsiString hs;
	//int code = 0;
  u = 0;
  if ( ! CheckRead( t ) )
    return;
  hs = "";
  if ( IgnoreSpaces( t ) )
  {
     /* When spaces were found and we are now at EOF,
       then we return 0 */
    if ( t.BufPos >= t.BufEnd )
      return;
    ReadNumeric( t, hs );
  }
  if ( hs.IsEmpty())
    u = 0;
  else
  {
		//Val( hs, u, code );
		//if ( code != 0 )
		//		InOutRes = 106;
		std::istringstream iss(hs.c_str());
		iss >> u;
	}
}


void fpc_Read_Text_UInt( TTextRec& t, unsigned short& u )

{
  AnsiString hs;
	//int code = 0;
  u = 0;
  if ( ! CheckRead( t ) )
    return;
  hs = "";
  if ( IgnoreSpaces( t ) )
  {
     /* When spaces were found and we are now at EOF,
       then we return 0 */
    if ( t.BufPos >= t.BufEnd )
      return;
    ReadNumeric( t, hs );
  }
  if ( hs.IsEmpty())
    u = 0;
  else
  {
		//Val( hs, u, code );
		//if ( code != 0 )
		//  InOutRes = 106;
		std::istringstream iss(hs.c_str());
		iss >> u;
	}
}



void fpc_Read_Text_Float( TTextRec& t, long double& v ) 
{
  AnsiString hs;
	//int code = 0;
  v = 0.0;
  if ( ! CheckRead( t ) )
    return;
  hs = "";
  if ( IgnoreSpaces( t ) )
  {
     /* When spaces were found and we are now at EOF,
       then we return 0 */
    if ( t.BufPos >= t.BufEnd )
      return;
    ReadNumeric( t, hs );
  }
	//Val( hs, v, code );
	//if ( code != 0 )
	//  InOutRes = 106;
	std::istringstream iss(hs.c_str());
	iss >> v;
}

void fpc_Read_Text_Currency( TTextRec& f, Currency& v )
{
  AnsiString hs;
	//int code = 0;
  v = 0.0;
	//double d = 0.0;
  if ( ! CheckRead( f ) )
    return;
  hs = "";
  if ( IgnoreSpaces( f ) )
  {
    // When spaces were found and we are now at EOF, then we return 0 
    if ( ((TTextRec*) &f )->BufPos >= ((TTextRec*) &f )->BufEnd )
      return;
    ReadNumeric( f, hs );
  }
//	Val( hs, d, code );
//  v = d;
//  if ( code != 0 )
//    InOutRes = 106;
	std::istringstream iss(hs.c_str());
	iss >> v;
}

void fpc_Read_Text_QWord( TTextRec& t, uint64_t& q )
{
  AnsiString hs;
	//int code = 0;
	q = 0;
  if ( ! CheckRead( t ) )
    return;
  hs = "";
  if ( IgnoreSpaces( t ) )
  {
     /* When spaces were found and we are now at EOF,
       then we return 0 */
    if ( t.BufPos >= t.BufEnd )
      return;
    ReadNumeric( t, hs );
  }
//  Val( hs, q, code );
//  if ( code != 0 )
//    InOutRes = 106;
	std::istringstream iss(hs.c_str());
	iss >> q;
}


void fpc_Read_Text_Int64( TTextRec& t, int64_t& i )
{
  AnsiString hs;
  //int code = 0;
  i = 0;
  if ( ! CheckRead( t ) )
    return;
  hs = "";
  if ( IgnoreSpaces( t ) )
  {
     /* When spaces were found and we are now at EOF,
       then we return 0 */
    if ( t.BufPos >= t.BufEnd )
      return;
    ReadNumeric( t, hs );
  }
//	Val( hs, i, code );
//  if ( code != 0 )
//    InOutRes = 106;
	std::istringstream iss(hs.c_str());
	iss >> i;
}


/*****************************************************************************
                    subroutines for typed file handling
*****************************************************************************/


void AssignFile( TFileRec& f, const String Name )
{
  memset(&f, 0, sizeof( TFileRec ));
  f.Handle = UnusedHandle;
  f.Mode = fmClosed;
  StrCpy(f.Name, Name.c_str());
}

void AssignFile( TFileRec& f, Char c )
{
  Char buf[2];
	buf[0] = c;
	buf[1] = _T('\0');
	AssignFile( f, buf);
}

void Assign( TFileRec& f, const String Name )
{
  AssignFile(f, Name);
}

void Assign( TFileRec& f, Char c ) 
{
  AssignFile(f, c);
}

//---------------------------------------------------------------------------
void fpc_typed_write( int typesize, TFileRec& f, void* buf )
{
  if ( InOutRes != 0 )
    return;
  switch ( f.Mode )
  {
    case fmOutput: case fmInOut:
      do_write( f.Handle, buf, typesize );
    break;
    case fmInput:
      InOutRes = 105;
    break;
  default:
    InOutRes = 103;
  }
}
//---------------------------------------------------------------------------
void fpc_typed_read( int typesize, TFileRec& f, void* buf )
{
  int result = 0;
  if ( InOutRes != 0 )
    return;
  switch ( f.Mode )
  {
    case fmInput: case fmInOut:
    {
      result = do_read( f.Handle, buf, typesize );
      if ( result < typesize )
        InOutRes = 100;
    }
    break;
    case fmOutput:
      InOutRes = 104;
    break;
  default:
    InOutRes = 103;
  }
}

/*****************************************************************************
                    interface functions
*****************************************************************************/


void Write( TTextRec& t, const SmallString<255> s, int Len ) 
{
  fpc_Write_Text_ShortStr( Len, t, s );
} 


void Write( TTextRec& t, const char* s, int s_maxidx, int Len, bool zerobased )
{
  fpc_Write_Text_Pchar_as_Array( Len, t, s, s_maxidx, zerobased );
} 


void Write( TTextRec& t, const char* P, int Len )
{
  fpc_Write_Text_PChar_As_Pointer( Len, t, P );
}


void Write( TTextRec& t, const AnsiString s, int Len )
{
  fpc_Write_Text_AnsiStr( Len, t, s );
}

void Write( TTextRec& t, const wchar_t* P, int Len )
{
  AnsiString s = wstr2str(P);
  fpc_Write_Text_PChar_As_Pointer( Len, t, s.c_str() );
}


void Write( TTextRec& t, const WideString xs, int Len )
{
  AnsiString s;
  s = wstr2str(xs);
  fpc_Write_Text_AnsiStr( Len, t, s );
}

void Write( TTextRec& t, long l, int Len )
{
  fpc_Write_Text_SInt( Len, t, l );
}

void Write( TTextRec& t, int l, int Len )
{
  fpc_Write_Text_SInt( Len, t, l );
}

void Write( TTextRec& t, unsigned int l, int Len )
{
  fpc_Write_Text_UInt( Len, t, l ); 
}

void Write( TTextRec& t, unsigned short l, int Len )
{
  fpc_Write_Text_UInt( Len, t, (int) l );
}


void Write( TTextRec& t, uint64_t q, int Len )  
{
  fpc_write_text_qword( Len, t, q ); 
}

void Write( TTextRec& t, int64_t i, int Len ) 
{
  fpc_write_text_int64( Len, t, i );
}

void Write( TTextRec& t, long double r, int rt, int fixkomma ) 
{
  fpc_Write_Text_Float( rt, fixkomma, 0, t, r ); 
}

void Write( TTextRec& t, double r, int rt, int fixkomma ) 
{
  fpc_Write_Text_Float( rt, fixkomma, 0, t, r ); 
}

void Write( TTextRec& t, Currency c, int fixkomma, int Len )
{
  fpc_Write_Text_Currency( fixkomma, Len, t, c );
}

void Write( TTextRec& t, bool b, int Len ) 
{
  fpc_Write_Text_Boolean( Len, t, b );
}

void Write( TTextRec& t, char c, int Len )
{
  fpc_Write_Text_Char( Len, t, c );
}

void Write( TTextRec& t, unsigned char c, int Len )
{
  fpc_Write_Text_Char( Len, t, c );
}

void Write( TTextRec& t, wchar_t c, int Len )
{
  fpc_Write_Text_Char( Len, t, wchar2char( c ));
}


void WriteLn( TTextRec& t )
{
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, const SmallString<255> s, int Len )
{
  fpc_Write_Text_ShortStr( Len, t, s );
  fpc_Writeln_End( t );
} 

void WriteLn( TTextRec& t, const char* P, int Len )
{
  fpc_Write_Text_PChar_As_Pointer( Len, t, P );
  fpc_Writeln_End( t );
}


void WriteLn( TTextRec& t, const AnsiString s, int Len )
{
  fpc_Write_Text_AnsiStr( Len, t, s );
  fpc_Writeln_End( t );
}


void WriteLn( TTextRec& t, const wchar_t* P, int Len )
{
  //fpc_Write_Text_WideStr( Len, t, P );
  Write(t, P, Len);
  fpc_Writeln_End( t );
}


void WriteLn( TTextRec& t, const WideString s, int Len )
{
  Write(t, s, Len);
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, long l, int Len )
{
  fpc_Write_Text_SInt( Len, t, l );
  fpc_Writeln_End( t );
}


void WriteLn( TTextRec& t, int l, int Len )
{
  fpc_Write_Text_SInt( Len, t, l );
  fpc_Writeln_End( t );
}


void WriteLn( TTextRec& t, unsigned int l, int Len )
{
  fpc_Write_Text_UInt( Len, t, l );
  fpc_Writeln_End( t );
}


void WriteLn( TTextRec& t, unsigned short l, int Len )
{
  fpc_Write_Text_UInt( Len, t, (int) l );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, uint64_t q, int Len ) 
{
  fpc_write_text_qword( Len, t, q ); 
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, int64_t i, int Len ) 
{
  fpc_write_text_int64( Len, t, i );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, long double r, int rt, int fixkomma )
{
  fpc_Write_Text_Float( rt, fixkomma, 0, t, r );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, double r, int rt, int fixkomma )
{
  fpc_Write_Text_Float( rt, fixkomma, 0, t, r ); 
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, Currency c, int fixkomma, int Len )
{
  fpc_Write_Text_Currency( fixkomma, Len, t, c );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, bool b, int Len ) 
{
  fpc_Write_Text_Boolean( Len, t, b );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, char c, int Len )
{
  fpc_Write_Text_Char( Len, t, c );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, unsigned char c, int Len )
{
  fpc_Write_Text_Char( Len, t, c );
  fpc_Writeln_End( t );
}

void WriteLn( TTextRec& t, wchar_t c, int Len )
{
  fpc_Write_Text_Char( Len, t, wchar2char(c) );
  fpc_Writeln_End( t );
}

void Write( const SmallString<255> s, int Len ) 
{
  fpc_Write_Text_ShortStr( Len, Output, s );
}

void Write( const char* P, int Len ) 
{
  fpc_Write_Text_PChar_As_Pointer( Len, Output, P );
}


void Write( const AnsiString s, int Len ) 
{
  fpc_Write_Text_AnsiStr( Len, Output, s );
}

void Write( long l, int Len )
{
  fpc_Write_Text_SInt( Len, Output, l );
}

void Write( int l, int Len )
{
  fpc_Write_Text_SInt( Len, Output, l );
}


void Write( unsigned int l, int Len )

{
  fpc_Write_Text_UInt( Len, Output, l );
}


void Write( uint64_t q, int Len )  

{
  fpc_write_text_qword( Len, Output, q ); 
}


void Write( int64_t i, int Len ) 
{
  fpc_write_text_int64( Len, Output, i );
}


void Write( double r, int rt, int fixkomma ) 
{
  fpc_Write_Text_Float( rt, fixkomma, 0, Output, r ); 
}

void Write( Currency c, int fixkomma, int Len )
{
  fpc_Write_Text_Currency( fixkomma, Len, Output, c );
}

void Write( bool b, int Len )
{
  fpc_Write_Text_Boolean( Len, Output, b );
}


void Write( char c, int Len )
{
  fpc_Write_Text_Char( Len, Output, c );
}

void WriteLn( ) 
{
  fpc_Writeln_End( Output );
}

void WriteLn( const SmallString<255> s, int Len ) 
{
  fpc_Write_Text_ShortStr( Len, Output, s );
  fpc_Writeln_End( Output );
} 


void WriteLn( const char* P, int Len ) 
{
  fpc_Write_Text_PChar_As_Pointer( Len, Output, P );
  fpc_Writeln_End( Output );
}


void WriteLn( const AnsiString s, int Len ) 
{
  fpc_Write_Text_AnsiStr( Len, Output, s );
  fpc_Writeln_End( Output );
}

void WriteLn( const wchar_t* P, int Len )
{
  AnsiString s(P);
  fpc_Write_Text_AnsiStr( Len, Output, s );
  fpc_Writeln_End( Output );
}


void WriteLn( const WideString s, int Len )
{
  fpc_Write_Text_AnsiStr( Len, Output, s );
  fpc_Writeln_End( Output );
}

void WriteLn( long l, int Len )
{
  fpc_Write_Text_SInt( Len, Output, l );
  fpc_Writeln_End( Output );
}

void WriteLn( int l, int Len ) 
{
  fpc_Write_Text_SInt( Len, Output, l );
  fpc_Writeln_End( Output );
}


void WriteLn( unsigned int l, int Len )
{
  fpc_Write_Text_UInt( Len, Output, l );
  fpc_Writeln_End( Output );
}


void WriteLn( uint64_t q, int Len )
{
  fpc_write_text_qword( Len, Output, q ); 
  fpc_Writeln_End( Output );
}


void WriteLn( int64_t i, int Len ) 
{
  fpc_write_text_int64( Len, Output, i );
  fpc_Writeln_End( Output );
}


void WriteLn( long double r, int rt, int fixkomma ) 
{
  fpc_Write_Text_Float( rt, fixkomma, 0, Output, r ); 
  fpc_Writeln_End( Output );
}

void WriteLn( double r, int rt, int fixkomma ) 
{
  fpc_Write_Text_Float( rt, fixkomma, 0, Output, r ); 
  fpc_Writeln_End( Output );
}

void WriteLn( Currency c, int fixkomma, int Len )
{
  fpc_Write_Text_Currency( fixkomma, Len, Output, c );
  fpc_Writeln_End( Output );
}

void WriteLn( bool b, int Len ) 
{
  fpc_Write_Text_Boolean( Len, Output, b );
  fpc_Writeln_End( Output );
}


void WriteLn( char c, int Len )
{
  fpc_Write_Text_Char( Len, Output, c );
  fpc_Writeln_End( Output );
}

// Redirecting wide strings into the console

void Write( wchar_t c, int Len )
{
  fpc_Write_Text_Char( Len, Output, wchar2char(c) );
}

void WriteLn( wchar_t c, int Len )
{
  fpc_Write_Text_Char( Len, Output, wchar2char(c) );
  fpc_Writeln_End( Output );
}

void Write( const wchar_t* P, int Len ) 
{
  fpc_Write_Text_AnsiStr( Len, Output, wstr2str(P) );
}

void Write( const WideString s, int Len )
{
  fpc_Write_Text_AnsiStr( Len, Output, wstr2str(s) );
}

/////////////  Read


void Read( TTextRec& t, SmallString<255>& s )
{
  fpc_Read_Text_ShortStr( t, s );
} 


void Read( TTextRec& t, char* s, int maxlen )
{
  fpc_Read_Text_PChar_As_Pointer( t, s, maxlen );
}

void Read( TTextRec& t, char*& s, bool zerobased)
{
  fpc_Read_Text_PChar_As_Array(t, s, zerobased);
}

void Read( TTextRec& t, wchar_t*& s, bool zerobased)
{
  fpc_Read_Text_PChar_As_Array(t, s, zerobased);  
}

void Read( TTextRec& t, wchar_t*  s, int maxlen )
{
  fpc_Read_Text_PChar_As_Pointer( t, s,  maxlen ); 
}

void Read( TTextRec& t, AnsiString& s )
{
  fpc_Read_Text_AnsiStr( t, s );
}

void Read( TTextRec& t, WideString& xs )
{
  AnsiString s;
  fpc_Read_Text_AnsiStr( t, s );
  xs = str2wstr(s);
}

void Read( TTextRec& t, char& c )
{
  fpc_Read_Text_Char( t, c );
}

void Read( TTextRec& t, wchar_t& xc )
{
  char c;
  fpc_Read_Text_Char( t, c );
  xc = c; 
}

void Read( TTextRec& t, int& l )
{
  fpc_Read_Text_SInt( t, l );
}


void Read( TTextRec& t, unsigned int& u )
{
  fpc_Read_Text_UInt( t, u );
}

void Read( TTextRec& t, unsigned short& u )
{
  fpc_Read_Text_UInt( t, u );
}

void Read( TTextRec& t, long double& v )
{
  fpc_Read_Text_Float( t, v );
}

void Read( TTextRec& t, double& xv )
{
  long double v; 
  fpc_Read_Text_Float( t, v );
  xv = (double) v;
}

void Read( TTextRec& f, Currency& v )
{
  fpc_Read_Text_Currency( f, v );
}

void Read( TTextRec& t, int64_t& i ) 
{
  fpc_Read_Text_Int64( t, i );
}

void Read( TTextRec& t, uint64_t& q ) 
{
  fpc_Read_Text_QWord( t, q ); 
}

void ReadLn( TTextRec& t ) 
{
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, SmallString<255>& s ) 
{
  fpc_Read_Text_ShortStr( t, s );
  fpc_ReadLn_End( t );
} 

void ReadLn( TTextRec& t, char* s, int maxlen )
{
  fpc_Read_Text_PChar_As_Pointer( t, s, maxlen );
  fpc_ReadLn_End( t );
}


void ReadLn( TTextRec& t, char*& s, bool zerobased )
{
  fpc_Read_Text_PChar_As_Array(t, s, zerobased);
  fpc_ReadLn_End( t );
}


void ReadLn( TTextRec& t, AnsiString& s )
{
  fpc_Read_Text_AnsiStr( t, s );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, WideString& xs )
{
  AnsiString s;
  fpc_Read_Text_AnsiStr( t, s );
  xs = str2wstr(s);
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, char& c )
{
  fpc_Read_Text_Char( t, c );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, wchar_t& xc ) 
{
  char c;  // todo MultiByteToWideChar
  fpc_Read_Text_Char( t, c );
  xc = c;
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, int& l )
{
  fpc_Read_Text_SInt( t, l );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, unsigned int& u )
{
  fpc_Read_Text_UInt( t, u );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, unsigned short& u )
{
  fpc_Read_Text_UInt( t, u );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, long double& v )
{
  fpc_Read_Text_Float( t, v );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, double& v )
{
  Read( t, v );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& f, Currency& v )
{
  fpc_Read_Text_Currency( f, v );
  fpc_ReadLn_End( f );
}

void ReadLn( TTextRec& t, int64_t& i ) 
{
  fpc_Read_Text_Int64( t, i );
  fpc_ReadLn_End( t );
}

void ReadLn( TTextRec& t, uint64_t& q ) 
{
  fpc_Read_Text_QWord( t, q );
  fpc_ReadLn_End( t );
}

void Read( SmallString<255>& s ) 
{
  fpc_Read_Text_ShortStr( Input, s );
} 


void Read( char* s, int maxlen )
{
  fpc_Read_Text_PChar_As_Pointer( Input, s, maxlen );
}

void Read( wchar_t* xp, int maxlen )
{
  char* p = (char*) xp;
  fpc_Read_Text_PChar_As_Pointer( Input, p, 2 * maxlen );
}


void Read( AnsiString& s )
{
  fpc_Read_Text_AnsiStr( Input, s );
}

void Read( WideString& xs )
{
	AnsiString s;
  fpc_Read_Text_AnsiStr( Input, s );
	xs = s;
}

void Read( char& c )
{
  fpc_Read_Text_Char( Input, c );
}

void Read( wchar_t& xc ) 
{
	char c;
  fpc_Read_Text_Char( Input, c );
	xc = c;
}


void Read( int& l )

{
  fpc_Read_Text_SInt( Input, l );
}


void Read( unsigned int& u )

{
  fpc_Read_Text_UInt( Input, u );
}

void Read( unsigned short& u )

{
  fpc_Read_Text_UInt( Input, u );
}

void Read( double& v )

{
  Read( Input, v );
}

void Read( Currency& v )
{
  fpc_Read_Text_Currency( Input, v );
}

void Read( int64_t& i ) 
{
  fpc_Read_Text_Int64( Input, i );
}

void Read( uint64_t& q ) 
{
  fpc_Read_Text_QWord( Input, q );
}


void ReadLn( )
{
  fpc_ReadLn_End( Input );
}

void ReadLn( SmallString<255>& s )
{
  fpc_Read_Text_ShortStr( Input, s );
  fpc_ReadLn_End( Input );
} 

void ReadLn( char* s, int maxlen )
{
  fpc_Read_Text_PChar_As_Pointer( Input, s, maxlen );
  fpc_ReadLn_End( Input );
}

void ReadLn( wchar_t* s, int maxlen )
{
  fpc_Read_Text_PChar_As_Pointer( Input, (char*) s, 2 * maxlen );
  fpc_ReadLn_End( Input );
}

void ReadLn( AnsiString& s )
{
  fpc_Read_Text_AnsiStr( Input, s );
  fpc_ReadLn_End( Input );
}

void ReadLn( WideString& xs )
{
	AnsiString s;
  fpc_Read_Text_AnsiStr( Input, s );
	xs = s;
  fpc_ReadLn_End( Input );
}

void ReadLn( char& c )
{
  fpc_Read_Text_Char( Input, c );
  fpc_ReadLn_End( Input );
}

void ReadLn( wchar_t& xc ) 
{
	char c;
  fpc_Read_Text_Char( Input, c );
	xc = c;
  fpc_ReadLn_End( Input );
}


void ReadLn( int& l )

{
  fpc_Read_Text_SInt( Input, l );
  fpc_ReadLn_End( Input );
}


void ReadLn( unsigned int& u )

{
  fpc_Read_Text_UInt( Input, u );
  fpc_ReadLn_End( Input );
}

void ReadLn( unsigned short& u )
{
  fpc_Read_Text_UInt( Input, u );
  fpc_ReadLn_End( Input );
}

void ReadLn( double& v )

{
  Read( Input, v );
  fpc_ReadLn_End( Input );
}

void ReadLn( Currency& v )
{
  fpc_Read_Text_Currency( Input, v );
  fpc_ReadLn_End( Input );
}

void ReadLn( int64_t& i )
{
  fpc_Read_Text_Int64( Input, i );
  fpc_ReadLn_End( Input );
}


void ReadLn( uint64_t& q )
{
  fpc_Read_Text_QWord( Input, q );
  fpc_ReadLn_End( Input );
}

#if (__BORLANDC__ >= 0x0610)
void Write( TTextRec& t, const UnicodeString xs, int Len )
{
  AnsiString s;
  s = wstr2str(xs);
  fpc_Write_Text_AnsiStr( Len, t, s );
}

void WriteLn( TTextRec& t, const UnicodeString s, int Len )
{
  Write(t, s, Len);
  fpc_Writeln_End( t );
}

void WriteLn( const UnicodeString s, int Len )
{
  fpc_Write_Text_AnsiStr( Len, Output, s );
  fpc_Writeln_End( Output );
}

void Write( const UnicodeString s, int Len )
{
  fpc_Write_Text_AnsiStr( Len, Output, wstr2str(s) );
}

void Read( TTextRec& t, UnicodeString& xs )
{
  AnsiString s;
  fpc_Read_Text_AnsiStr( t, s );
  xs = str2wstr(s);
}

void ReadLn( TTextRec& t, UnicodeString& xs )
{
  AnsiString s;
  fpc_Read_Text_AnsiStr( t, s );
  xs = str2wstr(s);
  fpc_ReadLn_End( t );
}

void Read( UnicodeString& xs )
{
	AnsiString s;
  fpc_Read_Text_AnsiStr( Input, s );
	xs = s;
}

void ReadLn( UnicodeString& xs )
{
	AnsiString s;
  fpc_Read_Text_AnsiStr( Input, s );
	xs = s;
  fpc_ReadLn_End( Input );
}
#endif

/*****************************************************************************
                            Directory Management
*****************************************************************************/

void GetDir( unsigned char drivenr, String& Dir )
{
  Char Drive [ 4 ];
  Drive[0] = _T('\x00');
  Drive[1] = _T(':');
  Drive[2] = _T('\x00');
  Drive[3] = _T('\x00');
  bool defaultdrive = false;
  Char DirBuf[ 260 ], SaveBuf[ 260 ];
  defaultdrive = drivenr == 0;
  if ( ! defaultdrive )
  {
    Drive[0]= char(drivenr + 64);
		GetCurrentDirectoryW( 259, SaveBuf );
		if ( ! SetCurrentDirectoryW( Drive ) )
		{
      /* dme
			errno = ((WORD) GetLastError() );
      Errno2InOutRes();
			Dir = String( 1, drivenr + 64 ) + _T(":\\");
      SetCurrentDirectory( &SaveBuf[0] );
      return;
      */
    }
  }
	GetCurrentDirectoryW( 259, DirBuf );
  if ( ! defaultdrive )
		SetCurrentDirectoryW( SaveBuf );
	Dir = DirBuf;
  if ( ! FileNameCaseSensitive )
		Dir = UpperCase( Dir );
}

ShortString UpperCase(ShortString& S)
{
  SmallString<255> result;
  int i = 0;
  result[0] = S[0];
  for ( i = 1; i <= S[0]; i++)
    result[i] = UpCase( S[i] );
  return result;
}

void GetDir( unsigned char drivenr, SmallString<255>& Dir )
{
  char Drive [ 4 ];
  Drive[0] = '\x00';
  Drive[1] = ':';
  Drive[2] = '\x00';
  Drive[3] = '\x00';
  bool defaultdrive = false;
  char DirBuf[ 260 ], SaveBuf[ 260 ];
  defaultdrive = drivenr == 0;
  if ( ! defaultdrive )
  {
    Drive[0]= char(drivenr + 64);
    GetCurrentDirectoryA( sizeof( SaveBuf ), SaveBuf );
    if ( ! SetCurrentDirectoryA( &Drive[0] ) )
    {
      errno = ((WORD) GetLastError() );
      Errno2InOutRes();
      Dir[1] = (char) ( drivenr + 64 );
      Dir[2] = ':';
      Dir[3] = '\\';
      SetCurrentDirectoryA( &SaveBuf[0] );
      return;
    }
  }
  GetCurrentDirectoryA( sizeof( DirBuf ), DirBuf );
  if ( ! defaultdrive )
		SetCurrentDirectoryA( &SaveBuf[0] );
	Dir = DirBuf;
  if ( ! FileNameCaseSensitive )
    Dir = UpperCase( Dir );
}

/******************************************************************************
                               Initializing
******************************************************************************/


void OpenStdIO( TTextRec& t, int Mode, HANDLE hdl )
{
  AssignFile( t, _T("") );
  t.Handle = hdl;
  t.Mode = Mode;
  t.CloseFunc = (void*) FileCloseFuncA;
  switch ( Mode )
  {
    case fmInput:
      t.InOutFunc = (void*) FileReadFuncA;
    break;
    case fmOutput:
    {
      t.InOutFunc = (void*) FileWriteFuncA;
      if ( do_isdevice( hdl ) )
        t.FlushFunc = (void*) FileWriteFuncA;
    }
    break;
  default:
   //HandleError(102);
    throw runtime_error("internal error");
  }
}

void SysInitStdIO( )
{
  /* Setup stdin, stdout and stderr, for GUI apps redirect stderr,stdout to be
    displayed in a messagebox */

  StdInputHandle = GetStdHandle( STD_INPUT_HANDLE  ) ;
  StdOutputHandle = GetStdHandle( STD_OUTPUT_HANDLE  ) ;
  StdErrorHandle = GetStdHandle( STD_ERROR_HANDLE  ) ;

  if ( ! IsConsole )
  {
     //AssignError(stderr);
     //AssignError(stdout);
    AssignFile( Output, _T("") );
    AssignFile( Input, _T("") );
    AssignFile( ErrOutput, _T("") );
  }
  else
  {
    OpenStdIO( Input, fmInput, StdInputHandle );
    OpenStdIO( Output, fmOutput, StdOutputHandle );
    OpenStdIO( ErrOutput, fmOutput, StdErrorHandle );
    OpenStdIO( Stdout, fmOutput, StdOutputHandle );
    OpenStdIO( Stderr, fmOutput, StdErrorHandle );
  }
}

WORD IOResult( )
{
  WORD result = 0;
  WORD* HInoutRes;
  HInoutRes = &InOutRes;
  result = *HInoutRes;
  HInoutRes = 0;
  return result;
}


void d2c_file_initialization()
{
  FileMode = 2;
  ((TTextRec*) &Input )->Mode = fmClosed;
  ((TTextRec*) &Output )->Mode = fmClosed;
  ((TTextRec*) &ErrOutput )->Mode = fmClosed;
  SysInitStdIO();
}

void d2c_file_finalization()
{
  CloseFile( Input );
  CloseFile( Output );
  CloseFile( ErrOutput );
}

class d2c_file_unit
{
public:
d2c_file_unit()
{
  d2c_file_initialization();
}
~d2c_file_unit(){ d2c_file_finalization(); }
};
d2c_file_unit _d2c_file_unit;

} //namespace System



