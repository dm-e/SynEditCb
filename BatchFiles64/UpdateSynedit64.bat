@echo off

set "ConvertExe=C:\Program Files (x86)\Delphi2CB\Delphi2CB.exe"
set "ExtractExe=ExtractReworked.exe"
set "project=Synedit.prj"
set "source=..\Source\*.pas;*.dpr"

set "generated=..\SourceCppRaw64"
set "working=..\SourceCppRun64"
set "reworked=..\SourceCppReworked64"
set "generatedFound=0"

if exist "%generated%" (
    dir /b "%generated%" >nul 2>&1
    if not errorlevel 1 set "generatedFound=1"
) else (
    echo Directory "%generated%" does not exist.
)

if "%generatedFound%"=="1" (
    "%ExtractExe%" -g "%generated%" -w "%working%" -r "%reworked%" -d
)

"%ConvertExe%" -p "%project%" -s "%source%" -t "%generated%" -r

if "%generatedFound%"=="1" (
    xcopy /s /y "%generated%" "%working%"
    xcopy /s /y "%reworked%" "%working%"
)

pause