setlocal

@echo off

set CURPATH=%~dp0
set MSBUILD_PATH=C:\Program Files\Microsoft Visual Studio\2022\Professional\Msbuild\Current\Bin
set OSTRICH_PATH=%CURPATH%\Ostrich
set OSTRICH_SLN_PATH=%CURPATH%\Ostrich\Ostrich.sln
set VCVARS64_PATH=C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvars64.bat
set SETUP_PATH=%CURPATH%\Setup
set BUILD_OUTPUT_PATH=%CURPATH%\Setup\output

echo Ostrich2 build will start 
echo hit enter key please 
pause

echo progressing deleting output directory...
rmdir %BUILD_OUTPUT_PATH% /S /Q


echo progressing msbuild...
cd %MSBUILD_PATH%
call "%VCVARS64_PATH%"



rmdir %OSTRICH_PATH%\Ostrich\bin\x64\Release\ /S /Q
msbuild.exe -t:restore -p:RestorePackagesConfig=true "%OSTRICH_SLN_PATH%" /p:Configuration="Release" /p:Platform="x64" /t:Ostrich /m
msbuild.exe -t:restore -p:RestorePackagesConfig=true "%OSTRICH_SLN_PATH%" /p:Configuration="Release" /p:Platform="x64" /t:PrimitiveNodeExtension /m

: 출력 폴더 생성
mkdir %BUILD_OUTPUT_PATH%

: VisionStudio 복사
xcopy /y /c /e /h /k %OSTRICH_PATH%\Ostrich\bin\x64\Release\net6.0-windows\*.* %BUILD_OUTPUT_PATH%\
xcopy /y /c /e /h /k %OSTRICH_PATH%\x64\Release\*.* %BUILD_OUTPUT_PATH%\


:Addon 이동
mkdir %BUILD_OUTPUT_PATH%\Addon\
xcopy /y /c /e /h /k %SETUP_PATH%\Addon\*.* %BUILD_OUTPUT_PATH%\Addon\

:불필요 파일 삭제
del /S %BUILD_OUTPUT_PATH%\*.pdb
del /S %BUILD_OUTPUT_PATH%\*.lib
del /S %BUILD_OUTPUT_PATH%\*.exp

:cd C:\Program Files (x86)\Inno Setup 6

"C:\Program Files (x86)\Inno Setup 6\iscc.exe" %SETUP_PATH%\OstrichPackage.iss


:아웃풋 경로 삭제
rmdir %BUILD_OUTPUT_PATH% /S /Q

endlocal