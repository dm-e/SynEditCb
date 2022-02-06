#ifndef d2c_sysfileH
#define d2c_sysfileH

#include <Winapi.Windows.hpp>

/*
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
		License along with this package; if not, write to the Free Software
		Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    see COPYING.txt

*/





namespace d2c_system
{

struct TFileRec {
  HANDLE Handle;
  int Mode;
  unsigned int RecSize;
  unsigned char _private [ 28 ];
  unsigned char UserData [ 32 ];
  Char Name [ 260 ];
};

template <typename T>
struct TTypedFile
{
  HANDLE Handle;
  int Mode;
  unsigned int RecSize;
  unsigned char _private [ 28 ];
  unsigned char UserData [ 32 ];
  Char Name [ 260 ];
};

typedef char TextBufA [ 260 ];

struct TTextRec {
  HANDLE Handle;
  int Mode;
  unsigned int BufSize;
  unsigned int BufPos;
  unsigned int BufEnd;
  char* BufPtr;
  void* OpenFunc;
  void* InOutFunc;
  void* FlushFunc;
  void* CloseFunc;
  unsigned char UserData [ 32 ];
  Char Name [ 260 ];
  char LineEnd[3];
  TextBufA Buffer;
};

typedef TTypedFile<unsigned char> file;
typedef TTextRec Text;
typedef TTextRec *ptext;

const Char DirectorySeparator = _T('\\');
const Char DriveSeparator = _T(':');
const Char PathSeparator = _T(';');
const int MaxPathLen = 260;

extern HANDLE UnusedHandle;
extern HANDLE StdInputHandle;
extern HANDLE StdOutputHandle;
extern HANDLE StdErrorHandle;


const bool LFNSupport = true;
const char ExtensionSeparator = '.';
extern Set <wchar_t, 0, 255 > AllowDirectorySeparators;
extern Set <wchar_t, 0, 255 > AllowDriveSeparators;

const wchar_t AllFilesMask = L'*';

extern bool FileNameCaseSensitive;
extern bool CtrlZMarksEOF;


const int fmAppend = 0xD7B4;   // unknown in C++Builder 6?


typedef void ( * FileFunc )( TTextRec&  );

/* Standard In- and Output */
extern WORD InOutRes;


/****************************************************************************
                          Untyped File Management
****************************************************************************/
void AssignFile( TFileRec& f, const String Name );
void AssignFile( TFileRec& f, Char c );
void Assign( TFileRec& f, const String Name );

void Rewrite( TFileRec& f, int l = 128 );
void Reset( TFileRec& f, int l = 128 );
void CloseFile( TFileRec& f );
void Close( TFileRec& f );

void BlockWrite( TTypedFile<unsigned char>& f, void* buf, int64_t Count, int& Result );
void BlockWrite( TTypedFile<unsigned char>& f, void* buf, int Count, int& Result );
void BlockWrite( TTypedFile<unsigned char>& f, void* buf, WORD Count, WORD& Result );
void BlockWrite( TTypedFile<unsigned char>& f, void* buf, unsigned int Count, unsigned int& Result );
void BlockWrite( TTypedFile<unsigned char>& f, void* buf, WORD Count, int& Result );
void BlockWrite( TTypedFile<unsigned char>& f, void* buf, int Count );
void BlockRead( TTypedFile<unsigned char>& f, void* buf, int Count, int& Result );
void BlockRead( TTypedFile<unsigned char>& f, void* buf, int64_t Count );
int64_t FileSize( TFileRec& f ); // FileSize can't be used on a text TTypedFile<unsigned char>.
int64_t FilePos( TFileRec& f, int l = 128 );
void Seek( TTypedFile<unsigned char>& f, int64_t Pos );
void Rename( TTypedFile<unsigned char>& f, const Char* P );
void Rename( TTypedFile<unsigned char>& f, const String s );
void Rename( TTypedFile<unsigned char>& f, Char c );
bool Eof( TFileRec& f, int l = 128 );
void Truncate( TFileRec& f, int RecSize );


/****************************************************************************
                           Typed File Management
****************************************************************************/

void fpc_typed_write( int typesize, TFileRec& f, void* buf );
void fpc_typed_read( int typesize, TFileRec& f, void* buf );

//---------------------------------------------------------------------------
template <typename T>
void AssignFile( TTypedFile<T>& f, const String Name )
{
  AssignFile(*((TFileRec*) &f), Name);
}
//---------------------------------------------------------------------------
template <typename T>
void AssignFile( TTypedFile<T>& f, const Char* P )
{
  AssignFile(*((TFileRec*) &f), P);
}
//---------------------------------------------------------------------------
template <typename T>
void AssignFile( TTypedFile<T>& f, Char c )
{
  AssignFile(*((TFileRec*) &f), c);
}
//---------------------------------------------------------------------------
template <typename T>
void Assign( TTypedFile<T>& f, const String Name )
{
  AssignFile(*((TFileRec*) &f), Name);
}
//---------------------------------------------------------------------------
template <typename T>
void Assign( TTypedFile<T>& f, const Char* P )
{
  AssignFile(*((TFileRec*) &f), P);
}
//---------------------------------------------------------------------------
template <typename T>
void Assign( TTypedFile<T>& f, Char c )
{
  AssignFile(*((TFileRec*) &f), c);
}
//---------------------------------------------------------------------------
template <typename T>
int64_t FileSize( TTypedFile<T>& f ) // FileSize can't be used on a text file.
{
  return FileSize(*((TFileRec*) &f));
}
//---------------------------------------------------------------------------
template <typename T>
bool Eof( TTypedFile<T>& f )
{
  return Eof(*((TFileRec*) &f), sizeof(T) );
}
//---------------------------------------------------------------------------
template <typename T>
void CloseFile( TTypedFile<T>& f )
{
  CloseFile(*((TFileRec*) &f));
}
//---------------------------------------------------------------------------
template <typename T>
void Close( TTypedFile<T>& f )
{
  CloseFile(*((TFileRec*) &f));
}
//---------------------------------------------------------------------------
template <typename T>
void Reset( TTypedFile<T>& f, int l = -1 )
{
  if( InOutRes != 0)
   return;
  if(l == -1)
    Reset( *((TFileRec*) &f), sizeof(T) );
  else
    Reset( *((TFileRec*) &f), l );

}
//---------------------------------------------------------------------------
template <typename T>
void Rewrite( TTypedFile<T>& f, int l = -1 )
{
  if( InOutRes != 0)
   return;
  if(l == -1)
    Rewrite(*((TFileRec*) &f), sizeof(T) );
  else
    Rewrite(*((TFileRec*) &f), l );
}
//---------------------------------------------------------------------------
template <typename T>
void Write( TTypedFile<T>& f, void* buf )
{
  fpc_typed_write( f.RecSize, *((TFileRec*)&f), buf );
}
//---------------------------------------------------------------------------
template <typename T>
void Read( TTypedFile<T>& f, void* buf )
{
  fpc_typed_read( f.RecSize, *((TFileRec*)&f), buf );
}

/////////
//---------------------------------------------------------------------------
template <typename T>
void Truncate( TTypedFile<T>& f )
{
  if( InOutRes != 0)
   return;
  Truncate(*((TFileRec*) &f), ((TFileRec*) &f )->RecSize );
}

/****************************************************************************
                            Text File Management
****************************************************************************/


void Assign( TTextRec& f, const String Name );
void Assign( TTextRec& t, Char c );
void AssignFile( TTextRec& f, const String Name );
void AssignFile( TTextRec& t, Char c );
void CloseFile( TTextRec& t );
void Close( TTextRec& t );
void Rewrite( TTextRec& t );
void Reset( TTextRec& t );
void Append( TTextRec& t );
void Flush( TTextRec& t );
void Erase( TTextRec& t );
void Rename( TTextRec& t, const Char* P );
void Rename( TTextRec& t, const String s );
void Rename( TTextRec& t, Char c );
bool Eof( TTextRec& t );
bool Eof( );
bool EoLn( TTextRec& t );
bool EoLn( );
bool SeekEof( TTextRec& t );
bool SeekEof( );
bool SeekEoLn( TTextRec& t );
bool SeekEoLn( );
void SetTextBuf( TTextRec& t, void* buf, int size );
void SetTextLineEnding(TTextRec& t, const String Ending);


void Write( TTextRec& t, const System::SmallString<255> s, int Len = 0 );
void Write( TTextRec& t, const char* P, int Len = 0 );
void Write( TTextRec& t, const AnsiString s, int Len = 0 );
void Write( TTextRec& t, const wchar_t* P, int Len = 0 );
void Write( TTextRec& t, const WideString s, int Len = 0 );
void Write( TTextRec& t, long l, int Len = 0 );
void Write( TTextRec& t, int l, int Len = 0 );
void Write( TTextRec& t, unsigned int l, int Len = 0 );
void Write( TTextRec& t, unsigned short l, int Len = 0 );
void Write( TTextRec& t, uint64_t q, int Len = 0 );
void Write( TTextRec& t, int64_t i, int Len = 0 );
void Write( TTextRec& t, long double r, int rt = -1, int fixkomma = -1 );
void Write( TTextRec& t, double r, int rt = -1, int fixkomma = -1 );
void Write( TTextRec& t, Currency c, int fixkomma = -1, int Len = 0 );
void Write( TTextRec& t, bool b, int Len = 0 );
void Write( TTextRec& t, char c, int Len = 0 );
void Write( TTextRec& t, unsigned char c, int Len = 0 );
void Write( TTextRec& t, wchar_t c, int Len = 0 );
void WriteLn( TTextRec& t );
void WriteLn( TTextRec& t, const System::SmallString<255> s, int Len = 0 );
void WriteLn( TTextRec& t, const char* P, int Len = 0 );
void WriteLn( TTextRec& t, const AnsiString s, int Len = 0 );
void WriteLn( TTextRec& t, const wchar_t* P, int Len = 0 );
void WriteLn( TTextRec& t, const WideString s, int Len = 0 );
void WriteLn( TTextRec& t, long l, int Len = 0 );
void WriteLn( TTextRec& t, int l, int Len = 0 );
void WriteLn( TTextRec& t, unsigned int l, int Len = 0 );
void WriteLn( TTextRec& t, unsigned short l, int Len = 0 );
void WriteLn( TTextRec& t, uint64_t q, int Len = 0 );
void WriteLn( TTextRec& t, int64_t i, int Len = 0 );
void WriteLn( TTextRec& t, long double r, int rt = -1, int fixkomma = -1 );
void WriteLn( TTextRec& t, double r, int rt = -1, int fixkomma = -1 );
void WriteLn( TTextRec& t, Currency c, int fixkomma, int Len );
void WriteLn( TTextRec& t, bool b, int Len = 0 );
void WriteLn( TTextRec& t, char c, int Len = 0 );
void WriteLn( TTextRec& t, unsigned char c, int Len = 0 );
void WriteLn( TTextRec& t, wchar_t c, int Len = 0 );
void Write( const System::SmallString<255> s, int Len = 0 );
void Write( const char* P, int Len = 0 );
void Write( const AnsiString s, int Len = 0 );
void Write( const wchar_t* P, int Len = 0 );
void Write( const WideString s, int Len = 0 );
void Write( long l, int Len = 0 );
void Write( int l, int Len = 0 );
void Write( unsigned int l, int Len = 0 );
void Write( uint64_t q, int Len = 0 );
void Write( int64_t i, int Len = 0 );
void Write( long double r, int rt = -1, int fixkomma = -1 );
void Write( double r, int rt = -1, int fixkomma = -1 );
void Write( Currency c, int fixkomma = -1, int Len = 0 );
void Write( bool b, int Len = 0 );
void Write( char c, int Len = 0 );
void WriteLn( );
void WriteLn( const System::SmallString<255> s, int Len = 0 );
void WriteLn( const char* P, int Len = 0 );
void WriteLn( const AnsiString s, int Len = 0 );
void WriteLn( const wchar_t* P, int Len = 0 );
void WriteLn( const WideString s, int Len = 0 );
void WriteLn( long l, int Len = 0 );
void WriteLn( int l, int Len = 0 );
void WriteLn( unsigned int l, int Len = 0 );
void WriteLn( uint64_t q, int Len = 0 );
void WriteLn( int64_t i, int Len = 0 );
void WriteLn( long double r, int rt = -1, int fixkomma = -1 );
void WriteLn( double r, int rt = -1, int fixkomma = -1 );
void WriteLn( Currency c, int fixkomma = -1, int Len = 0 );
void WriteLn( bool b, int Len = 0 );
void WriteLn( char c, int Len = 0 );
void Write( wchar_t c, int Len  = 0);
void WriteLn( wchar_t c, int Len = 0 );
// ----------
void Read( TTextRec& t, System::SmallString<255>& s );
void Read( TTextRec& t, char* s, int maxlen = 0x7FFFFFFF );
void Read( TTextRec& t, AnsiString& s );
void Read( TTextRec& t, char& c );
void Read( TTextRec& t, WideString& s );
void Read( TTextRec& t, wchar_t& c );
void Read( TTextRec& t, unsigned int& u );
void Read( TTextRec& t, unsigned short& u );
void Read( TTextRec& t, long double& v );
void Read( TTextRec& t, double& v );
void Read( TTextRec& f, Currency& v );
void Read( TTextRec& t, int64_t& i );
void Read( TTextRec& t, uint64_t& q );
void ReadLn( TTextRec& t);
void ReadLn( TTextRec& t, System::SmallString<255>& s );
void ReadLn( TTextRec& t, char* s, int maxlen = 0x7FFFFFFF );
void ReadLn( TTextRec& t, AnsiString& s );
void ReadLn( TTextRec& t, char& c );
void ReadLn( TTextRec& t, WideString& s );
void ReadLn( TTextRec& t, wchar_t& c );
void ReadLn( TTextRec& t, int& l );
void ReadLn( TTextRec& t, unsigned int& u );
void ReadLn( TTextRec& t, unsigned short& u );
void ReadLn( TTextRec& t, long double& v );
void ReadLn( TTextRec& f, Currency& v );
void ReadLn( TTextRec& t, double& v );
void ReadLn( TTextRec& t, int64_t& i );
void ReadLn( TTextRec& t, uint64_t& q );
void Read( System::SmallString<255>& s );
void Read( char* s, int maxlen = 0x7FFFFFFF );
void Read( AnsiString& s );
void Read( char& c );
void Read( WideString& s );
void Read( wchar_t& c );
void Read( int& l );
void Read( unsigned int& u );
void Read( long double& v );
void Read( Currency& v );
void Read( double& v );
void Read( int64_t& i );
void Read( uint64_t& q );
void ReadLn( );
void ReadLn( System::SmallString<255>& s );
void ReadLn( char* s, int maxlen = 0x7FFFFFFF );
void ReadLn( AnsiString& s );
void ReadLn( char& c );
void ReadLn( WideString& s );
void ReadLn( wchar_t& c );
void ReadLn( int& l );
void ReadLn( unsigned int& u );
void ReadLn( unsigned short& u );
void ReadLn( long double& v );
void ReadLn( Currency& v );
void ReadLn( double& v );
void ReadLn( int64_t& i );
void ReadLn( uint64_t& q );


template <unsigned char sz>
void Write( TTextRec& t, System::SmallString<sz> xs, int Len = 0 )
{
	AnsiString s = xs; // null character at the end needed
	Write( t, s.c_str(), max(xs[0] - 1, Len));	
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void WriteLn( TTextRec& t, System::SmallString<sz> xs, int Len = 0 )
{
	AnsiString s = xs; // null character at the end needed
	WriteLn( t, s.c_str(), max(xs[0] - 1, Len));	
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void Write( System::SmallString<sz> xs, int Len = 0 )
{
	AnsiString s = xs; // null character at the end needed
	Write(s.c_str(), max(xs[0] - 1, Len));	
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void WriteLn( System::SmallString<sz> xs, int Len = 0 )
{
	AnsiString s = xs; // null character at the end needed
	WriteLn(s.c_str(), max(xs[0] - 1, Len));	
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void Read( TTextRec& t, System::SmallString<sz>& s )
{
  char buf[sz + 1];
  Read( t, buf, sz);
  buf[sz] = '\0';
  s = buf;
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void ReadLn( TTextRec& t, System::SmallString<sz>& s )
{
  char buf[sz + 1];
  ReadLn( t, buf, sz);
  buf[sz] = '\0';
  s = buf;
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void Read( System::SmallString<sz>& s )
{
  char buf[sz + 1];
  Read( buf, sz);
  buf[sz] = '\0';
  s = buf;
}
//---------------------------------------------------------------------------
template <unsigned char sz>
void ReadLn( System::SmallString<sz>& s )
{
  char buf[sz + 1];
  ReadLn( buf, sz);
  buf[sz] = '\0';
  s = buf;
}

/*****************************************************************************
                            overloads for UnicodeString
*****************************************************************************/
#if (__BORLANDC__ >= 0x0610)
void Write( TTextRec& t, const UnicodeString s, int Len = 0 );
void WriteLn( TTextRec& t, const UnicodeString s, int Len = 0 );
void Write( const UnicodeString s, int Len = 0 );
void WriteLn( const UnicodeString s, int Len = 0 );
void Read( TTextRec& t, UnicodeString& s );
void ReadLn( TTextRec& t, UnicodeString& s );
void Read( UnicodeString& s );
void ReadLn( UnicodeString& s );
#endif
/*****************************************************************************
                            Directory Management
*****************************************************************************/

void GetDir( unsigned char drivenr, System::SmallString<255>& Dir );
void GetDir( unsigned char drivenr, String& Dir );



} // namespace System

//using namespace System;

#endif //  System
