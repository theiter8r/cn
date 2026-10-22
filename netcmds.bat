@echo off
REM Experiment 2 - Networking Commands (Windows)
REM Usage: netcmds.bat [target]   (default target: google.com)
set T=%1
if "%T%"=="" set T=google.com
set OUT=output.txt
echo Experiment 2 - Networking Commands > %OUT%
echo Target: %T% >> %OUT%

call :run "hostname"
call :run "ipconfig /all"
call :run "getmac /v"
call :run "ping -n 4 %T%"
call :run "tracert -d -h 15 %T%"
call :run "nslookup %T%"
call :run "arp -a"
call :run "netstat -an"
call :run "route print"
call :run "pathping -n -q 10 -h 10 %T%"

echo.
echo Done. All output saved to %OUT%
pause
goto :eof

:run
echo.
echo ===== %~1 =====
echo. >> %OUT%
echo ===== %~1 ===== >> %OUT%
%~1 > tmp_out.txt 2>&1
type tmp_out.txt
type tmp_out.txt >> %OUT%
del tmp_out.txt
goto :eof
