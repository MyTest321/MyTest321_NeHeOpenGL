@REM #change current directory to this file
@%~d0
@cd %~dp0

@REM using x86 cuz glaux.lib is build from x86

cmake -G "Visual Studio 17 2022" -A Win32 -B build/NeHeOpenGL-x86-windows2 .

@pause