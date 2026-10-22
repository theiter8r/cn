@echo off
REM Experiment 9 - count TCP flags and server packets from a saved capture with tshark
REM Usage: count.bat capture.pcapng [SERVER_IP]
setlocal
set F=%~1
set IP=%~2
if "%F%"=="" (echo Usage: count.bat capture.pcapng [SERVER_IP] & exit /b 1)
set TS=tshark
where tshark >nul 2>&1 || set TS=C:\Program Files\Wireshark\tshark.exe
set OUT=result.txt

call :count "tcp"
set TOTAL=%C%
echo Total TCP packets = %TOTAL% > %OUT%
if "%TOTAL%"=="0" (type %OUT% & exit /b 0)

echo. >> %OUT%
echo Flag  Packets  Percentage >> %OUT%
call :flag SYN "tcp.flags.syn == 1"
call :flag PSH "tcp.flags.push == 1"
call :flag RST "tcp.flags.reset == 1"

if not "%IP%"=="" (
  echo. >> %OUT%
  call :line "TCP received " "tcp && ip.src == %IP%"
  call :line "TCP sent     " "tcp && ip.dst == %IP%"
  call :line "HTTP received" "http && ip.src == %IP%"
  call :line "HTTP sent    " "http && ip.dst == %IP%"
)
del _c.txt 2>nul
type %OUT%
echo.
echo Saved to %OUT%
exit /b 0

:count
"%TS%" -r "%F%" -Y "%~1" > _c.txt 2>nul
for /f %%c in ('find /c /v "" ^< _c.txt') do set C=%%c
exit /b

:flag
call :count %2
set /a BP=C*10000/TOTAL
set /a W=BP/100
set /a D=BP%%100
if %D% LSS 10 set D=0%D%
echo %1   %C%   %W%.%D%%%   (filter: %~2) >> %OUT%
exit /b

:line
call :count %2
echo %~1 = %C%   (filter: %~2) >> %OUT%
exit /b
