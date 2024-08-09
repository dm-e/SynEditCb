
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterPerl.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditcodefolding;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterperl
{
#define Synhighlighterperl__0 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterperl__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterperl__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterperl__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterperl__4 (TSysCharSet() << ' ' << '\x08' << '(' << '{')
#define Synhighlighterperl__5 (TSysCharSet() << '_' << '$' << '@' << '%')
#define Synhighlighterperl__6 (TSysCharSet() << '$' << '\"' << '%' <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 << '_' << '#')
#define Synhighlighterperl__7 (TSysCharSet() <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 <<  \
          97 << 98 << 99 << 100 << 101 << 102 <<  \
          103 << 104 << 105 << 106 << 107 << 108 <<  \
          109 << 110 << 111 << 112 << 113 << 114 <<  \
          115 << 116 << 117 << 118 << 119 << 120 <<  \
          121 << 122 <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 << '_')


  /* expanded keywords list */                                                    //Fiala
const String Keywords[296/*# range 0..295*/] = {L"$ACCUMULATOR", L"$ARG", L"$ARGV", L"$BASETIME", L"$DEBUGGING", L"$EFFECTIVE_GROUP_ID", L"$EFFECTIVE_USER_ID", L"$EGID"
                    , L"$ENV", L"$ERRNO", L"$EUID", L"$EVAL_ERROR", L"$EXECUTABLE_NAME", L"$FORMAT_FORMFEED", L"$FORMAT_LINE_BREAK_CHARACTERS", L"$FORMAT_LINES_LEFT"
                    , L"$FORMAT_LINES_PER_PAGE", L"$FORMAT_NAME", L"$FORMAT_PAGE_NUMBER", L"$FORMAT_TOP_NAME", L"$GID"
                    , L"$CHILD_ERROR", L"$INPLACE_EDIT", L"$INPUT_LINE_NUMBER", L"$INPUT_RECORD_SEPARATOR", L"$LAST_PAREN_MATCH", L"$LIST_SEPARATOR"
                    , L"$MATCH", L"$MULTILINE_MATCHING", L"$NR", L"$OFMT", L"$ORS", L"$OS_ERROR", L"$OUTPUT_AUTOFLUSH", L"$OUTPUT_FIELD_SEPARATOR"
                    , L"$PERL_VERSION", L"$PERLDB", L"$PID", L"$POSTMATCH", L"$PREMATCH", L"$PROCESS_ID", L"$PROGRAM_NAME", L"$REAL_GROUP_ID"
                    , L"$REAL_USER_ID", L"$RS", L"$SIG", L"$SUBSCRIPT_SEPARATOR", L"$SUBSEP", L"$SYSTEM_FD_MAX", L"$UID", L"$WARNING"
                    , L"%INC", L"@ARGV", L"@INC", L"abs", L"accept", L"alarm", L"and", L"atan2", L"bind", L"binmode", L"bless", L"break", L"caller"
                    , L"close", L"closedir", L"cmp", L"connect", L"constant", L"continue", L"cos", L"crypt", L"dbmclose", L"dbmopen", L"defined"
                    , L"delete", L"diagnostics", L"die", L"do", L"dump", L"each", L"else", L"elsif", L"endgrent", L"endhostent", L"endnetent", L"endprotoent"
                    , L"endpwent", L"endservent", L"eof", L"eq", L"eval", L"exec", L"exists", L"exit", L"exp", L"fcntl", L"fileno", L"flock"
                    , L"for", L"foreach", L"fork", L"format", L"formline", L"ge", L"getc", L"getgrent", L"getgrgid", L"getgrnam", L"gethostbyaddr", L"gethostbyname"
                    , L"gethostent", L"getlogin", L"getnetbyaddr", L"getnetbyname", L"getnetent", L"getpeername", L"getpgrp", L"getppid"
                    , L"getpriority", L"getprotobyname", L"getprotobynumber", L"getprotoent", L"getpwent", L"getpwnam", L"getpwuid", L"getservbyname"
                    , L"getservbyport", L"getservent", L"getsockname", L"getsockopt", L"glob", L"gmtime", L"goto", L"grep", L"gt"
                    , L"hex", L"chdir", L"chmod", L"chomp", L"chop", L"chown", L"chr", L"chroot", L"if", L"import", L"index", L"int", L"integer", L"ioctl"
                    , L"join", L"keys", L"kill", L"last", L"lc", L"lcfirst", L"le", L"length", L"less", L"link", L"listen", L"local", L"locale", L"localtime"
                    , L"lock", L"log", L"lstat", L"lt", L"m", L"map", L"mkdir", L"msgctl", L"msgget", L"msgrcv", L"msgsnd", L"my", L"ne", L"next"
                    , L"no", L"not", L"oct", L"open", L"opendir", L"or", L"ord", L"our", L"pack", L"package", L"pipe", L"pop", L"pos", L"print", L"printf"
                    , L"push", L"q", L"qq", L"qr", L"quotemeta", L"qw", L"qx", L"rand", L"read", L"readdir", L"readline", L"readlink", L"readpipe", L"recv"
                    , L"redo", L"ref", L"rename", L"require", L"reset", L"return", L"reverse", L"rewinddir", L"rindex", L"rmdir", L"say", L"scalar"
                    , L"seek", L"seekdir", L"select", L"semctl", L"semget", L"semop", L"send", L"setgrent", L"sethostent", L"setnetent", L"setpgrp"
                    , L"setpriority", L"setprotoent", L"setpwent", L"setservent", L"setsockopt", L"shift", L"shmctl", L"shmget", L"shmread"
                    , L"shmwrite", L"shutdown", L"sigtrap", L"sin", L"sleep", L"socket", L"socketpair", L"sort", L"splice", L"split", L"sprintf"
                    , L"sqrt", L"srand", L"stat", L"state", L"strict", L"study", L"sub", L"subs", L"substr", L"symlink", L"syscall", L"sysopen", L"sysread"
                    , L"sysseek", L"system", L"syswrite", L"tell", L"telldir", L"tie", L"tied", L"time", L"times", L"tr", L"truncate", L"uc"
                    , L"ucfirst", L"umask", L"undef", L"unless", L"unlink", L"unpack", L"unshift", L"untie", L"until", L"use", L"utime", L"values", L"vars"
                    , L"vec", L"wait", L"waitpid", L"wantarray", L"warn", L"while", L"write", L"xor"};
const int KeyIndices[2729/*# range 0..2728*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 222, -1, -1, -1, -1, -1, -1, -1, -1, 201, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 203, -1, -1, -1, -1, -1, -1, -1, -1, 87, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 217, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 198
                    , 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 157, -1, -1, 167, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 58, -1, -1, -1, -1, -1, -1, -1, -1, -1, 126, -1, -1, -1, -1, -1, -1, -1, -1, 274, -1, -1, -1, -1, -1, 7, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 200, -1, 143, 275, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 254, -1, -1, -1, -1, -1, -1, -1, 118, -1, -1, -1, -1, -1, -1, 259, -1, -1, -1, -1, -1, -1, -1, -1, 114
                    , -1, -1, -1, -1, -1, -1, -1, -1, 23, -1, 237, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 148, 185, -1, -1, -1, 110, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 270, 16, -1, -1, -1, 103
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 60, 44, -1, 50, -1, -1, -1, -1, 135, -1, -1, 137, -1, -1, -1, -1, -1, -1, -1, -1, 83, -1, -1, 53, -1, -1, 63, -1, -1, -1, -1, -1, 166
                    , -1, -1, -1, -1, -1, -1, -1, 158, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 22, -1, -1, -1, -1, -1, -1, 149, 202, -1, -1, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 70, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 258, -1, -1, -1, -1, -1, -1, 204, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 277, -1, -1, -1, -1, -1, -1, -1, -1, -1, 194, -1, 41, -1, -1, 243, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 230, 71, -1, -1, -1, -1, -1, -1, 231
                    , -1, -1, -1, -1, -1, 283, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 216, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 265
                    , -1, -1, -1, -1, -1, 152, -1, -1, -1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 146, 92, -1, -1, -1, -1, -1, -1, 147, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, -1, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, 213, -1, -1, -1, 8, -1, -1, -1
                    , -1, -1, 36, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 233, -1, -1, -1, -1, 121, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 281, -1, 271, -1, -1, -1, -1, -1, -1, -1, 196, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 111, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 248, -1
                    , -1, -1, 5, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1, -1, -1, 207, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 176, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 131, -1, -1, -1, -1
                    , -1, -1, -1, 142, -1, 3, -1, -1, -1, -1, 249, 108, -1, -1, -1, -1, 133, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 211, -1, -1, -1, -1, -1, -1, 130, -1, 21, -1, -1, -1, -1, -1, -1, 225
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 287, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, 59, -1, -1, 169, -1, 82, -1, -1, 81, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, 240, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 123, -1, -1, -1, -1, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 192, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 235, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 205, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, -1, -1, 45, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, -1, -1, -1, 189, -1
                    , -1, -1, -1, -1, 187, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 246, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 105, -1, -1, -1, -1, 100, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 276, -1, -1, -1, -1, -1, -1, -1, -1, -1, 199, -1, -1, -1, -1, -1, 288, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 242, -1, -1, -1, -1, -1, -1, -1, -1, 94, -1, -1, 122, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 138, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, 284, -1, 179, 112, -1, -1, 253, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 239, 190, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 165, -1, -1, -1, -1, -1, 218, -1, -1, -1, 106, -1, 75, 255, -1, -1, 97, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 191, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 279, -1, -1, -1, -1, -1, -1, 224, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 212, -1, -1, -1, -1, -1, -1, 125, -1, -1
                    , -1, 139, 267, -1, 269, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 73, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 98, 136, -1, -1, -1, -1, 90, -1, -1, -1, -1, -1, -1, -1, -1, 74, -1, -1, 263
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 278, -1, -1, 30, -1, -1, -1, -1, -1, -1, -1, -1, 159, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, 66, -1, -1, -1, -1, 32, -1, 95, 161, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 209, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 264, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 291, -1, -1, -1, -1, 61, -1, -1, -1, -1, 244, -1, 11, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 182, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 256, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 150, -1, -1, 215, 260, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 54, -1, -1, -1, -1, -1, 197, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 210, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 88, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 175, -1, -1, -1, -1, -1, -1, -1, -1, 141, -1, -1, -1, -1, -1, -1, -1, 67
                    , -1, -1, -1, -1, -1, 65, 272, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, -1, -1, 292, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 227, -1, -1, -1, -1, -1, -1, -1, -1, -1, 160, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, 56, -1, -1, -1, 49, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 57, -1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, 228, 266, 170, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 180, 234, -1, -1, -1, -1, -1, -1, 69, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 289
                    , -1, 93, -1, -1, -1, -1, 55, -1, 183, -1, -1, -1, -1, -1, 163, -1, 162, -1, -1, -1, 132, -1, -1, -1, 282, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 247, -1, 188, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 174, -1, -1, -1, 280, -1, -1, 261, 51, -1, -1, -1, -1, -1, 144, 156, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 229, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 193, 172, -1, -1, -1, -1, -1, 219, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 208, -1, -1, -1, -1, -1, -1, -1, 6, 113, -1, -1, -1, 250, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, 145, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, 168, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 186, -1, 151, -1, -1, -1, 153
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 24, -1, -1, -1, -1, -1, 251, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 184, -1, 262, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 140
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 68, 238, -1, -1, -1, -1, 221, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 173, -1, -1, -1, 104, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 223, -1, 101, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 76, -1, -1
                    , -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, -1, -1, 294, -1, 85, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1
                    , 37, -1, -1, -1, -1, 220, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, 178, -1, -1, -1, -1, -1, -1, -1, -1, 293, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, 252, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 285, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 232, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, 43, 117, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 120, -1, 128, 48, -1, -1, -1, -1, -1, -1, -1, 47, -1, -1, -1, 39, 127, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 268
                    , -1, -1, -1, -1, -1, -1, 86, -1, -1, -1, -1, -1, -1, 89, -1, 236, -1, -1, -1, -1, -1, -1, 13, -1, -1, -1, -1, -1, 96, 155, -1, -1, -1, -1, -1, -1, -1, -1, -1, 286, -1, -1, -1, -1, -1, -1, -1, -1, 33
                    , 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 195, 80, 62, -1, -1, -1, 290, -1, -1, -1, -1, 26, -1, -1, -1, -1, -1, 115, -1, -1, 91, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 134, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 245, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, -1, 171, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 214, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 295, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 273, -1, -1, -1, 181, -1, -1, -1, -1, 116, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 226, 257, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 241, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 206, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, -1, 102, -1, -1, 79, -1, -1, -1, -1, -1, -1, 84, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 177, -1, -1, -1, -1, -1, -1, -1, 154, -1, -1, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynPerlSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 714 + int((*Str)) * 970);
		++Str;
	}
	result = (unsigned int) (result % 2729);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynPerlSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkSymbol;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 2728 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynPerlSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 2728 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
		else
			fIdentFuncTable[i] = FuncKey;
	}

/*variable                                                                       //Fiala
  all functions starting FuncNN (NN = number)
*/

/*pragma
  FuncConstant;
  FuncDiagnostics;
  FuncInteger;
  FuncLess;
  FuncLocale;
  FuncSigtrap;
  FuncStrict;
  FuncSubs;
  FuncVars;
*/
/*operators
  FuncAnd;
  FuncCmp;
  FuncEq;
  FuncGe;
  FuncGt;
  FuncLe;
  FuncLt;
  FuncNe;
  FuncNot;
  FuncOr;
  FuncXor;
*/
	fIdentFuncTable[2206] = FuncVar;
	fIdentFuncTable[2446] = FuncVar;
	fIdentFuncTable[144] = FuncVar;
	fIdentFuncTable[785] = FuncVar;
	fIdentFuncTable[1434] = FuncVar;
	fIdentFuncTable[732] = FuncVar;
	fIdentFuncTable[1994] = FuncVar;
	fIdentFuncTable[184] = FuncVar;
	fIdentFuncTable[627] = FuncVar;
	fIdentFuncTable[2152] = FuncVar;
	fIdentFuncTable[91] = FuncVar;
	fIdentFuncTable[1456] = FuncVar;
	fIdentFuncTable[2529] = FuncVar;
	fIdentFuncTable[2419] = FuncVar;
	fIdentFuncTable[911] = FuncVar;
	fIdentFuncTable[637] = FuncVar;
	fIdentFuncTable[282] = FuncVar;
	fIdentFuncTable[855] = FuncVar;
	fIdentFuncTable[2243] = FuncVar;
	fIdentFuncTable[610] = FuncVar;
	fIdentFuncTable[737] = FuncVar;
	fIdentFuncTable[820] = FuncVar;
	fIdentFuncTable[354] = FuncVar;
	fIdentFuncTable[247] = FuncVar;
	fIdentFuncTable[2070] = FuncVar;
	fIdentFuncTable[1803] = FuncVar;
	fIdentFuncTable[2468] = FuncVar;
	fIdentFuncTable[1473] = FuncVar;
	fIdentFuncTable[2014] = FuncVar;
	fIdentFuncTable[1678] = FuncVar;
	fIdentFuncTable[1352] = FuncVar;
	fIdentFuncTable[1477] = FuncVar;
	fIdentFuncTable[1376] = FuncVar;
	fIdentFuncTable[2445] = FuncVar;
	fIdentFuncTable[2285] = FuncVar;
	fIdentFuncTable[2218] = FuncVar;
	fIdentFuncTable[633] = FuncVar;
	fIdentFuncTable[2250] = FuncVar;
	fIdentFuncTable[969] = FuncVar;
	fIdentFuncTable[2382] = FuncVar;
	fIdentFuncTable[1220] = FuncVar;
	fIdentFuncTable[452] = FuncVar;
	fIdentFuncTable[956] = FuncVar;
	fIdentFuncTable[2345] = FuncVar;
	fIdentFuncTable[304] = FuncVar;
	fIdentFuncTable[959] = FuncVar;
	fIdentFuncTable[2183] = FuncVar;
	fIdentFuncTable[2378] = FuncVar;
	fIdentFuncTable[2370] = FuncVar;
	fIdentFuncTable[1773] = FuncVar;
	fIdentFuncTable[306] = FuncVar;
	fIdentFuncTable[1927] = FuncVar;
	fIdentFuncTable[2342] = FuncVar;
	fIdentFuncTable[326] = FuncVar;
	fIdentFuncTable[2112] = FuncPragma;
	fIdentFuncTable[2197] = FuncPragma;
	fIdentFuncTable[263] = FuncPragma;
	fIdentFuncTable[343] = FuncPragma;
	fIdentFuncTable[1878] = FuncPragma;
	fIdentFuncTable[2638] = FuncPragma;
	fIdentFuncTable[214] = FuncPragma;
	fIdentFuncTable[396] = FuncPragma;
	fIdentFuncTable[838] = FuncPragma;
	fIdentFuncTable[1795] = FuncOperator;
	fIdentFuncTable[1371] = FuncOperator;
	fIdentFuncTable[1302] = FuncOperator;
	fIdentFuncTable[2135] = FuncOperator;
	fIdentFuncTable[311] = FuncOperator;
	fIdentFuncTable[1934] = FuncOperator;
	fIdentFuncTable[110] = FuncOperator;
	fIdentFuncTable[762] = FuncOperator;
	fIdentFuncTable[1129] = FuncOperator;
	fIdentFuncTable[1870] = FuncOperator;
	fIdentFuncTable[2564] = FuncOperator;
}

TtkTokenKind __fastcall TSynPerlSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkSymbol;
	result = tkIdentifier;
	return result;
}

__fastcall TSynPerlSyn::TSynPerlSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkSymbol),
			fCommentAttri(nullptr),
			fIdentifierAttri(nullptr),
			fInvalidAttri(nullptr),
			fKeyAttri(nullptr),
			fNumberAttri(nullptr),
			fOperatorAttri(nullptr),
			fPragmaAttri(nullptr),
			fSpaceAttri(nullptr),
			fStringAttri(nullptr),
			fSymbolAttri(nullptr),
			fVariableAttri(nullptr)
{
	FCaseSensitive = true;
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterperl__0;
	addAttribute(fCommentAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fInvalidAttri = new TSynHighlighterAttributes(SYNS_AttrIllegalChar, SYNS_FriendlyAttrIllegalChar);
	addAttribute(fInvalidAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrReservedWord, SYNS_FriendlyAttrReservedWord);
	fKeyAttri->Style = Synhighlighterperl__1;
	addAttribute(fKeyAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fOperatorAttri = new TSynHighlighterAttributes(SYNS_AttrOperator, SYNS_FriendlyAttrOperator);
	addAttribute(fOperatorAttri);
	fPragmaAttri = new TSynHighlighterAttributes(SYNS_AttrPragma, SYNS_FriendlyAttrPragma);
	fPragmaAttri->Style = Synhighlighterperl__2;
	addAttribute(fPragmaAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	fSpaceAttri->Foreground = clWindow;
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	fVariableAttri->Style = Synhighlighterperl__3;
	addAttribute(fVariableAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterPerl;
} /* Create */

void __fastcall TSynPerlSyn::AndSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*bit and assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'&':
		{
			if(fLine[Run + 2] == L'=')   /*logical and assign*/
				Run += 3;
			else
                           /*logical and*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*bit and*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::CRProc()
{
	FTokenID = tkSpace;
	switch(fLine[Run + 1])
	{
		case L'\x0a':
		Run += 2;
		break;
		default:
		++Run;
		break;
	}
}

void __fastcall TSynPerlSyn::ColonProc()
{
	switch(fLine[Run + 1])
	{
		case L':':                               /*double colon*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*colon*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::CommentProc()
{
	if((Run == 0) || (Run > 0) && (fLine[Run - 1] != L'\\'))
	{
		FTokenID = tkComment;
		do
		{
			switch(fLine[Run])
			{
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				goto label0;
				default:
				  ;
				break;
			}
			++Run;
		}
		while(!(fLine[Run] == L'\x00'));
		label0:;
	}
	else
	++Run;
}

void __fastcall TSynPerlSyn::EqualProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*logical equal*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*digraph*/
		case L'>':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*bind scalar to pattern*/
		case L'~':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*assign*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::GreaterProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*greater than or equal to*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'>':
		{
			if(fLine[Run + 2] == L'=')   /*shift right assign*/
				Run += 3;
			else
                           /*shift right*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*greater than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::IdentProc()
{
	switch(fLine[Run])
	{
		case L'$':
		{
			switch(fLine[Run + 1])
			{
				case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42:
				 case 43:
				case 45: case 46: case 47: case 48: case 49: case 50: case 51: case 52: case 53: case 54:
				 case 55: case 56: case 57: case 58: case 59: case 60: case 61: case 62: case 63: case 64:
				case 91: case 92: case 93:
				case L'_':
				case L'`':
				case L'|':
				case L'~':                      /*predefined variables*/
				{
					Run += 2;
					FTokenID = tkVariable;
					return;
				}
				case L'^':
				{
					switch(fLine[Run + 2])
					{
						case L'A':
						case L'D':
						case L'F':
						case L'I':
						case L'L':
						case L'P':
						case L'T':
						case L'W':
						case L'X':                /*predefined variables*/
						{
							Run += 3;
							FTokenID = tkVariable;
							return;
						}          /*predefined variables*/
						case L'\x00':
						case L'\x0a':
						case L'\x0d':
						{
							Run += 2;
							FTokenID = tkVariable;
							return;
						}
						default:
						  ;
						break;
					}
				}
				break;
				default:
				  ;
				break;
			}
		}
		break;
		case L'%':
		{
			switch(fLine[Run + 1])
			{
				case L'=':                         /*mod assign*/
				{
					Run += 2;
					FTokenID = tkSymbol;
					return;
				}                /*mod*/
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				{
					++Run;
					FTokenID = tkSymbol;
					return;
				}
				default:
				  ;
				break;
			}
		}
		break;
		case L'x':
		{
			switch(fLine[Run + 1])
			{
				case L'=':                         /*repetition assign*/
				{
					Run += 2;
					FTokenID = tkSymbol;
					return;
				}                /*repetition*/
				case L'\x00':
				case L'\x0a':
				case L'\x0d':
				{
					++Run;
					FTokenID = tkSymbol;
					return;
				}
				default:
				  ;
				break;
			}
		}
		break;
		default:
		  ;
		break;
	}
  /*regular identifier*/
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynPerlSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynPerlSyn::LowerProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':
		{
			if(fLine[Run + 2] == L'>')   /*compare - less than, equal, greater*/
				Run += 3;
			else
                           /*less than or equal to*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'<':
		{
			if(fLine[Run + 2] == L'=')   /*shift left assign*/
				Run += 3;
			else
                           /*shift left*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*less than*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::MinusProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*subtract assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*decrement*/
		case L'-':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*arrow*/
		case L'>':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*subtract*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::NotSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'~':                               /*logical negated bind like =~*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*not equal*/
		case L'=':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*not*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynPerlSyn::NumberProc()
{

	auto IsNumberChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case L'-':
			case L'_':
			case L'.':
			case 65: case 66: case 67: case 68: case 69: case 70:
			case 97: case 98: case 99: case 100: case 101: case 102:
			case L'x':
			case L'X':
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
	if(fLine[Run] == L'.')
	{
		switch(fLine[Run + 1])
		{
			case L'.':
			{
				Run += 2;
				if(fLine[Run] == L'.')     /*sed range*/
					++Run;
				FTokenID = tkSymbol;        /*range*/
				return;
			}
			case L'=':
			{
				Run += 2;
				FTokenID = tkSymbol;        /*concatenation assign*/
				return;
			}
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case L'_':
			{
				FTokenID = tkSymbol;        /*concatenation*/
				++Run;
				return;
			}
			default:
			  ;
			break;
		}
	}
	++Run;
	FTokenID = tkNumber;
	while(IsNumberChar())
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label1;
			break;                             /*check for e notation*/
			case L'-':
			if(!((fLine[Run + 1] == L'e') || (fLine[Run + 1] == L'E')))
				goto label2;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label1:;
	label2:;
}

void __fastcall TSynPerlSyn::OrSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*bit or assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'|':
		{
			if(fLine[Run + 2] == L'=')   /*logical or assign*/
				Run += 3;
			else
                           /*logical or*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*bit or*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::PlusProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*add assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                               /*increment*/
		case L'+':
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*add*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}                                            //Fiala

void __fastcall TSynPerlSyn::qFunctionProc()
{
	Char myBracket = L'\0';

	auto GetFirstBracket = [&]() -> Char 
	{
		Char result = L'\0';
		int i = 0;
		result = L'\x00';
		i = Run + 1;
		while(!IsLineEnd(i))
		{
			if(CharInSet(fLine[i], Synhighlighterperl__4))
				switch(fLine[i])
				{
        /* we will return opening bracket */
					case L'(':
					{
						result = L')';
						goto label3;
					}
					case L'{':
					{
						result = L'}';
						goto label4;
					}
					default:
					  ;
					break;
				}
      /* when other than opening bracket or space, we will stop */
			else
				break;
			++i;
		}
		label3:;
		label4:;
		return result;
	};
  /* qfunction */
//  myBracket := GetFirstBracket;
//  if ((Run = 0) or (Run > 0) and (FLine[Run-1] = ' ')) and (myBracket <> #0) then
	if((fLine[Run + 1] == L'q') && (fLine[Run + 2] == L'(') || (fLine[Run + 1] == L'('))
	{
		myBracket = L')';
		FTokenID = tkString;
		do
		{
			++Run;
		}
		while(!((fLine[Run] == myBracket) || IsLineEnd(Run)));
		if(!IsLineEnd(Run))
			++Run;
	}
	else

  /* standard identifier */
	{
		FTokenID = tkIdentifier;
		++Run;
	}
}

void __fastcall TSynPerlSyn::SlashProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*division assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*division*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::SpaceProc()
{
	++Run;
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynPerlSyn::StarProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*multiply assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;
		case L'*':
		{
			if(fLine[Run + 2] == L'=')   /*exponentiation assign*/
				Run += 3;
			else
                           /*exponentiation*/
				Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*multiply*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::StringInterpProc()
{
	int fBackslashCount = 0;
  /* modification for first quote is backshlashed */
	if((FRange == rsUnKnown) && (fLine[Run - 1] == L'\\'))                      // Fiala
	{
		++Run;
		FTokenID = tkSymbol;
		return;
	}
	FTokenID = tkString;
	if(FRange == rsUnKnown)
		FRange = rsString;
	else
		++Run;
	if((fLine[Run + 1] == L'\x22') && (fLine[Run + 2] == L'\x22'))
		Run += 2;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label5;
        /* If we're looking at a backslash, and the following character is an
          end quote, and it's preceeded by an odd number of backslashes, then
          it shouldn't mark the end of the string.  If it's preceeded by an
          even number, then it should. */
			case L'\x5c':
			if(fLine[Run + 1] == L'\x22')
			{
				fBackslashCount = 1;
				while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\x5c')))
					fBackslashCount = fBackslashCount + 1;
				if(fBackslashCount % 2 == 1)
					++Run;
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x22'));
	label5:;
	if(fLine[Run] == L'\x22')
		FRange = rsUnKnown;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynPerlSyn::StringLiteralProc()
{
	FTokenID = tkString;
	do
	{
		switch(fLine[Run])
		{
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label6;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!(fLine[Run] == L'\x27'));
	label6:;
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynPerlSyn::SymbolProc()
{
	if((Run == 0) || (Run > 0) && (fLine[Run - 1] != L'\\'))
		FTokenID = tkSymbol;
	else
		FTokenID = tkUnknown;
	++Run;
}

void __fastcall TSynPerlSyn::XOrSymbolProc()
{
	switch(fLine[Run + 1])
	{
		case L'=':                               /*xor assign*/
		{
			Run += 2;
			FTokenID = tkSymbol;
		}
		break;                                 /*xor*/
		default:
		{
			++Run;
			FTokenID = tkSymbol;
		}
		break;
	}
}

void __fastcall TSynPerlSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynPerlSyn::Next()
{
	fTokenPos = Run;
	if(!IsLineEnd(Run) && (FRange == rsString))
	{
		StringEndProc();
	}
	else
	switch(fLine[Run])
	{
		case L'&':
		AndSymbolProc();
		break;
		case L'\x0d':
		CRProc();
		break;
		case L':':
		ColonProc();
		break;
		case L'#':
		CommentProc();
		break;
		case L'=':
		EqualProc();
		break;
		case L'>':
		GreaterProc();
		break;
//    '%', '@', '$', 'A'..'Z', 'a'..'z', '_': IdentProc;
		case L'$':
		case L'%':
		case L'@':
		VariableProc();
		break;
		case L'q':
		qFunctionProc();
		break;                                                         //Fiala
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112:
		case 114: case 115: case 116: case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		IdentProc();
		break;                               //Fiala
		case L'\x0a':
		LFProc();
		break;
		case L'<':
		LowerProc();
		break;
		case L'-':
		MinusProc();
		break;
		case L'!':
		NotSymbolProc();
		break;
		case L'\x00':
		NullProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		case L'.':
		NumberProc();
		break;
		case L'|':
		OrSymbolProc();
		break;
		case L'+':
		PlusProc();
		break;
		case L'/':
		SlashProc();
		break;
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'*':
		StarProc();
		break;
		case L'\"':
		StringInterpProc();
		break;
		case L'\x27':
		StringLiteralProc();
		break;
		case L'^':
		XOrSymbolProc();
		break;
		case L'(':
		case L')':
		case L'[':
		case L']':
		case L'\\':
		case L'{':
		case L'}':
		case L',':
		case L';':
		case L'?':
		case L'~':
		SymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynPerlSyn::GetDefaultAttribute(int Index)
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
		case SYN_ATTR_SYMBOL:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

bool __fastcall TSynPerlSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynPerlSyn::GetTokenID()
{
	TtkTokenKind result = tkSymbol;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynPerlSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(FTokenID)
	{
		case tkComment:
		result = fCommentAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkOperator:
		result = fOperatorAttri;
		break;
		case tkPragma:
		result = fPragmaAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fInvalidAttri;
		break;
		case tkVariable:
		result = fVariableAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynPerlSyn::GetTokenKind()
{
	int result = 0;
	result = int(FTokenID);
	return result;
}

String __fastcall TSynPerlSyn::GetSampleSource()
{
	String result;
	result = L"#!/bin/perl\x0d\x0a"
	           L"require \"cgi-lib.pl\";\x0d\x0a"
	           L"use sigtrap;\x0d\x0a"
	           L"do 'envars.pl';\x0d\x0a"
	           L"$_ = $password1;\x0d\x0a"
	           L"sub WriteBack {\x0d\x0a"
	           L"        while ($_ ne \"fred\")    {\x0d\x0a"
	           L"                sleep 5;\x0d\x0a"
	           L"        }\x0d\x0a"
	           L"}";
	return result;
}

bool __fastcall TSynPerlSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterPerl;
	return result;
}

bool __fastcall TSynPerlSyn::IsIdentChar(WideChar AChar)
{
	bool result = false; //Fiala
	result = IsCharAlphaNumeric(AChar) || CharInSet(AChar, Synhighlighterperl__5);
	return result;
}

/*#static*/
String __fastcall TSynPerlSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangPerl;
	return result;
}

/*#static*/
String __fastcall TSynPerlSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangPerl;
	return result;
}

/*begin*/                                                                         //Fiala

void __fastcall TSynPerlSyn::VariableProc()
{

  /* $" is Perl vaiable */                                                        //Fiala
	if(CharInSet(fLine[Run + 1], Synhighlighterperl__6))
	{
		FTokenID = tkVariable;
		Run += 2;
		while(CharInSet(fLine[Run], Synhighlighterperl__7))
			++Run;
	}
	else
	IdentProc();
}

TtkTokenKind __fastcall TSynPerlSyn::FuncVar(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkVariable;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPerlSyn::FuncKey(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPerlSyn::FuncOperator(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkOperator;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynPerlSyn::FuncPragma(int Index)
{
	TtkTokenKind result = tkSymbol;
	if(IsCurrentToken(Keywords[Index]))
		result = tkPragma;
	else
		result = tkIdentifier;
	return result;
}
/*end*/                                                                           //Fiala
                 //Fiala

bool __fastcall TSynPerlSyn::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	switch(AChar)
	{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		 case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
		 case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
		 case 30: case 31: case 32:
		case L'.':
		case L',':
		case L';':
		case L':':
		case L'\"':
		case L'\'':
		case L'+':
		case L'`':
		case L'-':
		case L'^':
		case L'!':
		case L'?':
		case L'&':
		case L'§':
		case L'#':
		case L'~':
		case L'[':
		case L']':
		case L'(':
		case L')':
		case L'{':
		case L'}':
		case L'<':
		case L'>':
		case L'=':
		case L'*':
		case L'/':
		case L'\\':
		case L'|':
		result = true;
		break;
		default:
		result = false;
		break;
	}
	return result;
}                                         //Fiala

void* __fastcall TSynPerlSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}                                               //Fiala

void __fastcall TSynPerlSyn::ResetRange()
{
	FRange = rsUnKnown;
}

//++ CodeFolding

void __fastcall TSynPerlSyn::ScanForFoldRanges(TSynFoldRanges* FoldRanges, TStrings* LinesToScan, int FromLine, int ToLine)
{
	String CurLine;
	__int64 Line = 0;

	auto LineHasChar = [&](int Line, Char Character, int StartCol) -> bool 
	{
		bool result = false;
		int i = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), i = StartCol; i <= stop; i++)
		{
			if(CurLine[i] == Character)
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, i) != fCommentAttri)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}; // faster than Pos!

	auto FindBraces = [&](int Line) -> bool 
	{
		bool result = false;
		int Col = 0;
		int stop = 0;
		result = false;
		for(stop = CurLine.Length(), Col = 1; Col <= stop; Col++)
		{
      // We've found a starting character
			if(CurLine[Col] == L'{')
        // Char must have proper highlighting (ignore stuff inside comments...)
			{
				if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != fCommentAttri)
          // And ignore lines with both opening and closing chars in them
				{
					if(!LineHasChar(Line, L'}', Col + 1))
					{
						FoldRanges->StartFoldRange(Line + 1, 1);
						result = true;
					}
          // Skip until a newline
					break;
				}
			}
			else
			{
				if(CurLine[Col] == L'}')
				{
					if(GetHighlighterAttriAtRowCol(LinesToScan, Line, Col) != fCommentAttri)
          // And ignore lines with both opening and closing chars in them
					{
						if(!LineHasChar(Line, L'{', Col + 1))
						{
							FoldRanges->StopFoldRange(Line + 1, 1);
							result = true;
						}
          // Skip until a newline
						break;
					}
				}
			}
		} // for Col
		return result;
	};

	auto FoldRegion = [&](int Line) -> bool 
	{
		bool result = false;
		String s;
		result = false;
		s = TrimLeft(CurLine);
		if(UpperCase(s.SubString(1, 9)) == L"#REGION")
		{
			FoldRanges->StartFoldRange(Line + 1, FoldRegionType);
			result = true;
		}
		else
		{
			if(UpperCase(s.SubString(1, 12)) == L"#ENDREGION")
			{
				FoldRanges->StopFoldRange(Line + 1, FoldRegionType);
				result = true;
			}
		}
		return result;
	};
	__int64 stop = 0;
	for(stop = ToLine, Line = FromLine; Line <= stop; Line++)
	{
		CurLine = LinesToScan->Strings[Line];

    // Skip empty lines
		if(CurLine == L"")
		{
			FoldRanges->NoFoldInfo((int) (Line + 1));
			continue;
		}

    // Find Fold regions
		if(FoldRegion((int) Line))
			continue;

    // Find an braces on this line  (Fold Type 1)
		if(!FindBraces((int) Line))
			FoldRanges->NoFoldInfo((int) (Line + 1));
	} // while Line
}
//-- CodeFolding
                                 //Fiala

void __fastcall TSynPerlSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}                                            //Fiala

void __fastcall TSynPerlSyn::StringEndProc()
{
	int fBackslashCount = 0;
	FTokenID = tkString;
	do
	{
		switch(fLine[Run])
		{
			case L'\x22':
			{
				++Run;
				FRange = rsUnKnown;
				goto label7;
			}
			case L'\x00':
			case L'\x0a':
			case L'\x0d':
			goto label8;
        /* If we're looking at a backslash, and the following character is an
          end quote, and it's preceeded by an odd number of backslashes, then
          it shouldn't mark the end of the string.  If it's preceeded by an
          even number, then it should. */
			case L'\x5c':
			if(fLine[Run + 1] == L'\x22')
			{
				fBackslashCount = 1;
				while(((Run > fBackslashCount) && (fLine[Run - fBackslashCount] == L'\x5c')))
					fBackslashCount = fBackslashCount + 1;
				if(fBackslashCount % 2 == 1)
					++Run;
			}
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	while(!IsLineEnd(Run));
	label7:;
	label8:;
}
static bool SynHighlighterPerl_Initialized = false;

void SynHighlighterPerl_initialization()
{
	if(SynHighlighterPerl_Initialized)
		return;
	
	SynHighlighterPerl_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynPerlSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterPerl

