setlocal

set CURPATH=%~dp0

pause

echo progressing deleting output directory...


rmdir %CURPATH%\Setup\output /S /Q
rmdir %CURPATH%\Setup\Addon /S /Q

rmdir %CURPATH%\Ostrich\AddonPrimitiveNode\x64 /S /Q
rmdir %CURPATH%\Ostrich\ConsoleCpp\x64 /S /Q
rmdir %CURPATH%\Ostrich\ConsoleSharp\bin /S /Q
rmdir %CURPATH%\Ostrich\ConsoleSharp\obj /S /Q

rmdir %CURPATH%\Ostrich\Model\bin /S /Q
rmdir %CURPATH%\Ostrich\Model\obj /S /Q

rmdir %CURPATH%\Ostrich\Ostrich\bin /S /Q
rmdir %CURPATH%\Ostrich\Ostrich\obj /S /Q

rmdir %CURPATH%\Ostrich\OstrichAPI\x64 /S /Q

rmdir %CURPATH%\Ostrich\OstrichAPISharp\x64 /S /Q
rmdir %CURPATH%\Ostrich\OstrichAPISharp\obj /S /Q

rmdir %CURPATH%\Ostrich\PrimitiveNode\x64 /S /Q

rmdir %CURPATH%\Ostrich\PrimitiveNodeExtension\x64 /S /Q
rmdir %CURPATH%\Ostrich\PrimitiveNodeExtension\obj /S /Q


rmdir %CURPATH%\Ostrich\UC\bin /S /Q
rmdir %CURPATH%\Ostrich\UC\obj /S /Q

rmdir %CURPATH%\Ostrich\View\bin /S /Q
rmdir %CURPATH%\Ostrich\View\obj /S /Q

rmdir %CURPATH%\Ostrich\ViewModel\bin /S /Q
rmdir %CURPATH%\Ostrich\ViewModel\obj /S /Q

endlocal