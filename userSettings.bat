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
echo MY_PATH=%MY_PATH%

set PATH=%MY_PATH%

:End