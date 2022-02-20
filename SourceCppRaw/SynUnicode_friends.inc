
friend TFontCharset __fastcall CharSetFromLocale(LCID Language);
friend bool __fastcall ClipboardProvidesText();
friend int __fastcall CodePageFromLocale(LCID Language);
friend String __fastcall GetClipboardText();
friend System::Sysutils::TEncoding* __fastcall GetEncoding(const String FileName, bool& WithBOM);
friend TSize __fastcall GetTextSize(HDC DC, PWideChar Str, int Count);
friend bool __fastcall IsAnsiOnly(const String WS);
friend bool __fastcall IsUTF8(System::Classes::TStream* Stream, bool& WithBOM, int BytesToCheck/*# = 0x4000*/);
friend bool __fastcall IsWideCharMappableToAnsi(WideChar WC);
friend WORD __fastcall KeyboardCodePage();
friend void __fastcall SetClipboardText(const String Text);
friend void __fastcall StrSwapByteOrder(PWideChar Str);
friend PWideChar __fastcall SynCharNext(PWideChar P);
friend int __fastcall SynUniElementsCount(String s);
friend bool __fastcall IsUTF8(const String FileName, bool& WithBOM, int BytesToCheck/*# = 0x4000*/);
friend void SynUnicode_initialization();
