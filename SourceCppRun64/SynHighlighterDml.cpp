
#include <vcl.h>
#pragma hdrstop

#include "SynHighlighterDml.h"
#include "SynEditStrConst.h"

using namespace std;
using namespace d2c_system;
using namespace Synedithighlighter;
using namespace Syneditstrconst;
using namespace System;
using namespace Vcl::Graphics;

namespace Synhighlighterdml
{
#define Synhighlighterdml__0 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdml__1 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdml__2 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdml__3 (TFontStyles() << TFontStyle::fsBold)
#define Synhighlighterdml__4 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdml__5 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdml__6 (TFontStyles() << TFontStyle::fsBold << TFontStyle::fsItalic)
#define Synhighlighterdml__7 (TFontStyles() << TFontStyle::fsItalic)
#define Synhighlighterdml__8 (TSysCharSet() <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57 << '.')
#define Synhighlighterdml__9 (TSysCharSet() << '\x09' << '\x20')


const String Keywords[264/*# range 0..263*/] = {L"abs", L"absolute_position", L"account", L"acos", L"actual_break", L"add", L"add_form", L"alternate_form", L"ascii"
                    , L"asin", L"atan", L"atan2", L"attributes", L"back", L"base", L"batch", L"begin_block", L"begin_case", L"begin_disable_trigger", L"begin_row"
                    , L"begin_signal_to_status", L"bell", L"binary_to_poly", L"bottom_line", L"break", L"break0", L"call", L"case", L"ceil"
                    , L"check", L"check_domain", L"chr", L"clear_buffer", L"cli", L"close", L"close_text", L"col", L"column_heading_row", L"column_headings"
                    , L"column_spacing", L"commit", L"commit_rate", L"compile", L"compress", L"compress_all", L"confirm", L"connect"
                    , L"continue", L"cos", L"cosh", L"cross_reference", L"date", L"date_seconds", L"day_of_week", L"days", L"dcl", L"default_tag"
                    , L"delete", L"delete_form", L"description", L"dir", L"disconnect", L"display", L"display_length", L"documentation", L"domain"
                    , L"edit", L"else", L"else_if", L"end_block", L"end_case", L"end_disable_trigger", L"end_execute", L"end_form", L"end_if"
                    , L"end_row", L"end_signal_to_status", L"end_while", L"erase", L"error", L"execute", L"exit", L"exit_forward", L"expand"
                    , L"external", L"facility", L"failure", L"fetch", L"files", L"find", L"find_form", L"finish", L"first", L"floor", L"footing"
                    , L"footing_form", L"form", L"generate", L"goto", L"grouped_by", L"heading", L"heading_form", L"height", L"identifier", L"if"
                    , L"in", L"input_block", L"input_mask", L"input_row_height", L"int", L"invoke", L"item", L"item_block", L"item_if", L"joined_to"
                    , L"left", L"len", L"lfooting", L"lheading", L"line", L"lines_after", L"lines_before", L"list", L"load", L"lock", L"log"
                    , L"log10", L"lov", L"lov_auto_select", L"lov_col", L"lov_data", L"lov_first", L"lov_height", L"lov_noheading", L"lov_nosearch", L"lov_reduced_to"
                    , L"lov_row", L"lov_secondary", L"lov_selection", L"lov_sorted_by", L"lov_width", L"lov_with", L"lowercase", L"ltrim"
                    , L"mail", L"menu", L"menu_block", L"menu_form", L"message", L"mid", L"mod", L"modify_form", L"new", L"no_domain", L"nobell"
                    , L"noclear_buffer", L"nodeadlock_exit", L"noerase", L"noerror", L"noexit_forward", L"noheading", L"nolov_data", L"norepeat"
                    , L"nostatus", L"nototals", L"nounderlines", L"nowait", L"open", L"open_text", L"opt", L"options", L"output", L"output_block"
                    , L"output_mask", L"pause", L"pause_block", L"perform", L"poly_to_binary", L"pos", L"print", L"procedure_form", L"prompt"
                    , L"protect", L"query", L"query_form", L"random", L"read_line", L"read_only", L"receive", L"receive_arguments", L"receive_data"
                    , L"receive_table", L"reduced_to", L"release", L"remain", L"repeat", L"report", L"report_form", L"reposition", L"rewind_text"
                    , L"rfooting", L"rheading", L"right", L"rollback", L"round", L"row", L"row_height", L"search", L"secondary", L"seconds"
                    , L"selection", L"send", L"send_data", L"send_message", L"send_table", L"sequence", L"severity", L"sin", L"sinh", L"sorted_by"
                    , L"source", L"source_if", L"sqrt", L"start_stream", L"start_transaction", L"statistic", L"status", L"stream_name", L"string"
                    , L"success", L"switch", L"switch_base", L"system", L"table", L"table_form", L"table_search", L"tag", L"tag_length", L"tan"
                    , L"tanh", L"target", L"text", L"text_only", L"title", L"to", L"top_line", L"total", L"transfer", L"trigger", L"trim", L"tsuppress"
                    , L"unload", L"uppercase", L"use_if", L"user_key", L"using", L"utilities", L"wait", L"while", L"width", L"with", L"write"
                    , L"write_line", L"yesno_block"};
const int KeyIndices[2439/*# range 0..2438*/] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 261, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 230, -1
                    , 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 217, -1, -1, -1, -1, -1, 183, -1, 246, -1, 134, -1, -1, -1, -1, -1, 65, -1, -1, 223, -1, -1, -1, -1, -1, 213, -1, -1, -1
                    , 46, -1, -1, 262, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 124, -1, -1, -1, -1, -1, -1, -1, -1, -1, 111, 157, -1, -1
                    , -1, -1, -1, -1, 118, -1, -1, -1, -1, -1, -1, -1, -1, 208, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 22, -1, -1, -1, -1, -1, -1, -1, -1, -1, 86, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 123, 102, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 84, -1, 154, -1, 96, -1, -1, -1, 176, -1, -1, -1, 120, 178, -1, -1, -1, -1, 74, -1, -1, -1, -1, 241, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 81, -1, 147, -1, -1, -1, 122, -1, 58, -1, 87, 191, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, 170, -1, -1, -1, -1, -1, -1, -1, -1, -1, 5, -1, -1, 194, -1, -1, -1, 243, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 52, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 248
                    , -1, -1, -1, 28, 77, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 255, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 239, -1
                    , -1, -1, -1, 20, -1, -1, -1, -1, 79, 116, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 192, -1, -1, -1, -1, -1, -1, -1, -1, -1, 109, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 0, -1, -1, -1, 119, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 196, -1, -1, 85, -1, -1, -1, 104, -1, 103, -1, -1, 14, -1, -1, 131, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 105, -1, -1, 6, -1, 182, -1, -1, 171, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 80, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 97, -1, -1, -1, -1, 41, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, 142, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 204, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 185, -1, -1, -1, -1, -1
                    , -1, -1, 115, -1, -1, 108, -1, 150, -1, -1, 42, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 224, -1, -1, -1, 59, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 143, 166, -1, -1, -1, -1, -1, -1, 225, -1, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, 92, -1, -1, 226, -1, 161, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 40, -1, -1, -1, -1, -1, -1, -1, 237, -1, -1, -1, -1, -1, 100, -1, -1, -1, -1, -1, -1, -1, -1, 214, -1, -1, -1, -1, -1, -1
                    , -1, -1, 151, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1, -1, 146, 210, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 23
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 245, -1, -1, -1, -1, -1, 68, -1, 231, -1, -1, -1, 126, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 57, -1, -1, -1, 112, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 7, -1, -1, 75, -1, 252, 212, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 149, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 187, -1, -1, -1, -1, -1, -1, -1, 78, -1, -1, -1, -1, 47, -1, -1, -1, -1, -1, -1, -1, -1, 164, 35, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, 234, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 107, -1, -1, -1, -1, -1, -1, 50, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 240
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 39, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 72, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21, -1, -1, 229, 11, -1, -1, 43, -1, -1, -1, -1, -1, 236, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 159, -1, -1, 238, -1, -1, -1, -1, -1, -1, -1, -1, -1, 181, -1, 139, -1, -1, -1, -1, -1, -1, 37, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 83, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 69, 258, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 101, -1
                    , -1, 153, -1, -1, 36, -1, -1, 175, -1, -1, -1, -1, -1, -1, -1, -1, 89, -1, -1, -1, -1, -1, -1, -1, -1, 48, -1, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, 232, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 199, -1, -1, -1, -1, -1, 9, -1, -1, 140, 193, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, 82, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 177, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 163, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 188, -1, -1, -1, -1, -1, 44, -1, -1, -1, -1, -1, -1, -1, -1, 228, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, -1, 66, -1, -1, -1, 24, -1, -1, -1, -1, 186, -1, -1, -1, -1, 99, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 67, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 253, -1, -1, -1, -1, -1, -1, -1, -1, -1, 54, -1, -1, -1, -1, 259, -1, 32, -1, -1, -1, -1, -1, 121, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, 221, 209, 260, -1, -1, -1, -1, -1, -1, -1, 76, 257, -1, -1, -1, -1, 211, -1, 90, -1, -1, -1, -1, -1, -1, 133, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, 70, -1, -1, -1, -1, -1, 63
                    , -1, -1, -1, 25, 207, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 174, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 167, -1, -1, -1, -1, -1, -1, -1, -1, 179
                    , -1, 189, -1, -1, -1, 113, -1, -1, -1, 110, -1, 205, -1, 56, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 51, -1, -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, 132, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 117, -1, -1, -1, -1, -1, -1, -1, -1, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 180, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 71, -1, 254, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 49, -1, -1, -1, -1, -1, -1, -1, -1, 155, -1, -1, 235, -1, 34, -1, 218, -1, -1, -1
                    , -1, -1, -1, 152, -1, -1, -1, -1, 220, -1, -1, -1, 141, -1, -1, -1, -1, 195, -1, -1, -1, 137, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 129, -1, -1, -1, -1, 160, -1, -1
                    , -1, -1, 227, -1, -1, -1, -1, -1, -1, -1, 148, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 203, -1, -1, -1, -1, -1, -1, -1, -1, 156, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, 91, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 219, -1, -1, -1
                    , -1, -1, 61, -1, -1, 30, -1, -1, 130, -1, -1, -1, -1, -1, -1, -1, -1, 12, -1, 202, -1, -1, -1, -1, -1, 200, -1, -1, 169, -1, -1, -1, -1, -1, -1, 16, -1, -1, -1, 172, -1, -1, -1, -1, -1, -1, 162, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 114, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 247, -1, -1, -1, -1, -1, -1, 242, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 198, -1, -1, -1, 251, -1, -1, -1, -1, -1, -1, -1, -1, 216, -1, -1, -1, -1, 128, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, 158, -1, -1, -1, -1, -1, -1, -1, 93, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 88, -1, 173
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 73, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, 135, -1, -1, 190, -1, -1, -1, 222, 60, -1, -1, -1, -1, -1, -1, -1, -1, 106, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 98, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , 136, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 168, -1, -1, -1, -1, -1, -1, 144, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 94, -1, 95, -1, -1, -1, -1, -1, 215, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 145, -1, -1, -1, 10, 250, -1, -1, -1, 256
                    , -1, -1, -1, -1, -1, -1, -1, -1, -1, 197, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 201, -1, -1, -1, 233, -1, -1, -1, -1, -1, 249, -1, -1, 184, -1, -1, -1, -1, -1, 263, -1, -1
                    , -1, -1, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26, 138, -1, -1, -1, -1, -1, -1, -1, -1, 64, -1, -1, -1, 55, -1, -1, -1, -1, -1, -1, -1, -1
                    , -1, -1, 3, 127, 206, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 165, -1, -1, 244, -1, -1, -1, -1, -1, -1, -1, -1};

/*$Q-*/

unsigned int __fastcall TSynDmlSyn::HashKey(PWideChar Str)
{
	unsigned int result = 0;
	result = 0;
	while(IsIdentChar((*Str)))
	{
		result = (unsigned int) (result * 798 + int((*Str)) * 3);
		++Str;
	}
	result = (unsigned int) (result % 2439);
	fStringLen = Str - fToIdent;
	return result;
}
/*$Q+*/

TtkTokenKind __fastcall TSynDmlSyn::IdentKind(PWideChar Maybe)
{
	TtkTokenKind result = tkBlock;
	unsigned int key = 0;
	fToIdent = Maybe;
	key = HashKey(Maybe);
	if(key <= 2438 /*# High(fIdentFuncTable) */)
		result = fIdentFuncTable[key](KeyIndices[key]);
	else
		result = tkIdentifier;
	return result;
}

void __fastcall TSynDmlSyn::InitIdent()
{
	int i = 0;
	int stop = 0;
	for(stop = 2438 /*# High(fIdentFuncTable) */, i = 0 /*# Low(fIdentFuncTable) */; i <= stop; i++)
	{
		if(KeyIndices[i] == -1)
			fIdentFuncTable[i] = AltFunc;
	}
	fIdentFuncTable[435] = FuncAbs;
	fIdentFuncTable[41] = FuncAbsolute_position;
	fIdentFuncTable[13] = FuncAccount;
	fIdentFuncTable[2405] = FuncAcos;
	fIdentFuncTable[1707] = FuncActual_break;
	fIdentFuncTable[300] = FuncAdd;
	fIdentFuncTable[486] = FuncAdd_form;
	fIdentFuncTable[839] = FuncAlternate_form;
	fIdentFuncTable[735] = FuncAscii;
	fIdentFuncTable[1265] = FuncAsin;
	fIdentFuncTable[2300] = FuncAtan;
	fIdentFuncTable[1065] = FuncAtan2;
	fIdentFuncTable[1930] = FuncAttributes;
	fIdentFuncTable[1202] = FuncBack;
	fIdentFuncTable[464] = FuncBase;
	fIdentFuncTable[1118] = FuncBatch;
	fIdentFuncTable[1948] = FuncBegin_block;
	fIdentFuncTable[2124] = FuncBegin_case;
	fIdentFuncTable[2068] = FuncBegin_disable_trigger;
	fIdentFuncTable[1385] = FuncBegin_row;
	fIdentFuncTable[387] = FuncBegin_signal_to_status;
	fIdentFuncTable[1061] = FuncBell;
	fIdentFuncTable[166] = FuncBinary_to_poly;
	fIdentFuncTable[776] = FuncBottom_line;
	fIdentFuncTable[1391] = FuncBreak;
	fIdentFuncTable[1524] = FuncBreak0;
	fIdentFuncTable[2380] = FuncCall;
	fIdentFuncTable[2044] = FuncCase;
	fIdentFuncTable[337] = FuncCeil;
	fIdentFuncTable[644] = FuncCheck;
	fIdentFuncTable[1918] = FuncCheck_domain;
	fIdentFuncTable[1512] = FuncChr;
	fIdentFuncTable[1454] = FuncClear_buffer;
	fIdentFuncTable[1305] = FuncCli;
	fIdentFuncTable[1761] = FuncClose;
	fIdentFuncTable[908] = FuncClose_text;
	fIdentFuncTable[1179] = FuncCol;
	fIdentFuncTable[1114] = FuncColumn_heading_row;
	fIdentFuncTable[2183] = FuncColumn_headings;
	fIdentFuncTable[1007] = FuncColumn_spacing;
	fIdentFuncTable[697] = FuncCommit;
	fIdentFuncTable[521] = FuncCommit_rate;
	fIdentFuncTable[591] = FuncCompile;
	fIdentFuncTable[1068] = FuncCompress;
	fIdentFuncTable[1359] = FuncCompress_all;
	fIdentFuncTable[1637] = FuncConfirm;
	fIdentFuncTable[89] = FuncConnect;
	fIdentFuncTable[898] = FuncContinue;
	fIdentFuncTable[1200] = FuncCos;
	fIdentFuncTable[1747] = FuncCosh;
	fIdentFuncTable[954] = FuncCross_reference;
	fIdentFuncTable[1630] = FuncDate;
	fIdentFuncTable[320] = FuncDate_seconds;
	fIdentFuncTable[368] = FuncDay_of_week;
	fIdentFuncTable[1447] = FuncDays;
	fIdentFuncTable[2394] = FuncDcl;
	fIdentFuncTable[1583] = FuncDefault_tag;
	fIdentFuncTable[820] = FuncDelete;
	fIdentFuncTable[261] = FuncDelete_form;
	fIdentFuncTable[608] = FuncDescription;
	fIdentFuncTable[2142] = FuncDir;
	fIdentFuncTable[1915] = FuncDisconnect;
	fIdentFuncTable[1889] = FuncDisplay;
	fIdentFuncTable[1520] = FuncDisplay_length;
	fIdentFuncTable[2390] = FuncDocumentation;
	fIdentFuncTable[76] = FuncDomain;
	fIdentFuncTable[1387] = FuncEdit;
	fIdentFuncTable[1414] = FuncElse;
	fIdentFuncTable[801] = FuncElse_if;
	fIdentFuncTable[1158] = FuncEnd_block;
	fIdentFuncTable[1514] = FuncEnd_case;
	fIdentFuncTable[1734] = FuncEnd_disable_trigger;
	fIdentFuncTable[1043] = FuncEnd_execute;
	fIdentFuncTable[2119] = FuncEnd_form;
	fIdentFuncTable[224] = FuncEnd_if;
	fIdentFuncTable[842] = FuncEnd_row;
	fIdentFuncTable[1484] = FuncEnd_signal_to_status;
	fIdentFuncTable[338] = FuncEnd_while;
	fIdentFuncTable[893] = FuncErase;
	fIdentFuncTable[392] = FuncError;
	fIdentFuncTable[503] = FuncExecute;
	fIdentFuncTable[253] = FuncExit;
	fIdentFuncTable[1280] = FuncExit_forward;
	fIdentFuncTable[1146] = FuncExpand;
	fIdentFuncTable[206] = FuncExternal;
	fIdentFuncTable[455] = FuncFacility;
	fIdentFuncTable[176] = FuncFailure;
	fIdentFuncTable[263] = FuncFetch;
	fIdentFuncTable[2106] = FuncFiles;
	fIdentFuncTable[1191] = FuncFind;
	fIdentFuncTable[1492] = FuncFind_form;
	fIdentFuncTable[1868] = FuncFinish;
	fIdentFuncTable[651] = FuncFirst;
	fIdentFuncTable[2081] = FuncFloor;
	fIdentFuncTable[2267] = FuncFooting;
	fIdentFuncTable[2269] = FuncFooting_form;
	fIdentFuncTable[210] = FuncForm;
	fIdentFuncTable[516] = FuncGenerate;
	fIdentFuncTable[2196] = FuncGoto;
	fIdentFuncTable[1401] = FuncGrouped_by;
	fIdentFuncTable[711] = FuncHeading;
	fIdentFuncTable[1173] = FuncHeading_form;
	fIdentFuncTable[194] = FuncHeight;
	fIdentFuncTable[461] = FuncIdentifier;
	fIdentFuncTable[459] = FuncIf;
	fIdentFuncTable[483] = FuncIn;
	fIdentFuncTable[2151] = FuncInput_block;
	fIdentFuncTable[947] = FuncInput_mask;
	fIdentFuncTable[586] = FuncInput_row_height;
	fIdentFuncTable[420] = FuncInt;
	fIdentFuncTable[1579] = FuncInvoke;
	fIdentFuncTable[134] = FuncItem;
	fIdentFuncTable[824] = FuncItem_block;
	fIdentFuncTable[1575] = FuncItem_if;
	fIdentFuncTable[1988] = FuncJoined_to;
	fIdentFuncTable[583] = FuncLeft;
	fIdentFuncTable[393] = FuncLen;
	fIdentFuncTable[1698] = FuncLfooting;
	fIdentFuncTable[142] = FuncLheading;
	fIdentFuncTable[439] = FuncLine;
	fIdentFuncTable[218] = FuncLines_after;
	fIdentFuncTable[1460] = FuncLines_before;
	fIdentFuncTable[259] = FuncList;
	fIdentFuncTable[193] = FuncLoad;
	fIdentFuncTable[124] = FuncLock;
	fIdentFuncTable[2361] = FuncLog;
	fIdentFuncTable[807] = FuncLog10;
	fIdentFuncTable[2406] = FuncLov;
	fIdentFuncTable[2043] = FuncLov_auto_select;
	fIdentFuncTable[1806] = FuncLov_col;
	fIdentFuncTable[1921] = FuncLov_data;
	fIdentFuncTable[467] = FuncLov_first;
	fIdentFuncTable[1673] = FuncLov_height;
	fIdentFuncTable[1499] = FuncLov_noheading;
	fIdentFuncTable[70] = FuncLov_nosearch;
	fIdentFuncTable[2134] = FuncLov_reduced_to;
	fIdentFuncTable[2208] = FuncLov_row;
	fIdentFuncTable[1788] = FuncLov_secondary;
	fIdentFuncTable[2381] = FuncLov_selection;
	fIdentFuncTable[1107] = FuncLov_sorted_by;
	fIdentFuncTable[1268] = FuncLov_width;
	fIdentFuncTable[1779] = FuncLov_with;
	fIdentFuncTable[538] = FuncLowercase;
	fIdentFuncTable[631] = FuncLtrim;
	fIdentFuncTable[2233] = FuncMail;
	fIdentFuncTable[2296] = FuncMenu;
	fIdentFuncTable[743] = FuncMenu_block;
	fIdentFuncTable[255] = FuncMenu_form;
	fIdentFuncTable[1824] = FuncMessage;
	fIdentFuncTable[858] = FuncMid;
	fIdentFuncTable[588] = FuncMod;
	fIdentFuncTable[729] = FuncModify_form;
	fIdentFuncTable[1770] = FuncNew;
	fIdentFuncTable[1176] = FuncNo_domain;
	fIdentFuncTable[208] = FuncNobell;
	fIdentFuncTable[1756] = FuncNoclear_buffer;
	fIdentFuncTable[1858] = FuncNodeadlock_exit;
	fIdentFuncTable[135] = FuncNoerase;
	fIdentFuncTable[2073] = FuncNoerror;
	fIdentFuncTable[1092] = FuncNoexit_forward;
	fIdentFuncTable[1811] = FuncNoheading;
	fIdentFuncTable[656] = FuncNolov_data;
	fIdentFuncTable[1959] = FuncNorepeat;
	fIdentFuncTable[1319] = FuncNostatus;
	fIdentFuncTable[907] = FuncNototals;
	fIdentFuncTable[2427] = FuncNounderlines;
	fIdentFuncTable[632] = FuncNowait;
	fIdentFuncTable[1560] = FuncOpen;
	fIdentFuncTable[2226] = FuncOpen_text;
	fIdentFuncTable[1941] = FuncOpt;
	fIdentFuncTable[290] = FuncOptions;
	fIdentFuncTable[491] = FuncOutput;
	fIdentFuncTable[1952] = FuncOutput_block;
	fIdentFuncTable[2108] = FuncOutput_mask;
	fIdentFuncTable[1539] = FuncPause;
	fIdentFuncTable[1182] = FuncPause_block;
	fIdentFuncTable[214] = FuncPerform;
	fIdentFuncTable[1294] = FuncPoly_to_binary;
	fIdentFuncTable[219] = FuncPos;
	fIdentFuncTable[1569] = FuncPrint;
	fIdentFuncTable[1719] = FuncProcedure_form;
	fIdentFuncTable[1105] = FuncPrompt;
	fIdentFuncTable[488] = FuncProtect;
	fIdentFuncTable[66] = FuncQuery;
	fIdentFuncTable[2344] = FuncQuery_form;
	fIdentFuncTable[575] = FuncRandom;
	fIdentFuncTable[1396] = FuncRead_line;
	fIdentFuncTable[885] = FuncRead_only;
	fIdentFuncTable[1353] = FuncReceive;
	fIdentFuncTable[1571] = FuncReceive_arguments;
	fIdentFuncTable[2137] = FuncReceive_data;
	fIdentFuncTable[264] = FuncReceive_table;
	fIdentFuncTable[410] = FuncReduced_to;
	fIdentFuncTable[1269] = FuncRelease;
	fIdentFuncTable[303] = FuncRemain;
	fIdentFuncTable[1784] = FuncRepeat;
	fIdentFuncTable[452] = FuncReport;
	fIdentFuncTable[2315] = FuncReport_form;
	fIdentFuncTable[2025] = FuncReposition;
	fIdentFuncTable[1259] = FuncRewind_text;
	fIdentFuncTable[1938] = FuncRfooting;
	fIdentFuncTable[2331] = FuncRheading;
	fIdentFuncTable[1932] = FuncRight;
	fIdentFuncTable[1849] = FuncRollback;
	fIdentFuncTable[553] = FuncRound;
	fIdentFuncTable[1581] = FuncRow;
	fIdentFuncTable[2407] = FuncRow_height;
	fIdentFuncTable[1525] = FuncSearch;
	fIdentFuncTable[151] = FuncSecondary;
	fIdentFuncTable[1475] = FuncSeconds;
	fIdentFuncTable[744] = FuncSelection;
	fIdentFuncTable[1490] = FuncSend;
	fIdentFuncTable[845] = FuncSend_data;
	fIdentFuncTable[85] = FuncSend_message;
	fIdentFuncTable[720] = FuncSend_table;
	fIdentFuncTable[2275] = FuncSequence;
	fIdentFuncTable[2038] = FuncSeverity;
	fIdentFuncTable[60] = FuncSin;
	fIdentFuncTable[1763] = FuncSinh;
	fIdentFuncTable[1909] = FuncSorted_by;
	fIdentFuncTable[1775] = FuncSource;
	fIdentFuncTable[1474] = FuncSource_if;
	fIdentFuncTable[2141] = FuncSqrt;
	fIdentFuncTable[79] = FuncStart_stream;
	fIdentFuncTable[604] = FuncStart_transaction;
	fIdentFuncTable[639] = FuncStatistic;
	fIdentFuncTable[654] = FuncStatus;
	fIdentFuncTable[1816] = FuncStream_name;
	fIdentFuncTable[1368] = FuncString;
	fIdentFuncTable[1064] = FuncSuccess;
	fIdentFuncTable[39] = FuncSwitch;
	fIdentFuncTable[803] = FuncSwitch_base;
	fIdentFuncTable[1212] = FuncSystem;
	fIdentFuncTable[2335] = FuncTable;
	fIdentFuncTable[934] = FuncTable_form;
	fIdentFuncTable[1759] = FuncTable_search;
	fIdentFuncTable[1074] = FuncTag;
	fIdentFuncTable[705] = FuncTag_length;
	fIdentFuncTable[1095] = FuncTan;
	fIdentFuncTable[382] = FuncTanh;
	fIdentFuncTable[975] = FuncTarget;
	fIdentFuncTable[229] = FuncText;
	fIdentFuncTable[2007] = FuncText_only;
	fIdentFuncTable[307] = FuncTitle;
	fIdentFuncTable[2430] = FuncTo;
	fIdentFuncTable[795] = FuncTop_line;
	fIdentFuncTable[68] = FuncTotal;
	fIdentFuncTable[2000] = FuncTransfer;
	fIdentFuncTable[333] = FuncTrigger;
	fIdentFuncTable[2341] = FuncTrim;
	fIdentFuncTable[2301] = FuncTsuppress;
	fIdentFuncTable[2029] = FuncUnload;
	fIdentFuncTable[844] = FuncUppercase;
	fIdentFuncTable[1437] = FuncUse_if;
	fIdentFuncTable[1736] = FuncUser_key;
	fIdentFuncTable[353] = FuncUsing;
	fIdentFuncTable[2305] = FuncUtilities;
	fIdentFuncTable[1485] = FuncWait;
	fIdentFuncTable[1159] = FuncWhile;
	fIdentFuncTable[1452] = FuncWidth;
	fIdentFuncTable[1476] = FuncWith;
	fIdentFuncTable[27] = FuncWrite;
	fIdentFuncTable[92] = FuncWrite_line;
	fIdentFuncTable[2350] = FuncYesno_block;
}

bool __fastcall TSynDmlSyn::IsQuali()
{
	bool result = false;
	result = false;
	if(Run > 0)
	{
		if(fLine[Run - 1] == L'/')
			result = true;
	}
	return result;
}

bool __fastcall TSynDmlSyn::IsSpecial()
{
	bool result = false;
	result = false;
	if(Run > 0)
	{
		if(fLine[Run - 1] == L'%')
			result = true;
	}
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAbs(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAbsolute_position(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAccount(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsSpecial())
		result = tkSpecial;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAcos(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncActual_break(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsSpecial())
		result = tkSpecial;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAdd(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsSpecial())
			result = tkSpecial;
		else
		{
			result = tkKey;
			FRange = rsAdd;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAdd_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAlternate_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAscii(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAsin(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAtan(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAtan2(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncAttributes(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBack(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBase(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBatch(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBegin_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBegin_case(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBegin_disable_trigger(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBegin_row(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBegin_signal_to_status(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBell(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBinary_to_poly(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBottom_line(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsSpecial())
		result = tkSpecial;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBreak(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncBreak0(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCall(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCase(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCeil(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCheck(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCheck_domain(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncChr(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncClear_buffer(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCli(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncClose(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncClose_text(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCol(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
		{
			if(IsSpecial())
				result = tkSpecial;
			else
				result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncColumn_heading_row(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncColumn_headings(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncColumn_spacing(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCommit(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCommit_rate(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCompile(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCompress(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCompress_all(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncConfirm(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncConnect(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncContinue(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCos(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCosh(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncCross_reference(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDate(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDate_seconds(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDay_of_week(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDays(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDcl(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDefault_tag(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDelete(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDelete_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDescription(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDir(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDisconnect(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDisplay(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDisplay_length(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDocumentation(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncDomain(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEdit(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncElse(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncElse_if(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_case(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_disable_trigger(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_execute(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkForm;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_if(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
	{
		if(IsCurrentToken(Keywords[Index]))
			result = tkKey;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_row(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_signal_to_status(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncEnd_while(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncErase(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncError(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
			result = tkKey;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncExecute(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncExit(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
	{
		if(IsCurrentToken(Keywords[Index]))
			result = tkKey;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncExit_forward(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncExpand(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncExternal(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFacility(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFailure(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
		{
			if(IsSpecial())
				result = tkSpecial;
			else
				result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFetch(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFiles(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFind(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		result = tkKey;
		FRange = rsFind;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFind_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFinish(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFirst(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFloor(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFooting(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncFooting_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncForm(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsSpecial())
			result = tkSpecial;
		else
			result = tkForm;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncGenerate(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncGoto(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncGrouped_by(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncHeading(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncHeading_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncHeight(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncIdentifier(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncIf(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncIn(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && (FRange == rsFind))
	{
		result = tkKey;
		FRange = rsUnKnown;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncInput_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncInput_mask(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncInput_row_height(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncInt(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncInvoke(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncItem(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncItem_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncItem_if(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncJoined_to(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLeft(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLen(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
			result = tkFunction;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLfooting(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLheading(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLine(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLines_after(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
	{
		if(IsCurrentToken(Keywords[Index]) && IsSpecial())
			result = tkSpecial;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLines_before(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncList(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLoad(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLock(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLog(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
			result = tkFunction;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLog10(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_auto_select(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_col(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_data(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_first(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_height(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_noheading(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_nosearch(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_reduced_to(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_row(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_secondary(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_selection(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_sorted_by(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_width(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLov_with(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLowercase(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncLtrim(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMail(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMenu(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMenu_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMenu_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkForm;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMessage(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMid(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncMod(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncModify_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNew(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNo_domain(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNobell(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNoclear_buffer(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNodeadlock_exit(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNoerase(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNoerror(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNoexit_forward(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNoheading(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNolov_data(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNorepeat(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNostatus(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNototals(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsSpecial())
		result = tkSpecial;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNounderlines(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
		{
			if(IsSpecial())
				result = tkSpecial;
			else
				result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncNowait(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOpen(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOpen_text(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOpt(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOptions(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOutput(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOutput_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncOutput_mask(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPause(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPause_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPerform(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPoly_to_binary(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPos(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPrint(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncProcedure_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkForm;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncPrompt(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncProtect(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncQuery(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncQuery_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkForm;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRandom(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRead_line(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRead_only(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReceive(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReceive_arguments(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReceive_data(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReceive_table(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReduced_to(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRelease(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRemain(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRepeat(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
			result = tkKey;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReport(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReport_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkForm;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncReposition(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRewind_text(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRfooting(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRheading(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRight(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRollback(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRound(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRow(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
	{
		if(IsCurrentToken(Keywords[Index]) && IsSpecial())
			result = tkSpecial;
		else
			result = tkIdentifier;
	}
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncRow_height(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSearch(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSecondary(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSeconds(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSelection(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSend(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSend_data(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSend_message(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSend_table(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSequence(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSeverity(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSin(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSinh(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSorted_by(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSource(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSource_if(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSqrt(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncStart_stream(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncStart_transaction(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncStatistic(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncStatus(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
		{
			if(IsSpecial())
				result = tkSpecial;
			else
				result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncStream_name(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncString(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSuccess(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
		{
			if(IsSpecial())
				result = tkSpecial;
			else
				result = tkIdentifier;
		}
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSwitch(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSwitch_base(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncSystem(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTable(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTable_form(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkForm;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTable_search(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTag(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTag_length(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTan(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTanh(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTarget(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncText(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsSpecial())
			result = tkSpecial;
		else
			result = tkKey;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncText_only(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTitle(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
	{
		if(IsQuali())
			result = tkQualifier;
		else
			result = tkKey;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTo(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && (FRange == rsAdd))
	{
		result = tkKey;
		FRange = rsUnKnown;
	}
	else
	result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTop_line(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsSpecial())
		result = tkSpecial;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTotal(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTransfer(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTrigger(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTrim(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncTsuppress(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsSpecial())
		result = tkSpecial;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncUnload(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncUppercase(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkFunction;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncUse_if(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncUser_key(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncUsing(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncUtilities(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncWait(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncWhile(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncWidth(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncWith(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]) && IsQuali())
		result = tkQualifier;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncWrite(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncWrite_line(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkKey;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::FuncYesno_block(int Index)
{
	TtkTokenKind result = tkBlock;
	if(IsCurrentToken(Keywords[Index]))
		result = tkBlock;
	else
		result = tkIdentifier;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::AltFunc(int Index)
{
	TtkTokenKind result = tkBlock;
	result = tkIdentifier;
	return result;
}

__fastcall TSynDmlSyn::TSynDmlSyn(TComponent* AOwner)
 : inherited(AOwner),
			FRange(rsUnKnown),
			FTokenID(tkBlock),
			fFormAttri(nullptr),
			fBlockAttri(nullptr),
			fKeyAttri(nullptr),
			fQualiAttri(nullptr),
			fCommentAttri(nullptr),
			fFunctionAttri(nullptr),
			fVariableAttri(nullptr),
			fSpecialAttri(nullptr),
			fStringAttri(nullptr),
			fNumberAttri(nullptr),
			fSymbolAttri(nullptr),
			fIdentifierAttri(nullptr),
			fSpaceAttri(nullptr)
{
	FCaseSensitive = false;
	fFormAttri = new TSynHighlighterAttributes(SYNS_AttrForm, SYNS_FriendlyAttrForm);
	fFormAttri->Style = Synhighlighterdml__0;
	fFormAttri->Foreground = clBlue;
	addAttribute(fFormAttri);
	fBlockAttri = new TSynHighlighterAttributes(SYNS_AttrBlock, SYNS_FriendlyAttrBlock);
	fBlockAttri->Style = Synhighlighterdml__1;
	fBlockAttri->Foreground = clGreen;
	addAttribute(fBlockAttri);
	fKeyAttri = new TSynHighlighterAttributes(SYNS_AttrKey, SYNS_FriendlyAttrKey);
	fKeyAttri->Style = Synhighlighterdml__2;
	addAttribute(fKeyAttri);
	fCommentAttri = new TSynHighlighterAttributes(SYNS_AttrComment, SYNS_FriendlyAttrComment);
	fCommentAttri->Style = Synhighlighterdml__3;
	fCommentAttri->Foreground = clRed;
	addAttribute(fCommentAttri);
	fQualiAttri = new TSynHighlighterAttributes(SYNS_AttrQualifier, SYNS_FriendlyAttrQualifier);
	fQualiAttri->Style = Synhighlighterdml__4;
	fQualiAttri->Foreground = clGreen;
	addAttribute(fQualiAttri);
	fFunctionAttri = new TSynHighlighterAttributes(SYNS_AttrFunction, SYNS_FriendlyAttrFunction);
	fFunctionAttri->Style = Synhighlighterdml__5;
	fFunctionAttri->Foreground = clBlack;
	addAttribute(fFunctionAttri);
	fVariableAttri = new TSynHighlighterAttributes(SYNS_AttrVariable, SYNS_FriendlyAttrVariable);
	fVariableAttri->Style = Synhighlighterdml__6;
	fVariableAttri->Foreground = clBlack;
	addAttribute(fVariableAttri);
	fSpecialAttri = new TSynHighlighterAttributes(SYNS_AttrSpecialVariable, SYNS_FriendlyAttrSpecialVariable);
	fSpecialAttri->Style = Synhighlighterdml__7;
	fSpecialAttri->Foreground = clBlack;
	addAttribute(fSpecialAttri);
	fIdentifierAttri = new TSynHighlighterAttributes(SYNS_AttrIdentifier, SYNS_FriendlyAttrIdentifier);
	addAttribute(fIdentifierAttri);
	fNumberAttri = new TSynHighlighterAttributes(SYNS_AttrNumber, SYNS_FriendlyAttrNumber);
	addAttribute(fNumberAttri);
	fSpaceAttri = new TSynHighlighterAttributes(SYNS_AttrSpace, SYNS_FriendlyAttrSpace);
	addAttribute(fSpaceAttri);
	fStringAttri = new TSynHighlighterAttributes(SYNS_AttrString, SYNS_FriendlyAttrString);
	addAttribute(fStringAttri);
	fSymbolAttri = new TSynHighlighterAttributes(SYNS_AttrSymbol, SYNS_FriendlyAttrSymbol);
	addAttribute(fSymbolAttri);
	SetAttributesOnChange(DefHighlightChange);
	InitIdent();
	fDefaultFilter = SYNS_FilterGembase;
}

void __fastcall TSynDmlSyn::AddressOpProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'@')
		++Run;
}

void __fastcall TSynDmlSyn::AsciiCharProc()
{

	auto IsAsciiChar = [&]() -> bool 
	{
		bool result = false;
		switch(fLine[Run])
		{
			case L'_':
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
			case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
			 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
			 case 85: case 86: case 87: case 88: case 89: case 90:
			case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
			 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
			 case 117: case 118: case 119: case 120: case 121: case 122:
			result = true;
			break;
			default:
			result = false;
			break;
		}
		return result;
	};
  // variables...
	FTokenID = tkVariable;
	do
	{
		++Run;
	}
	while(!!IsAsciiChar());
}

void __fastcall TSynDmlSyn::SymbolProc()
{
	++Run;
	FTokenID = tkSymbol;
}

void __fastcall TSynDmlSyn::CRProc()
{
	FTokenID = tkSpace;
	++Run;
	if(fLine[Run] == L'\x0a')
		++Run;
}

void __fastcall TSynDmlSyn::GreaterProc()
{
	FTokenID = tkSymbol;
	++Run;
	if(fLine[Run] == L'=')
		++Run;
}

void __fastcall TSynDmlSyn::IdentProc()
{
	FTokenID = IdentKind((fLine + Run));
	Run += fStringLen;
	while(IsIdentChar(fLine[Run]))
		++Run;
}

void __fastcall TSynDmlSyn::LFProc()
{
	FTokenID = tkSpace;
	++Run;
}

void __fastcall TSynDmlSyn::LowerProc()
{
	FTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'=') || (fLine[Run] == L'>'))
		++Run;
}

void __fastcall TSynDmlSyn::NullProc()
{
	FTokenID = tkNull;
	++Run;
}

void __fastcall TSynDmlSyn::NumberProc()
{
	++Run;
	FTokenID = tkNumber;
	while(CharInSet(fLine[Run], Synhighlighterdml__8))
	{
		switch(fLine[Run])
		{
			case L'.':
			if(fLine[Run + 1] == L'.')
				goto label0;
			break;
			default:
			  ;
			break;
		}
		++Run;
	}
	label0:;
}

void __fastcall TSynDmlSyn::PointProc()
{
	FTokenID = tkSymbol;
	++Run;
	if((fLine[Run] == L'.') || (fLine[Run] == L')'))
		++Run;
}

void __fastcall TSynDmlSyn::RemProc()
{
	PWideChar P = nullptr;
	P = &fLine[Run - 1];
	while(P >= fLine)
	{
		if(!CharInSet((*P), Synhighlighterdml__9))
		{
			++Run;
			FTokenID = tkSymbol;
			return;
		}
		--P;
	}
  // it is a comment...
	FTokenID = tkComment;
	do
	{
		++Run;
	}
	while(!IsLineEnd(Run));
}

void __fastcall TSynDmlSyn::SpaceProc()
{
	FTokenID = tkSpace;
	while((fLine[Run] <= L'\x20') && !IsLineEnd(Run))
		++Run;
}

void __fastcall TSynDmlSyn::StringProc()
{
	FTokenID = tkString;
	if((fLine[Run + 1] == L'\"') && (fLine[Run + 2] == L'\"'))
		Run += 2;
	do
	{
		++Run;
	}
	while(!((fLine[Run] == L'\"') || IsLineEnd(Run)));
	if(fLine[Run] != L'\x00')
		++Run;
}

void __fastcall TSynDmlSyn::UnknownProc()
{
	++Run;
	FTokenID = tkUnknown;
}

void __fastcall TSynDmlSyn::Next()
{
	fTokenPos = Run;
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
		case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
		case L'\x0b':
		case L'\x0c':
		case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22: case 23:
		 case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 32:
		SpaceProc();
		break;
		case L'#':
		AsciiCharProc();
		break;
		case L'\"':
		StringProc();
		break;
		case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57:
		NumberProc();
		break;
		case 65: case 66: case 67: case 68: case 69: case 70: case 71: case 72: case 73: case 74:
		 case 75: case 76: case 77: case 78: case 79: case 80: case 81: case 82: case 83: case 84:
		 case 85: case 86: case 87: case 88: case 89: case 90:
		case 97: case 98: case 99: case 100: case 101: case 102: case 103: case 104: case 105: case 106:
		 case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116:
		 case 117: case 118: case 119: case 120: case 121: case 122:
		case L'_':
		IdentProc();
		break;
		case L'{':
		SymbolProc();
		break;
		case L'}':
		SymbolProc();
		break;
		case L'!':
		RemProc();
		break;
		case L'.':
		PointProc();
		break;
		case L'<':
		LowerProc();
		break;
		case L'>':
		GreaterProc();
		break;
		case L'@':
		AddressOpProc();
		break;
		case L'\x27':
		case L'&':
		case 40: case 41: case 42: case 43: case 44: case 45:
		case L'/':
		case L':':
		case L';':
		case L'=':
		case L'?':
		case 91: case 92: case 93: case 94:
		case L'`':
		case L'~':
		SymbolProc();
		break;
		default:
		UnknownProc();
		break;
	}
	inherited::Next();
}

TSynHighlighterAttributes* __fastcall TSynDmlSyn::GetDefaultAttribute(int Index)
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

bool __fastcall TSynDmlSyn::GetEol()
{
	bool result = false;
	result = Run == fLineLen + 1;
	return result;
}

TtkTokenKind __fastcall TSynDmlSyn::GetTokenID()
{
	TtkTokenKind result = tkBlock;
	result = FTokenID;
	return result;
}

TSynHighlighterAttributes* __fastcall TSynDmlSyn::GetTokenAttribute()
{
	TSynHighlighterAttributes* result = nullptr;
	switch(GetTokenID())
	{
		case tkForm:
		result = fFormAttri;
		break;
		case tkBlock:
		result = fBlockAttri;
		break;
		case tkKey:
		result = fKeyAttri;
		break;
		case tkComment:
		result = fCommentAttri;
		break;
		case tkQualifier:
		result = fQualiAttri;
		break;
		case tkFunction:
		result = fFunctionAttri;
		break;
		case tkIdentifier:
		result = fIdentifierAttri;
		break;
		case tkNumber:
		result = fNumberAttri;
		break;
		case tkSpecial:
		result = fSpecialAttri;
		break;
		case tkSpace:
		result = fSpaceAttri;
		break;
		case tkString:
		result = fStringAttri;
		break;
		case tkVariable:
		result = fVariableAttri;
		break;
		case tkSymbol:
		result = fSymbolAttri;
		break;
		case tkUnknown:
		result = fSymbolAttri;
		break;
		default:
		result = nullptr;
		break;
	}
	return result;
}

int __fastcall TSynDmlSyn::GetTokenKind()
{
	int result = 0;
	result = int(GetTokenID());
	return result;
}

void* __fastcall TSynDmlSyn::GetRange()
{
	void* result = nullptr;
	result = ((void*) FRange);
	return result;
}

void __fastcall TSynDmlSyn::SetRange(void* Value)
{
	FRange = (TRangeState)(NativeInt)Value;
}

void __fastcall TSynDmlSyn::ResetRange()
{
	FRange = rsUnKnown;
}

bool __fastcall TSynDmlSyn::IsFilterStored()
{
	bool result = false;
	result = fDefaultFilter != SYNS_FilterGembase;
	return result;
}

/*#static*/
String __fastcall TSynDmlSyn::GetLanguageName()
{
	String result;
	result = SYNS_LangGembase;
	return result;
}

/*#static*/
String __fastcall TSynDmlSyn::GetFriendlyLanguageName()
{
	String result;
	result = SYNS_FriendlyLangGembase;
	return result;
}
static bool SynHighlighterDml_Initialized = false;

void SynHighlighterDml_initialization()
{
	if(SynHighlighterDml_Initialized)
		return;
	
	SynHighlighterDml_Initialized = true;
	
	RegisterPlaceableHighlighter(__classid(TSynDmlSyn));
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynHighlighterDml

