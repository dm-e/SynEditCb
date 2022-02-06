#ifndef SynEditOptionsDialogH
#define SynEditOptionsDialogH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Winapi.CommCtrl.hpp>
#include <System.Win.Registry.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include "SynEdit.h"
#include "SynEditHighlighter.h"
#include "SynEditMiscClasses.h"
#include "SynEditKeyCmds.h"
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.ImageList.hpp>




/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

 
/****************************************************************************************************/
/*                                                                                                  */
/*  The contents of this file are subject to the Mozilla Public License Version 1.1 (the "License");*/
/*  you may not use this file except in compliance with the License. You may obtain a copy of the   */
/*  License at http://www.mozilla.org/MPL/                                                          */
/*                                                                                                  */
/*  Software distributed under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF  */
/*  ANY KIND, either express or implied. See the License for the specific language governing rights */
/*  and limitations under the License.                                                              */
/*                                                                                                  */
/*  The Original Code is: jedi.inc.                                                                 */
/*  The Initial Developer of the Original Code is Project JEDI http://www.delphi-jedi.org           */
/*                                                                                                  */
/*  Alternatively, the contents of this file may be used under the terms of the GNU Lesser General  */
/*  Public License (the  "LGPL License"), in which case the provisions of the LGPL License are      */
/*  applicable instead of those above. If you wish to allow use of your version of this file only   */
/*  under the terms of the LGPL License and not to allow others to use your version of this file    */
/*  under the MPL, indicate your decision by deleting the provisions above and replace them with    */
/*  the notice and other provisions required by the LGPL License. If you do not delete the          */
/*  provisions above, a recipient may use your version of this file under either the MPL or the     */
/*  LGPL License.                                                                                   */
/*                                                                                                  */
/*  For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html                    */
/*                                                                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*  This file defines various generic compiler directives used in different libraries, e.g. in the  */
/*  JEDI Code Library (JCL) and JEDI Visual Component Library Library (JVCL). The directives in     */
/*  this file are of generic nature and consist mostly of mappings from the VERXXX directives       */
/*  defined by Delphi, C++Builder and FPC to friendly names such as DELPHI5 and                     */
/*  SUPPORTS_WIDESTRING. These friendly names are subsequently used in the libraries to test for    */
/*  compiler versions and/or whether the compiler supports certain features (such as widestrings or */
/*  64 bit integers. The libraries provide an additional, library specific, include file. For the   */
/*  JCL e.g. this is jcl.inc. These files should be included in source files instead of this file   */
/*  (which is pulled in automatically).                                                             */
/*                                                                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/* Last modified: $Date::                                                                         $ */
/* Revision:      $Rev::                                                                          $ */
/* Author:        $Author::                                                                       $ */
/*                                                                                                  */
/****************************************************************************************************/
/*
- Development environment directives
  This file defines two directives to indicate which development environment the
  library is being compiled with. Currently this can either be Delphi, Kylix,
  C++Builder or FPC.
  Directive           Description
  ------------------------------------------------------------------------------
  DELPHI              Defined if compiled with Delphi
  KYLIX               Defined if compiled with Kylix
  DELPHICOMPILER      Defined if compiled with Delphi or Kylix/Delphi
  BCB                 Defined if compiled with C++Builder
  CPPBUILDER          Defined if compiled with C++Builder (alias for BCB)
  BCBCOMPILER         Defined if compiled with C++Builder or Kylix/C++
  DELPHILANGUAGE      Defined if compiled with Delphi, Kylix or C++Builder
  BORLAND             Defined if compiled with Delphi, Kylix or C++Builder
  FPC                 Defined if compiled with FPC
- Platform Directives
  Platform directives are not all explicitly defined in this file, some are
  defined by the compiler itself. They are listed here only for completeness.
  Directive           Description
  ------------------------------------------------------------------------------
  WIN32               Defined when target platform is 32 bit Windows
  WIN64               Defined when target platform is 64 bit Windows
  MSWINDOWS           Defined when target platform is 32 bit Windows
  LINUX               Defined when target platform is Linux
  UNIX                Defined when target platform is Unix-like (including Linux)
  CLR                 Defined when target platform is .NET
- Architecture directives. These are auto-defined by FPC
  CPU32 and CPU64 are mostly for generic pointer size dependant differences rather
  than for a specific architecture.
  CPU386              Defined when target platform is native x86 (win32)
  CPUx86_64           Defined when target platform is native x86_64 (win64)
  CPU32               Defined when target is 32-bit
  CPU64	              Defined when target is 64-bit
  CPUASM              Defined when target assembler is available
- Visual library Directives
  The following directives indicate for a visual library. In a Delphi/BCB
  (Win32) application you need to define the VisualCLX symbol in the project
  options, if  you want to use the VisualCLX library. Alternatively you can use
  the IDE expert, which is distributed with the JCL to do this automatically.
  Directive           Description
  ------------------------------------------------------------------------------
  VCL                 Defined for Delphi/BCB (Win32) exactly if VisualCLX is not defined
  VisualCLX           Defined for Kylix; needs to be defined for Delphi/BCB to
                      use JCL with VisualCLX applications.

- Other cross-platform related defines
  These symbols are intended to help in writing portable code.
  Directive           Description
  ------------------------------------------------------------------------------
  PUREPASCAL          Code is machine-independent (as opposed to assembler code)
  Win32API            Code is specific for the Win32 API;
                      use instead of "{$IFNDEF CLR} {$IFDEF MSWINDOWS}" constructs

- Delphi Versions
  The following directives are direct mappings from the VERXXX directives to a
  friendly name of the associated compiler. These directives are only defined if
  the compiler is Delphi (ie DELPHI is defined).
  Directive           Description
  ------------------------------------------------------------------------------
  DELPHI1             Defined when compiling with Delphi 1 (Codename WASABI/MANGO)
  DELPHI2             Defined when compiling with Delphi 2 (Codename POLARIS)
  DELPHI3             Defined when compiling with Delphi 3 (Codename IVORY)
  DELPHI4             Defined when compiling with Delphi 4 (Codename ALLEGRO)
  DELPHI5             Defined when compiling with Delphi 5 (Codename ARGUS)
  DELPHI6             Defined when compiling with Delphi 6 (Codename ILLIAD)
  DELPHI7             Defined when compiling with Delphi 7 (Codename AURORA)
  DELPHI8             Defined when compiling with Delphi 8 (Codename OCTANE)
  DELPHI2005          Defined when compiling with Delphi 2005 (Codename DIAMONDBACK)
  DELPHI9             Alias for DELPHI2005
  DELPHI10            Defined when compiling with Delphi 2006 (Codename DEXTER)
  DELPHI2006          Alias for DELPHI10
  DELPHI11            Defined when compiling with Delphi 2007 for Win32 (Codename SPACELY)
  DELPHI2007          Alias for DELPHI11
  DELPHI12            Defined when compiling with Delphi 2009 for Win32 (Codename TIBURON)
  DELPHI2009          Alias for DELPHI12
  DELPHI14            Defined when compiling with Delphi 2010 for Win32 (Codename WEAVER)
  DELPHI2010          Alias for DELPHI14
  DELPHI15            Defined when compiling with Delphi XE for Win32 (Codename FULCRUM)
  DELPHIXE            Alias for DELPHI15
  DELPHI16            Defined when compiling with Delphi XE2 for Win32 (Codename PULSAR)
  DELPHIXE2           Alias for DELPHI16
  DELPHI17            Defined when compiling with Delphi XE3 for Win32 (Codename WATERDRAGON)
  DELPHIXE3           Alias for DELPHI17
  DELPHI18            Defined when compiling with Delphi XE4 for Win32 (Codename QUINTESSENCE)
  DELPHIXE4           Alias for DELPHI18
  DELPHI19            Defined when compiling with Delphi XE5 for Win32 (Codename ZEPHYR)
  DELPHIXE5           Alias for DELPHI19
  DELPHI20            Defined when compiling with Delphi XE6 for Win32 (Codename PROTEUS)
  DELPHIXE6           Alias for DELPHI20
  DELPHI21            Defined when compiling with Delphi XE7 for Win32 (Codename CARPATHIA)
  DELPHIXE7           Alias for DELPHI21
  DELPHI22            Defined when compiling with Delphi XE8 for Win32 (Codename ELBRUS)
  DELPHIXE8           Alias for DELPHI22
  DELPHI23            Defined when compiling with Delphi 10 for Win32 (Codename AITANA)
  DELPHIX_SEATTLE     Alias for DELPHI23
  DELPHI24            Defined when compiling with Delphi 10.1 for Win32 (Codename BIGBEN)
  DELPHIX_BERLIN      Alias for DELPHI24
  DELPHI25            Defined when compiling with Delphi 10.2 for Win32 (Codename GODZILLA)
  DELPHIX_TOKYO       Alias for DELPHI25
  DELPHI26            Defined when compiling with Delphi 10.3 for Win32 (Codename CARNIVAL)
  DELPHIX_RIO         Alias for DELPHI26
  DELPHI1_UP          Defined when compiling with Delphi 1 or higher
  DELPHI2_UP          Defined when compiling with Delphi 2 or higher
  DELPHI3_UP          Defined when compiling with Delphi 3 or higher
  DELPHI4_UP          Defined when compiling with Delphi 4 or higher
  DELPHI5_UP          Defined when compiling with Delphi 5 or higher
  DELPHI6_UP          Defined when compiling with Delphi 6 or higher
  DELPHI7_UP          Defined when compiling with Delphi 7 or higher
  DELPHI8_UP          Defined when compiling with Delphi 8 or higher
  DELPHI2005_UP       Defined when compiling with Delphi 2005 or higher
  DELPHI9_UP          Alias for DELPHI2005_UP
  DELPHI10_UP         Defined when compiling with Delphi 2006 or higher
  DELPHI2006_UP       Alias for DELPHI10_UP
  DELPHI11_UP         Defined when compiling with Delphi 2007 for Win32 or higher
  DELPHI2007_UP       Alias for DELPHI11_UP
  DELPHI12_UP         Defined when compiling with Delphi 2009 for Win32 or higher
  DELPHI2009_UP       Alias for DELPHI12_UP
  DELPHI14_UP         Defined when compiling with Delphi 2010 for Win32 or higher
  DELPHI2010_UP       Alias for DELPHI14_UP
  DELPHI15_UP         Defined when compiling with Delphi XE for Win32 or higher
  DELPHIXE_UP         Alias for DELPHI15_UP
  DELPHI16_UP         Defined when compiling with Delphi XE2 for Win32 or higher
  DELPHIXE2_UP        Alias for DELPHI16_UP
  DELPHI17_UP         Defined when compiling with Delphi XE3 for Win32 or higher
  DELPHIXE3_UP        Alias for DELPHI17_UP
  DELPHI18_UP         Defined when compiling with Delphi XE4 for Win32 or higher
  DELPHIXE4_UP        Alias for DELPHI18_UP
  DELPHI19_UP         Defined when compiling with Delphi XE5 for Win32 or higher
  DELPHIXE5_UP        Alias for DELPHI19_UP
  DELPHI20_UP         Defined when compiling with Delphi XE6 for Win32 or higher
  DELPHIXE6_UP        Alias for DELPHI20_UP
  DELPHI21_UP         Defined when compiling with Delphi XE7 for Win32 or higher
  DELPHIXE7_UP        Alias for DELPHI21_UP
  DELPHI22_UP         Defined when compiling with Delphi XE8 for Win32 or higher
  DELPHIXE8_UP        Alias for DELPHI22_UP
  DELPHI23_UP         Defined when compiling with Delphi 10 for Win32 or higher
  DELPHIX_SEATTLE_UP  Alias for DELPHI23_UP
  DELPHI24_UP         Defined when compiling with Delphi 10.1 for Win32 or higher
  DELPHIX_BERLIN_UP   Alias for DELPHI24_UP
  DELPHI25_UP         Defined when compiling with Delphi 10.2 for Win32 or higher
  DELPHIX_TOKYO_UP    Alias for DELPHI25_UP
  DELPHI26_UP         Defined when compiling with Delphi 10.3 for Win32 or higher
  DELPHIX_RIO_UP      Alias for DELPHI26_UP
  DELPHI27_UP         Defined when compiling with Delphi 10.4 for Win32 or higher

- Kylix Versions
  The following directives are direct mappings from the VERXXX directives to a
  friendly name of the associated compiler. These directives are only defined if
  the compiler is Kylix (ie KYLIX is defined).
  Directive           Description
  ------------------------------------------------------------------------------
  KYLIX1              Defined when compiling with Kylix 1
  KYLIX2              Defined when compiling with Kylix 2
  KYLIX3              Defined when compiling with Kylix 3 (Codename CORTEZ)
  KYLIX1_UP           Defined when compiling with Kylix 1 or higher
  KYLIX2_UP           Defined when compiling with Kylix 2 or higher
  KYLIX3_UP           Defined when compiling with Kylix 3 or higher

- Delphi Compiler Versions (Delphi / Kylix, not in BCB mode)
  Directive           Description
  ------------------------------------------------------------------------------
  DELPHICOMPILER1      Defined when compiling with Delphi 1
  DELPHICOMPILER2      Defined when compiling with Delphi 2
  DELPHICOMPILER3      Defined when compiling with Delphi 3
  DELPHICOMPILER4      Defined when compiling with Delphi 4
  DELPHICOMPILER5      Defined when compiling with Delphi 5
  DELPHICOMPILER6      Defined when compiling with Delphi 6 or Kylix 1, 2 or 3
  DELPHICOMPILER7      Defined when compiling with Delphi 7
  DELPHICOMPILER8      Defined when compiling with Delphi 8
  DELPHICOMPILER9      Defined when compiling with Delphi 2005
  DELPHICOMPILER10     Defined when compiling with Delphi Personality of BDS 4.0
  DELPHICOMPILER11     Defined when compiling with Delphi 2007 for Win32
  DELPHICOMPILER12     Defined when compiling with Delphi Personality of BDS 6.0
  DELPHICOMPILER14     Defined when compiling with Delphi Personality of BDS 7.0
  DELPHICOMPILER15     Defined when compiling with Delphi Personality of BDS 8.0
  DELPHICOMPILER16     Defined when compiling with Delphi Personality of BDS 9.0
  DELPHICOMPILER17     Defined when compiling with Delphi Personality of BDS 10.0
  DELPHICOMPILER18     Defined when compiling with Delphi Personality of BDS 11.0
  DELPHICOMPILER19     Defined when compiling with Delphi Personality of BDS 12.0
  DELPHICOMPILER20     Defined when compiling with Delphi Personality of BDS 14.0
  DELPHICOMPILER21     Defined when compiling with Delphi Personality of BDS 15.0
  DELPHICOMPILER22     Defined when compiling with Delphi Personality of BDS 16.0
  DELPHICOMPILER23     Defined when compiling with Delphi Personality of BDS 17.0
  DELPHICOMPILER24     Defined when compiling with Delphi Personality of BDS 18.0
  DELPHICOMPILER25     Defined when compiling with Delphi Personality of BDS 19.0
  DELPHICOMPILER26     Defined when compiling with Delphi Personality of BDS 20.0
  DELPHICOMPILER27     Defined when compiling with Delphi Personality of BDS 21.0
  DELPHICOMPILER1_UP   Defined when compiling with Delphi 1 or higher
  DELPHICOMPILER2_UP   Defined when compiling with Delphi 2 or higher
  DELPHICOMPILER3_UP   Defined when compiling with Delphi 3 or higher
  DELPHICOMPILER4_UP   Defined when compiling with Delphi 4 or higher
  DELPHICOMPILER5_UP   Defined when compiling with Delphi 5 or higher
  DELPHICOMPILER6_UP   Defined when compiling with Delphi 6 or Kylix 1, 2 or 3 or higher
  DELPHICOMPILER7_UP   Defined when compiling with Delphi 7 or higher
  DELPHICOMPILER8_UP   Defined when compiling with Delphi 8 or higher
  DELPHICOMPILER9_UP   Defined when compiling with Delphi 2005
  DELPHICOMPILER10_UP  Defined when compiling with Delphi 2006 or higher
  DELPHICOMPILER11_UP  Defined when compiling with Delphi 2007 for Win32 or higher
  DELPHICOMPILER12_UP  Defined when compiling with Delphi 2009 for Win32 or higher
  DELPHICOMPILER14_UP  Defined when compiling with Delphi 2010 for Win32 or higher
  DELPHICOMPILER15_UP  Defined when compiling with Delphi XE for Win32 or higher
  DELPHICOMPILER16_UP  Defined when compiling with Delphi XE2 for Win32 or higher
  DELPHICOMPILER17_UP  Defined when compiling with Delphi XE3 for Win32 or higher
  DELPHICOMPILER18_UP  Defined when compiling with Delphi XE4 for Win32 or higher
  DELPHICOMPILER19_UP  Defined when compiling with Delphi XE5 for Win32 or higher
  DELPHICOMPILER20_UP  Defined when compiling with Delphi XE6 for Win32 or higher
  DELPHICOMPILER21_UP  Defined when compiling with Delphi XE7 for Win32 or higher
  DELPHICOMPILER22_UP  Defined when compiling with Delphi XE8 for Win32 or higher
  DELPHICOMPILER23_UP  Defined when compiling with Delphi 10 for Win32 or higher
  DELPHICOMPILER24_UP  Defined when compiling with Delphi 10.1 for Win32 or higher
  DELPHICOMPILER25_UP  Defined when compiling with Delphi 10.2 for Win32 or higher
  DELPHICOMPILER26_UP  Defined when compiling with Delphi 10.3 for Win32 or higher
  DELPHICOMPILER27_UP  Defined when compiling with Delphi 10.4 for Win32 or higher

- C++Builder Versions
  The following directives are direct mappings from the VERXXX directives to a
  friendly name of the associated compiler. These directives are only defined if
  the compiler is C++Builder (ie BCB is defined).
  Directive    Description
  ------------------------------------------------------------------------------
  BCB1         Defined when compiling with C++Builder 1
  BCB3         Defined when compiling with C++Builder 3
  BCB4         Defined when compiling with C++Builder 4
  BCB5         Defined when compiling with C++Builder 5 (Codename RAMPAGE)
  BCB6         Defined when compiling with C++Builder 6 (Codename RIPTIDE)
  BCB10        Defined when compiling with C++Builder Personality of BDS 4.0 (also known as C++Builder 2006) (Codename DEXTER)
  BCB11        Defined when compiling with C++Builder Personality of RAD Studio 2007 (also known as C++Builder 2007) (Codename COGSWELL)
  BCB12        Defined when compiling with C++Builder Personality of RAD Studio 2009 (also known as C++Builder 2009) (Codename TIBURON)
  BCB14        Defined when compiling with C++Builder Personality of RAD Studio 2010 (also known as C++Builder 2010) (Codename WEAVER)
  BCB15        Defined when compiling with C++Builder Personality of RAD Studio XE (also known as C++Builder XE) (Codename FULCRUM)
  BCB16        Defined when compiling with C++Builder Personality of RAD Studio XE2 (also known as C++Builder XE2) (Codename PULSAR)
  BCB17        Defined when compiling with C++Builder Personality of RAD Studio XE3 (also known as C++Builder XE3) (Codename WATERDRAGON)
  BCB18        Defined when compiling with C++Builder Personality of RAD Studio XE4 (also known as C++Builder XE4) (Codename QUINTESSENCE)
  BCB19        Defined when compiling with C++Builder Personality of RAD Studio XE5 (also known as C++Builder XE5) (Codename ZEPHYR)
  BCB20        Defined when compiling with C++Builder Personality of RAD Studio XE6 (also known as C++Builder XE6) (Codename PROTEUS)
  BCB21        Defined when compiling with C++Builder Personality of RAD Studio XE7 (also known as C++Builder XE7) (Codename CARPATHIA)
  BCB22        Defined when compiling with C++Builder Personality of RAD Studio XE8 (also known as C++Builder XE8) (Codename ELBRUS)
  BCB23        Defined when compiling with C++Builder Personality of RAD Studio 10 Seattle (also known as C++Builder 10 Seattle) (Codename AITANA)
  BCB24        Defined when compiling with C++Builder Personality of RAD Studio 10.1 Berlin (also known as C++Builder 10.1 Berlin) (Codename BIGBEN)
  BCB25        Defined when compiling with C++Builder Personality of RAD Studio 10.2 Tokyo (also known as C++Builder 10.2 Tokyo) (Codename GODZILLA)
  BCB26        Defined when compiling with C++Builder Personality of RAD Studio 10.3 Rio (also known as C++Builder 10.3) (Codename CARNIVAL)
  BCB27        Defined when compiling with C++Builder Personality of RAD Studio 10.4 Rio (also known as C++Builder 10.4) (Codename DENALI)
  BCB1_UP      Defined when compiling with C++Builder 1 or higher
  BCB3_UP      Defined when compiling with C++Builder 3 or higher
  BCB4_UP      Defined when compiling with C++Builder 4 or higher
  BCB5_UP      Defined when compiling with C++Builder 5 or higher
  BCB6_UP      Defined when compiling with C++Builder 6 or higher
  BCB10_UP     Defined when compiling with C++Builder Personality of BDS 4.0 or higher
  BCB11_UP     Defined when compiling with C++Builder Personality of RAD Studio 2007 or higher
  BCB12_UP     Defined when compiling with C++Builder Personality of RAD Studio 2009 or higher
  BCB14_UP     Defined when compiling with C++Builder Personality of RAD Studio 2010 or higher
  BCB15_UP     Defined when compiling with C++Builder Personality of RAD Studio XE or higher
  BCB16_UP     Defined when compiling with C++Builder Personality of RAD Studio XE2 or higher
  BCB17_UP     Defined when compiling with C++Builder Personality of RAD Studio XE3 or higher
  BCB18_UP     Defined when compiling with C++Builder Personality of RAD Studio XE4 or higher
  BCB19_UP     Defined when compiling with C++Builder Personality of RAD Studio XE5 or higher
  BCB20_UP     Defined when compiling with C++Builder Personality of RAD Studio XE6 or higher
  BCB21_UP     Defined when compiling with C++Builder Personality of RAD Studio XE7 or higher
  BCB22_UP     Defined when compiling with C++Builder Personality of RAD Studio XE8 or higher
  BCB23_UP     Defined when compiling with C++Builder Personality of RAD Studio 10 or higher
  BCB24_UP     Defined when compiling with C++Builder Personality of RAD Studio 10.1 or higher
  BCB25_UP     Defined when compiling with C++Builder Personality of RAD Studio 10.2 or higher
  BCB26_UP     Defined when compiling with C++Builder Personality of RAD Studio 10.3 or higher
  BCB27_UP     Defined when compiling with C++Builder Personality of RAD Studio 10.4 or higher

- RAD Studio / Borland Developer Studio Versions
  The following directives are direct mappings from the VERXXX directives to a
  friendly name of the associated IDE. These directives are only defined if
  the IDE is Borland Developer Studio Version 2 or above.
  Note: Borland Developer Studio 2006 is marketed as Delphi 2006 or C++Builder 2006,
  but those provide only different labels for identical content.
  Directive    Description
  ------------------------------------------------------------------------------
  BDS          Defined when compiling with BDS version of dcc32.exe (Codename SIDEWINDER)
  BDS2         Defined when compiling with BDS 2.0 (Delphi 8) (Codename OCTANE)
  BDS3         Defined when compiling with BDS 3.0 (Delphi 2005) (Codename DIAMONDBACK)
  BDS4         Defined when compiling with BDS 4.0 (Borland Developer Studio 2006) (Codename DEXTER)
  BDS5         Defined when compiling with BDS 5.0 (CodeGear RAD Studio 2007) (Codename HIGHLANDER)
  BDS6         Defined when compiling with BDS 6.0 (CodeGear RAD Studio 2009) (Codename TIBURON)
  BDS7         Defined when compiling with BDS 7.0 (Embarcadero RAD Studio 2010) (Codename WEAVER)
  BDS8         Defined when compiling with BDS 8.0 (Embarcadero RAD Studio XE) (Codename FULCRUM)
  BDS9         Defined when compiling with BDS 9.0 (Embarcadero RAD Studio XE2) (Codename PULSAR)
  BDS10        Defined when compiling with BDS 10.0 (Embarcadero RAD Studio XE3) (Codename WATERDRAGON)
  BDS11        Defined when compiling with BDS 11.0 (Embarcadero RAD Studio XE4) (Codename QUINTESSENCE)
  BDS12        Defined when compiling with BDS 12.0 (Embarcadero RAD Studio XE5) (Codename ZEPHYR)
  BDS14        Defined when compiling with BDS 14.0 (Embarcadero RAD Studio XE6) (Codename PROTEUS)
  BDS15        Defined when compiling with BDS 15.0 (Embarcadero RAD Studio XE7) (Codename CARPATHIA)
  BDS16        Defined when compiling with BDS 16.0 (Embarcadero RAD Studio XE8) (Codename ELBRUS)
  BDS17        Defined when compiling with BDS 17.0 (Embarcadero RAD Studio 10) (Codename AITANA)
  BDS18        Defined when compiling with BDS 18.0 (Embarcadero RAD Studio 10.1) (Codename BIGBEN)
  BDS19        Defined when compiling with BDS 19.0 (Embarcadero RAD Studio 10.2) (Codename GODZILLA)
  BDS20        Defined when compiling with BDS 20.0 (Embarcadero RAD Studio 10.3) (Codename CARNIVAL)
  BDS21        Defined when compiling with BDS 21.0 (Embarcadero RAD Studio 10.4) (Codename DENALI)
  BDS2_UP      Defined when compiling with BDS 2.0 or higher
  BDS3_UP      Defined when compiling with BDS 3.0 or higher
  BDS4_UP      Defined when compiling with BDS 4.0 or higher
  BDS5_UP      Defined when compiling with BDS 5.0 or higher
  BDS6_UP      Defined when compiling with BDS 6.0 or higher
  BDS7_UP      Defined when compiling with BDS 7.0 or higher
  BDS8_UP      Defined when compiling with BDS 8.0 or higher
  BDS9_UP      Defined when compiling with BDS 9.0 or higher
  BDS10_UP     Defined when compiling with BDS 10.0 or higher
  BDS11_UP     Defined when compiling with BDS 11.0 or higher
  BDS12_UP     Defined when compiling with BDS 12.0 or higher
  BDS14_UP     Defined when compiling with BDS 14.0 or higher
  BDS15_UP     Defined when compiling with BDS 15.0 or higher
  BDS16_UP     Defined when compiling with BDS 16.0 or higher
  BDS17_UP     Defined when compiling with BDS 17.0 or higher
  BDS18_UP     Defined when compiling with BDS 18.0 or higher
  BDS19_UP     Defined when compiling with BDS 19.0 or higher
  BDS20_UP     Defined when compiling with BDS 20.0 or higher
  BDS21_UP     Defined when compiling with BDS 21.0 or higher
- Compiler Versions
  The following directives are direct mappings from the VERXXX directives to a
  friendly name of the associated compiler. Unlike the DELPHI_X and BCB_X
  directives, these directives are indepedent of the development environment.
  That is, they are defined regardless of whether compilation takes place using
  Delphi or C++Builder.
  Directive     Description
  ------------------------------------------------------------------------------
  COMPILER1      Defined when compiling with Delphi 1
  COMPILER2      Defined when compiling with Delphi 2 or C++Builder 1
  COMPILER3      Defined when compiling with Delphi 3
  COMPILER35     Defined when compiling with C++Builder 3
  COMPILER4      Defined when compiling with Delphi 4 or C++Builder 4
  COMPILER5      Defined when compiling with Delphi 5 or C++Builder 5
  COMPILER6      Defined when compiling with Delphi 6 or C++Builder 6
  COMPILER7      Defined when compiling with Delphi 7
  COMPILER8      Defined when compiling with Delphi 8
  COMPILER9      Defined when compiling with Delphi 9
  COMPILER10     Defined when compiling with Delphi or C++Builder Personalities of BDS 4.0
  COMPILER11     Defined when compiling with Delphi or C++Builder Personalities of BDS 5.0
  COMPILER12     Defined when compiling with Delphi or C++Builder Personalities of BDS 6.0
  COMPILER14     Defined when compiling with Delphi or C++Builder Personalities of BDS 7.0
  COMPILER15     Defined when compiling with Delphi or C++Builder Personalities of BDS 8.0
  COMPILER16     Defined when compiling with Delphi or C++Builder Personalities of BDS 9.0
  COMPILER17     Defined when compiling with Delphi or C++Builder Personalities of BDS 10.0
  COMPILER18     Defined when compiling with Delphi or C++Builder Personalities of BDS 11.0
  COMPILER19     Defined when compiling with Delphi or C++Builder Personalities of BDS 12.0
  COMPILER20     Defined when compiling with Delphi or C++Builder Personalities of BDS 14.0
  COMPILER21     Defined when compiling with Delphi or C++Builder Personalities of BDS 15.0
  COMPILER22     Defined when compiling with Delphi or C++Builder Personalities of BDS 16.0
  COMPILER23     Defined when compiling with Delphi or C++Builder Personalities of BDS 17.0
  COMPILER24     Defined when compiling with Delphi or C++Builder Personalities of BDS 18.0
  COMPILER25     Defined when compiling with Delphi or C++Builder Personalities of BDS 19.0
  COMPILER26     Defined when compiling with Delphi or C++Builder Personalities of BDS 20.0
  COMPILER27     Defined when compiling with Delphi or C++Builder Personalities of BDS 21.0
  COMPILER1_UP   Defined when compiling with Delphi 1 or higher
  COMPILER2_UP   Defined when compiling with Delphi 2 or C++Builder 1 or higher
  COMPILER3_UP   Defined when compiling with Delphi 3 or higher
  COMPILER35_UP  Defined when compiling with C++Builder 3 or higher
  COMPILER4_UP   Defined when compiling with Delphi 4 or C++Builder 4 or higher
  COMPILER5_UP   Defined when compiling with Delphi 5 or C++Builder 5 or higher
  COMPILER6_UP   Defined when compiling with Delphi 6 or C++Builder 6 or higher
  COMPILER7_UP   Defined when compiling with Delphi 7
  COMPILER8_UP   Defined when compiling with Delphi 8
  COMPILER9_UP   Defined when compiling with Delphi Personalities of BDS 3.0
  COMPILER10_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 4.0 or higher
  COMPILER11_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 5.0 or higher
  COMPILER12_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 6.0 or higher
  COMPILER14_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 7.0 or higher
  COMPILER15_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 8.0 or higher
  COMPILER16_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 9.0 or higher
  COMPILER17_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 10.0 or higher
  COMPILER18_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 11.0 or higher
  COMPILER19_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 12.0 or higher
  COMPILER20_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 14.0 or higher
  COMPILER21_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 15.0 or higher
  COMPILER22_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 16.0 or higher
  COMPILER23_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 17.0 or higher
  COMPILER24_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 18.0 or higher
  COMPILER25_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 19.0 or higher
  COMPILER26_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 20.0 or higher
  COMPILER27_UP  Defined when compiling with Delphi or C++Builder Personalities of BDS 21.0 or higher

- RTL Versions
  Use e.g. following to determine the exact RTL version since version 14.0:
    {$IFDEF CONDITIONALEXPRESSIONS}
      {$IF Declared(RTLVersion) and (RTLVersion >= 14.2)}
        // code for Delphi 6.02 or higher, Kylix 2 or higher, C++Builder 6 or higher
        ...
      {$IFEND}
    {$ENDIF}
  Directive     Description
  ------------------------------------------------------------------------------
  RTL80_UP      Defined when compiling with Delphi 1 or higher
  RTL90_UP      Defined when compiling with Delphi 2 or higher
  RTL93_UP      Defined when compiling with C++Builder 1 or higher
  RTL100_UP     Defined when compiling with Delphi 3 or higher
  RTL110_UP     Defined when compiling with C++Builder 3 or higher
  RTL120_UP     Defined when compiling with Delphi 4 or higher
  RTL125_UP     Defined when compiling with C++Builder 4 or higher
  RTL130_UP     Defined when compiling with Delphi 5 or C++Builder 5 or higher
  RTL140_UP     Defined when compiling with Delphi 6, Kylix 1, 2 or 3 or C++Builder 6 or higher
  RTL150_UP     Defined when compiling with Delphi 7 or higher
  RTL160_UP     Defined when compiling with Delphi 8 or higher
  RTL170_UP     Defined when compiling with Delphi Personalities of BDS 3.0 or higher
  RTL180_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 4.0 or higher
  RTL185_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 5.0 or higher
  RTL190_UP     Defined when compiling with Delphi.NET of BDS 5.0 or higher
  RTL200_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 6.0 or higher
  RTL210_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 7.0 or higher
  RTL220_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 8.0 or higher
  RTL230_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 9.0 or higher
  RTL240_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 10.0 or higher
  RTL250_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 11.0 or higher
  RTL260_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 12.0 or higher
  RTL270_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 14.0 or higher
  RTL280_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 15.0 or higher
  RTL290_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 16.0 or higher
  RTL300_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 17.0 or higher
  RTL310_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 18.0 or higher
  RTL320_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 19.0 or higher
  RTL330_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 20.0 or higher
  RTL340_UP     Defined when compiling with Delphi or C++Builder Personalities of BDS 21.0 or higher

- CLR Versions
  Directive     Description
  ------------------------------------------------------------------------------
  CLR            Defined when compiling for .NET
  CLR10          Defined when compiling for .NET 1.0 (may be overriden by FORCE_CLR10)
  CLR10_UP       Defined when compiling for .NET 1.0 or higher
  CLR11          Defined when compiling for .NET 1.1 (may be overriden by FORCE_CLR11)
  CLR11_UP       Defined when compiling for .NET 1.1 or higher
  CLR20          Defined when compiling for .NET 2.0 (may be overriden by FORCE_CLR20)
  CLR20_UP       Defined when compiling for .NET 2.0 or higher

- Feature Directives
  The features directives are used to test if the compiler supports specific
  features, such as method overloading, and adjust the sources accordingly. Use
  of these directives is preferred over the use of the DELPHI and COMPILER
  directives.
  Directive              Description
  ------------------------------------------------------------------------------
  SUPPORTS_CONSTPARAMS           Compiler supports const parameters (D1+)
  SUPPORTS_SINGLE                Compiler supports the Single type (D1+)
  SUPPORTS_DOUBLE                Compiler supports the Double type (D1+)
  SUPPORTS_EXTENDED              Compiler supports the Extended type (D1+)
  SUPPORTS_CURRENCY              Compiler supports the Currency type (D2+)
  SUPPORTS_THREADVAR             Compiler supports threadvar declarations (D2+)
  SUPPORTS_OUTPARAMS             Compiler supports out parameters (D3+)
  SUPPORTS_VARIANT               Compiler supports variant (D2+)
  SUPPORTS_WIDECHAR              Compiler supports the WideChar type (D2+)
  SUPPORTS_WIDESTRING            Compiler supports the WideString type (D3+/BCB3+)
  SUPPORTS_INTERFACE             Compiler supports interfaces (D3+/BCB3+)
  SUPPORTS_DISPINTERFACE         Compiler supports dispatch interfaces (D3+/BCB3+)
  SUPPORTS_DISPID                Compiler supports dispatch ids (D3+/BCB3+/FPC)
  SUPPORTS_EXTSYM                Compiler supports the $EXTERNALSYM directive (D4+/BCB3+)
  SUPPORTS_NODEFINE              Compiler supports the $NODEFINE directive (D4+/BCB3+)
  SUPPORTS_LONGWORD              Compiler supports the LongWord type (unsigned 32 bit) (D4+/BCB4+)
  SUPPORTS_INT64                 Compiler supports the Int64 type (D4+/BCB4+)
  SUPPORTS_UINT64                Compiler supports the UInt64 type (D7+)
  SUPPORTS_DYNAMICARRAYS         Compiler supports dynamic arrays (D4+/BCB4+)
  SUPPORTS_DEFAULTPARAMS         Compiler supports default parameters (D4+/BCB4+)
  SUPPORTS_OVERLOAD              Compiler supports overloading (D4+/BCB4+)
  SUPPORTS_IMPLEMENTS            Compiler supports implements (D4+/BCB4+)
  SUPPORTS_DEPRECATED            Compiler supports the deprecated directive (D6+/BCB6+)
  SUPPORTS_PLATFORM              Compiler supports the platform directive (D6+/BCB6+)
  SUPPORTS_LIBRARY               Compiler supports the library directive (D6+/BCB6+/FPC)
  SUPPORTS_LOCAL                 Compiler supports the local directive (D6+/BCB6+)
  SUPPORTS_SETPEFLAGS            Compiler supports the SetPEFlags directive (D6+/BCB6+)
  SUPPORTS_EXPERIMENTAL_WARNINGS Compiler supports the WARN SYMBOL_EXPERIMENTAL and WARN UNIT_EXPERIMENTAL directives (D6+/BCB6+)
  SUPPORTS_INLINE                Compiler supports the inline directive (D9+/FPC)
  SUPPORTS_FOR_IN                Compiler supports for in loops (D9+)
  SUPPORTS_NESTED_CONSTANTS      Compiler supports nested constants (D9+)
  SUPPORTS_NESTED_TYPES          Compiler supports nested types (D9+)
  SUPPORTS_REGION                Compiler supports the REGION and ENDREGION directives (D9+)
  SUPPORTS_ENHANCED_RECORDS      Compiler supports class [operator|function|procedure] for record types (D9.NET, D10+)
  SUPPORTS_CLASS_FIELDS          Compiler supports class fields (D9.NET, D10+)
  SUPPORTS_CLASS_HELPERS         Compiler supports class helpers (D9.NET, D10+)
  SUPPORTS_CLASS_OPERATORS       Compiler supports class operators (D9.NET, D10+)
  SUPPORTS_CLASS_CTORDTORS       Compiler supports class contructors/destructors (D14+)
  SUPPORTS_STRICT                Compiler supports strict keyword (D9.NET, D10+)
  SUPPORTS_STATIC                Compiler supports static keyword (D9.NET, D10+)
  SUPPORTS_FINAL                 Compiler supports final keyword (D9.NET, D10+)
  SUPPORTS_METHODINFO            Compiler supports the METHODINFO directives (D10+)
  SUPPORTS_GENERICS              Compiler supports generic implementations (D11.NET, D12+)
  SUPPORTS_GENERIC_TYPES         Compiler supports generic implementations of types (D11.NET, D12+, FPC)
  SUPPORTS_GENERIC_METHODS       Compiler supports generic implementations of methods (D11.NET, D12+, FPC)
  SUPPORTS_GENERIC_ROUTINES      Compiler supports generic implementations of global functions/procedures (FPC)
  SUPPORTS_DEPRECATED_DETAILS    Compiler supports additional text for the deprecated directive (D11.NET, D12+)
  ACCEPT_DEPRECATED              Compiler supports or ignores the deprecated directive (D6+/BCB6+/FPC)
  ACCEPT_PLATFORM                Compiler supports or ignores the platform directive (D6+/BCB6+/FPC)
  ACCEPT_LIBRARY                 Compiler supports or ignores the library directive (D6+/BCB6+)
  SUPPORTS_CUSTOMVARIANTS        Compiler supports custom variants (D6+/BCB6+)
  SUPPORTS_VARARGS               Compiler supports varargs (D6+/BCB6+)
  SUPPORTS_ENUMVALUE             Compiler supports assigning ordinalities to values of enums (D6+/BCB6+)
  SUPPORTS_DEPRECATED_WARNINGS   Compiler supports deprecated warnings (D6+/BCB6+)
  SUPPORTS_LIBRARY_WARNINGS      Compiler supports library warnings (D6+/BCB6+)
  SUPPORTS_PLATFORM_WARNINGS     Compiler supports platform warnings (D6+/BCB6+)
  SUPPORTS_UNSAFE_WARNINGS       Compiler supports unsafe warnings (D7)
  SUPPORTS_WEAKPACKAGEUNIT       Compiler supports the WEAKPACKAGEUNIT directive
  SUPPORTS_COMPILETIME_MESSAGES  Compiler supports the MESSAGE directive
  SUPPORTS_PACKAGES              Compiler supports Packages
  HAS_UNIT_LIBC                  Unit Libc exists (Kylix, FPC on Linux/x86)
  HAS_UNIT_RTLCONSTS             Unit RTLConsts exists (D6+/BCB6+/FPC)
  HAS_UNIT_TYPES                 Unit Types exists (D6+/BCB6+/FPC)
  HAS_UNIT_VARIANTS              Unit Variants exists (D6+/BCB6+/FPC)
  HAS_UNIT_STRUTILS              Unit StrUtils exists (D6+/BCB6+/FPC)
  HAS_UNIT_DATEUTILS             Unit DateUtils exists (D6+/BCB6+/FPC)
  HAS_UNIT_CONTNRS               Unit contnrs exists (D6+/BCB6+/FPC)
  HAS_UNIT_HTTPPROD              Unit HTTPProd exists (D9+)
  HAS_UNIT_GIFIMG                Unit GifImg exists (D11+)
  HAS_UNIT_ANSISTRINGS           Unit AnsiStrings exists (D12+)
  HAS_UNIT_PNGIMAGE              Unit PngImage exists (D12+)
  HAS_UNIT_CHARACTER             Unit Character exists (D12+)
  XPLATFORM_RTL                  The RTL supports crossplatform function names (e.g. RaiseLastOSError) (D6+/BCB6+/FPC)
  SUPPORTS_UNICODE               string type is aliased to an unicode string (WideString or UnicodeString) (DX.NET, D12+)
  SUPPORTS_UNICODE_STRING        Compiler supports UnicodeString (D12+)
  SUPPORTS_INT_ALIASES           Types Int8, Int16, Int32, UInt8, UInt16 and UInt32 are defined in the unit System (D12+)
  HAS_UNIT_RTTI                  Unit RTTI is available (D14+)
  SUPPORTS_CAST_INTERFACE_TO_OBJ The compiler supports casts from interfaces to objects (D14+)
  SUPPORTS_DELAYED_LOADING       The compiler generates stubs for delaying imported function loads (D14+)
  HAS_UNIT_REGULAREXPRESSIONSAPI Unit RegularExpressionsAPI is available (D15+)
  HAS_UNIT_SYSTEM_UITYPES        Unit System.UITypes is available (D16+)
  HAS_UNIT_SYSTEM_ACTIONS        Unit System.Actions is available (D17+)
  DEPRECATED_SYSUTILS_ANSISTRINGS  AnsiString functions from SysUtils are deprecated and moved to System.AnsiStrings (D18+)
  HAS_PROPERTY_STYLEELEMENTS     TControl has a StyleElements property (D17+)
  HAS_AUTOMATIC_DB_FIELDS        Database fields are automatically created/refreshed (D20+)
  HAS_EARGUMENTEXCEPTION         Exception class EArgumentException is available (D14+)
  HAS_ENOTIMPLEMENTED            Exception class ENotImplemented is available (D15+)
  HAS_UNIT_VCL_THEMES            Unit Vcl.Themes is available (D16+)
  HAS_UNIT_UXTHEME               Unit (Vcl.)UxTheme is available (D7+)
  HAS_EXCEPTION_STACKTRACE       Exception class has the StackTrace propery (D12+)
  SUPPORTS_LEGACYIFEND           Compiler supports the LEGACYIFEND directive (D17+)
  DEPRECATED_TCHARACTER          TCharacter is deprecated and replaced by a record helper on Char (D18+)

- Compiler Settings
  The compiler settings directives indicate whether a specific compiler setting
  is in effect. This facilitates changing compiler settings locally in a more
  compact and readible manner.
  Directive              Description
  ------------------------------------------------------------------------------
  ALIGN_ON               Compiling in the A+ state (no alignment)
  BOOLEVAL_ON            Compiling in the B+ state (complete boolean evaluation)
  ASSERTIONS_ON          Compiling in the C+ state (assertions on)
  DEBUGINFO_ON           Compiling in the D+ state (debug info generation on)
  IMPORTEDDATA_ON        Compiling in the G+ state (creation of imported data references)
  LONGSTRINGS_ON         Compiling in the H+ state (string defined as AnsiString)
  IOCHECKS_ON            Compiling in the I+ state (I/O checking enabled)
  WRITEABLECONST_ON      Compiling in the J+ state (typed constants can be modified)
  LOCALSYMBOLS           Compiling in the L+ state (local symbol generation)
  LOCALSYMBOLS_ON        Alias of LOCALSYMBOLS
  TYPEINFO_ON            Compiling in the M+ state (RTTI generation on)
  OPTIMIZATION_ON        Compiling in the O+ state (code optimization on)
  OPENSTRINGS_ON         Compiling in the P+ state (variable string parameters are openstrings)
  OVERFLOWCHECKS_ON      Compiling in the Q+ state (overflow checing on)
  RANGECHECKS_ON         Compiling in the R+ state (range checking on)
  TYPEDADDRESS_ON        Compiling in the T+ state (pointers obtained using the @ operator are typed)
  SAFEDIVIDE_ON          Compiling in the U+ state (save FDIV instruction through RTL emulation)
  VARSTRINGCHECKS_ON     Compiling in the V+ state (type checking of shortstrings)
  STACKFRAMES_ON         Compiling in the W+ state (generation of stack frames)
  EXTENDEDSYNTAX_ON      Compiling in the X+ state (Delphi extended syntax enabled)
*/
/* Set FreePascal to Delphi mode */         
      // CPUX86 is not defined, which means it most likely is a 64 bits compiler.
      // However, this is only the case if either of two other symbols are defined:
      // http://docwiki.embarcadero.com/RADStudio/Seattle/en/Conditional_compilation_%28Delphi%29
    // None of the two 64-bits symbols are defined, assume this is 32-bit
   
    // The ASSEMBLER symbol appeared with Delphi 7
      
/*------------------------------------------------------------------------------*/
/* VERXXX to COMPILERX, DELPHIX and BCBX mappings                               */
/*------------------------------------------------------------------------------*/                                                                                                                  // adjust for newer version (always use latest version)
       
/*------------------------------------------------------------------------------*/
/* DELPHIX_UP from DELPHIX mappings                                             */
/*------------------------------------------------------------------------------*/                                                    
/*------------------------------------------------------------------------------*/
/* DELPHIX_UP from DELPHIX_UP mappings                                          */
/*------------------------------------------------------------------------------*/    // synonym to DELPHI26_UP
   // synonym to DELPHI25_UP
   // synonym to DELPHI24_UP
   // synonym to DELPHI23_UP
   // synonym to DELPHI22_UP
   // synonym to DELPHI21_UP
   // synonym to DELPHI20_UP
   // synonym to DELPHI19_UP
   // synonym to DELPHI18_UP
   // synonym to DELPHI17_UP
   // synonym to DELPHI16_UP
   // synonym to DELPHI15_UP
   // synonym to DELPHI14_UP
   // synonym to DELPHI12_UP
   // synonym to DELPHI11_UP
   // synonym to DELPHI10_UP
   // synonym to DELPHI9_UP
               
/*------------------------------------------------------------------------------*/
/* BCBX_UP from BCBX mappings                                                   */
/*------------------------------------------------------------------------------*/                                            
/*------------------------------------------------------------------------------*/
/* BCBX_UP from BCBX_UP mappings                                                */
/*------------------------------------------------------------------------------*/                                          
/*------------------------------------------------------------------------------*/
/* BDSX_UP from BDSX mappings                                                   */
/*------------------------------------------------------------------------------*/                                      
/*------------------------------------------------------------------------------*/
/* BDSX_UP from BDSX_UP mappings                                                */
/*------------------------------------------------------------------------------*/                                    
/*------------------------------------------------------------------------------*/
/* DELPHICOMPILERX_UP from DELPHICOMPILERX mappings                             */
/*------------------------------------------------------------------------------*/                                                    
/*------------------------------------------------------------------------------*/
/* DELPHICOMPILERX_UP from DELPHICOMPILERX_UP mappings                          */
/*------------------------------------------------------------------------------*/                                                    
/*------------------------------------------------------------------------------*/
/* COMPILERX_UP from COMPILERX mappings                                         */
/*------------------------------------------------------------------------------*/                                                      
/*------------------------------------------------------------------------------*/
/* COMPILERX_UP from COMPILERX_UP mappings                                      */
/*------------------------------------------------------------------------------*/                                                    
/*------------------------------------------------------------------------------*/
/* RTLX_UP from RTLX_UP mappings                                                */
/*------------------------------------------------------------------------------*/                                                              
/*------------------------------------------------------------------------------*/
/* Check for CLR overrides of default detection                                 */
/*------------------------------------------------------------------------------*/        
/*------------------------------------------------------------------------------*/
/* CLRX from CLRX_UP mappings                                                   */
/*------------------------------------------------------------------------------*/      
/*------------------------------------------------------------------------------*/
/* CLRX_UP from CLRX_UP mappings                                                */
/*------------------------------------------------------------------------------*/    
/*------------------------------------------------------------------------------*/    
/*------------------------------------------------------------------------------*/
/* KYLIXX_UP from KYLIXX mappings                                               */
/*------------------------------------------------------------------------------*/      
/*------------------------------------------------------------------------------*/
/* KYLIXX_UP from KYLIXX_UP mappings                                            */
/*------------------------------------------------------------------------------*/    
/*------------------------------------------------------------------------------*/
/* Map COMPILERX_UP to friendly feature names                                   */
/*------------------------------------------------------------------------------*/                                                                                                  
/*------------------------------------------------------------------------------*/
/* Cross-platform related defines                                               */
/*------------------------------------------------------------------------------*/    // predefined for D6+/BCB6+
           
/*------------------------------------------------------------------------------*/
/* Compiler settings                                                            */
/*------------------------------------------------------------------------------*/                
// Hints
                  
// Real compatibility
        
// Warnings
  
// for Delphi/BCB trial versions remove the point from the line below
/*.$UNDEF SUPPORTS_WEAKPACKAGEUNIT*/ 

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $
class DELPHICLASS TSynEditorOptionsContainer;
enum TColorPopup {cpGutter,
                  cpRightEdge };


  //NOTE: in order for the user commands to be recorded correctly, you must
  //      put the command itself in the object property.
  //      you can do this like so:
  //
  //      StringList.AddObject('ecSomeCommand', TObject(ecSomeCommand))
  //
  //      where ecSomeCommand is the command that you want to add
typedef void __fastcall (__closure *TSynEditorOptionsUserCommand) (int, String&);
typedef void __fastcall (__closure *TSynEditorOptionsAllUserCommands) (System::Classes::TStrings*);

class TfmEditorOptionsDialog : public TForm
{
__published:
	TPageControl* PageControl1;
	TButton* btnOK;
	TButton* btnCancel;
	TTabSheet* Display;
	TColorDialog* ColorDialog;
	TPopupMenu* ColorPopup;
	TMenuItem* None1;
	TMenuItem* Scrollbar1;
	TMenuItem* ActiveCaption1;
	TMenuItem* Background1;
	TMenuItem* InactiveCaption1;
	TMenuItem* Menu1;
	TMenuItem* Window1;
	TMenuItem* WindowFrame1;
	TMenuItem* Menu2;
	TMenuItem* WindowText1;
	TMenuItem* CaptionText1;
	TMenuItem* ActiveBorder1;
	TMenuItem* InactiveBorder1;
	TMenuItem* ApplicationWorkspace1;
	TMenuItem* Highlight1;
	TMenuItem* HighlightText1;
	TMenuItem* ButtonFace1;
	TMenuItem* ButtonShadow1;
	TMenuItem* GrayText1;
	TMenuItem* ButtonText1;
	TMenuItem* InactiveCaptionText1;
	TMenuItem* Highlight2;
	TMenuItem* N3dDarkShadow1;
	TMenuItem* N3DLight1;
	TMenuItem* InfoTipText1;
	TMenuItem* InfoTipBackground1;
	TImageList* ImageList1;
	TTabSheet* Options;
	TTabSheet* Keystrokes;
	TGroupBox* gbBookmarks;
	TCheckBox* ckBookmarkKeys;
	TCheckBox* ckBookmarkVisible;
	TGroupBox* gbLineSpacing;
	TEdit* eLineSpacing;
	TGroupBox* gbGutter;
	TLabel* Label1;
	TCheckBox* ckGutterAutosize;
	TCheckBox* ckGutterShowLineNumbers;
	TCheckBox* ckGutterShowLeaderZeros;
	TCheckBox* ckGutterStartAtZero;
	TCheckBox* ckGutterVisible;
	TGroupBox* gbRightEdge;
	TLabel* Label3;
	TPanel* pRightEdgeBack;
	TEdit* eRightEdge;
	TGroupBox* gbEditorFont;
	TButton* btnFont;
	TGroupBox* gbOptions;
	TCheckBox* ckAutoIndent;
	TCheckBox* ckDragAndDropEditing;
	TCheckBox* ckHalfPageScroll;
	TCheckBox* ckEnhanceEndKey;
	TCheckBox* ckScrollByOneLess;
	TCheckBox* ckScrollPastEOF;
	TCheckBox* ckScrollPastEOL;
	TCheckBox* ckShowScrollHint;
	TCheckBox* ckSmartTabs;
	TCheckBox* ckTabsToSpaces;
	TCheckBox* ckTrimTrailingSpaces;
	TCheckBox* ckWantTabs;
	TGroupBox* gbCaret;
	TComboBox* cInsertCaret;
	TLabel* Label2;
	TLabel* Label4;
	TComboBox* cOverwriteCaret;
	TPanel* Panel3;
	TLabel* labFont;
	TFontDialog* FontDialog;
	TButton* btnAddKey;
	TButton* btnRemKey;
	TGroupBox* gbKeyStrokes;
	TLabel* Label5;
	TLabel* Label6;
	TLabel* Label7;
	TComboBox* cKeyCommand;
	TButton* btnUpdateKey;
	TCheckBox* ckAltSetsColumnMode;
	TCheckBox* ckKeepCaretX;
	TEdit* eTabWidth;
	TPanel* pRightEdgeColor;
	TLabel* Label8;
	TLabel* Label9;
	TLabel* Label10;
	TCheckBox* cbGutterFont;
	TButton* btnGutterFont;
	TPanel* btnRightEdge;
	TImage* Image1;
	TPanel* pGutterBack;
	TPanel* pGutterColor;
	TPanel* btnGutterColor;
	TImage* Image2;
	TCheckBox* ckScrollHintFollows;
	TCheckBox* ckGroupUndo;
	TCheckBox* ckSmartTabDelete;
	TCheckBox* ckRightMouseMoves;
	TPanel* pnlGutterFontDisplay;
	TLabel* lblGutterFont;
	TCheckBox* ckEnhanceHomeKey;
	TPanel* pnlCommands;
	TListView* KeyList;
	TCheckBox* ckHideShowScrollbars;
	TCheckBox* ckDisableScrollArrows;
	TCheckBox* ckShowSpecialChars;
	void __fastcall PopupMenuClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall pGutterColorClick(TObject* Sender);
	void __fastcall pRightEdgeColorClick(TObject* Sender);
	void __fastcall btnFontClick(TObject* Sender);
	void __fastcall KeyListSelectItem(TObject* Sender, TListItem* Item, bool Selected);
	void __fastcall btnUpdateKeyClick(TObject* Sender);
	void __fastcall btnAddKeyClick(TObject* Sender);
	void __fastcall btnRemKeyClick(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall KeyListEditing(TObject* Sender, TListItem* Item, bool& AllowEdit);
	void __fastcall btnOKClick(TObject* Sender);
	void __fastcall btnGutterFontClick(TObject* Sender);
	void __fastcall cbGutterFontClick(TObject* Sender);
	void __fastcall btnRightEdgeMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall btnGutterColorMouseDown(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall cKeyCommandKeyUp(TObject* Sender, WORD& key, TShiftState Shift);
	void __fastcall KeyListChanging(TObject* Sender, TListItem* Item, TItemChange Change, bool& AllowChange);
private:
	TSynEditorOptionsContainer* FSynEdit;
	TColorPopup FPoppedFrom;
	TSynEditorOptionsUserCommand FUserCommand;
	TSynEditorOptionsAllUserCommands FAllUserCommands;
	TListItem* OldSelected;
	bool InChanging;
	bool FExtended;
	TColor __fastcall GetColor(Vcl::Menus::TMenuItem* Item);
	void __fastcall GetData();
	void __fastcall PutData();
	void __fastcall EditStrCallback(const String s);
	void __fastcall FillInKeystrokeInfo(Syneditkeycmds::TSynEditKeyStroke* AKey, Vcl::Comctrls::TListItem* AItem);
public:
	Syneditmiscclasses::TSynHotKey* eKeyShort2;
	Syneditmiscclasses::TSynHotKey* eKeyShort1;
	typedef Vcl::Forms::TForm inherited;	
	#include "SynEditOptionsDialog_friends.inc"
	bool __fastcall Execute(TSynEditorOptionsContainer* EditOptions);
	__property TSynEditorOptionsUserCommand GetUserCommandNames = { read = FUserCommand, write = FUserCommand };
	__property TSynEditorOptionsAllUserCommands GetAllUserCommands = { read = FAllUserCommands, write = FAllUserCommands };
	__property bool UseExtendedStrings = { read = FExtended, write = FExtended };
	__fastcall TfmEditorOptionsDialog(System::Classes::TComponent* AOwner);
};

class TSynEditOptionsDialog : public System::Classes::TComponent
{
private:
	TfmEditorOptionsDialog* FForm;
	TSynEditorOptionsUserCommand __fastcall GetUserCommandNames();
	void __fastcall SetUserCommandNames(const TSynEditorOptionsUserCommand Value);
	TSynEditorOptionsAllUserCommands __fastcall GetUserCommands();
	void __fastcall SetUserCommands(const TSynEditorOptionsAllUserCommands Value);
	bool __fastcall GetExtended();
	void __fastcall SetExtended(bool Value);
public:
	typedef System::Classes::TComponent inherited;	
	#include "SynEditOptionsDialog_friends.inc"
	__fastcall TSynEditOptionsDialog(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynEditOptionsDialog();
	bool __fastcall Execute(TSynEditorOptionsContainer* EditOptions);
	__property TfmEditorOptionsDialog* Form = { read = FForm };
__published:
	__property TSynEditorOptionsUserCommand GetUserCommand = { read = GetUserCommandNames, write = SetUserCommandNames };
	__property TSynEditorOptionsAllUserCommands GetAllUserCommands = { read = GetUserCommands, write = SetUserCommands };
	__property bool UseExtendedStrings = { read = GetExtended, write = SetExtended };
};

  //This class is assignable to a SynEdit without modifying key properties that affect function

class TSynEditorOptionsContainer : public System::Classes::TComponent
{
private:
	bool FHideSelection;
	bool FWantTabs;
	int FMaxUndo;
	int fExtraLineSpacing;
	int FTabWidth;
	int FMaxScrollWidth;
	int fRightEdge;
	Syneditmiscclasses::TSynSelectedColor* FSelectedColor;
	TColor fRightEdgeColor;
	Vcl::Graphics::TFont* FFont;
	Syneditmiscclasses::TSynBookMarkOpt* fBookMarks;
	Synedit::TSynEditCaretType fOverwriteCaret;
	Synedit::TSynEditCaretType fInsertCaret;
	Syneditkeycmds::TSynEditKeyStrokes* fKeyStrokes;
	Synedit::TSynEditorOptions fOptions;
	Syneditmiscclasses::TSynGutter* FSynGutter;
	TColor FColor;
	void __fastcall SetBookMarks(Syneditmiscclasses::TSynBookMarkOpt* const Value);
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall SetKeystrokes(Syneditkeycmds::TSynEditKeyStrokes* const Value);
	void __fastcall SetOptions(const Synedit::TSynEditorOptions Value);
	void __fastcall SetSynGutter(Syneditmiscclasses::TSynGutter* const Value);
public:
	typedef System::Classes::TComponent inherited;	
	#include "SynEditOptionsDialog_friends.inc"
	__fastcall TSynEditorOptionsContainer(System::Classes::TComponent* AOwner);
	virtual __fastcall ~TSynEditorOptionsContainer();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
__published:
	__property TSynEditorOptions Options = { read = fOptions, write = SetOptions };
	__property TSynBookMarkOpt* BookMarkOptions = { read = fBookMarks, write = SetBookMarks };
	__property TColor Color = { read = FColor, write = FColor };
	__property TFont* Font = { read = FFont, write = SetFont };
	__property int ExtraLineSpacing = { read = fExtraLineSpacing, write = fExtraLineSpacing };
	__property TSynGutter* Gutter = { read = FSynGutter, write = SetSynGutter };
	__property int RightEdge = { read = fRightEdge, write = fRightEdge };
	__property TColor RightEdgeColor = { read = fRightEdgeColor, write = fRightEdgeColor };
	__property bool WantTabs = { read = FWantTabs, write = FWantTabs };
	__property TSynEditCaretType InsertCaret = { read = fInsertCaret, write = fInsertCaret };
	__property TSynEditCaretType OverwriteCaret = { read = fOverwriteCaret, write = fOverwriteCaret };
	__property bool HideSelection = { read = FHideSelection, write = FHideSelection };
	__property int MaxScrollWidth = { read = FMaxScrollWidth, write = FMaxScrollWidth };
	__property int MaxUndo = { read = FMaxUndo, write = FMaxUndo };
	__property TSynSelectedColor* SelectedColor = { read = FSelectedColor, write = FSelectedColor };
	__property int TabWidth = { read = FTabWidth, write = FTabWidth };
	__property TSynEditKeyStrokes* Keystrokes = { read = fKeyStrokes, write = SetKeystrokes };
};
#endif // SynEditOptionsDialogH

