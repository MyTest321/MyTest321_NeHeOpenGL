@REM #change current directory to this file
@%~d0
@cd %~dp0

cmake -G "Visual Studio 17 2022" -DOPT_CG_TOOLKIT=ON -A Win32 -B build/NeHeOpenGL-x86-windows .

@pause