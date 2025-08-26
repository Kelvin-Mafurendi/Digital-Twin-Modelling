
cd .

if "%1"=="" ("E:\MATLAB\bin\win64\gmake"  DEPRULES=1 -j5  -f test_c2000.mk all) else ("E:\MATLAB\bin\win64\gmake"  DEPRULES=1 -j5  -f test_c2000.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1