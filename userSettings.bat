@echo off

rem ============================================================================
rem user depended path settings
rem ============================================================================
call %HOMEDRIVE%\%HOMEPATH%\bin\mySettings.bat

rem ============================================================================
rem GCC compiller path
rem ============================================================================
IF "%ARM_GCC_PATH%"=="" (
  ECHO ARM_GCC_PATH is NOT defined - check your mySettings.bat!
  GOTO End
)
set MY_PATH=%ARM_GCC_PATH%

rem ============================================================================
rem GNU tools (AWK, RM, etc.)
rem ============================================================================
IF "%GNUWIN32_PATH%"=="" (
  ECHO GNUWIN32_PATH is NOT defined - check your mySettings.bat!
rem  GOTO End
)
set MY_PATH=%MY_PATH%;%GNUWIN32_PATH%

rem ============================================================================
rem Python (versions 3.x)
rem ============================================================================
IF "%PYTHON3_PATH%"=="" (
  ECHO PYTHON3_PATH is NOT defined - check your mySettings.bat!
rem  GOTO End
)
set MY_PATH=%MY_PATH%;%PYTHON3_PATH%

rem ============================================================================
rem git
rem ============================================================================
IF "%GIT_PATH%"=="" (
  ECHO GIT_PATH is NOT defined - check your mySettings.bat!
  GOTO End
)
set MY_PATH=%MY_PATH%;%GIT_PATH%

rem ============================================================================
rem doxygen settings
rem ============================================================================
IF "%DOXYGEN_PATH%"=="" (
  ECHO DOXYGEN_PATH is NOT defined - check your mySettings.bat!
  rem Just optional tool, a missing path should not cause terminating the build process
  rem GOTO End
)
set MY_PATH=%MY_PATH%;%DOXYGEN_PATH%

rem ============================================================================
rem Typesetting tools settings
rem ============================================================================
IF "%GHOSTSCRIPT_PATH%"=="" (
  ECHO GHOSTSCRIPT_PATH is NOT defined - check your mySettings.bat!
  rem Just optional tool, a missing path should not cause terminating the build process
  rem GOTO End
)
set MY_PATH=%MY_PATH%;%GHOSTSCRIPT_PATH%

IF "%GRAPHVIZ_PATH%"=="" (
  ECHO GRAPHVIZ_PATH is NOT defined - check your mySettings.bat!
  rem Just optional tool, a missing path should not cause terminating the build process
  rem GOTO End
)
set MY_PATH=%MY_PATH%;%GRAPHVIZ_PATH%


rem ============================================================================
echo MY_PATH=%MY_PATH%

set PATH=%MY_PATH%

:End