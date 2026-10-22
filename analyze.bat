@echo off
REM Experiment 12 - security summary of a saved capture using tshark
REM Usage: analyze.bat capture.pcapng
setlocal
set F=%~1
if "%F%"=="" (echo Usage: analyze.bat capture.pcapng & exit /b 1)
set TS=tshark
where tshark >nul 2>&1 || set TS=C:\Program Files\Wireshark\tshark.exe
set OUT=report.txt

echo Experiment 12 - Packet Security Analysis of %F% > %OUT%

set A=-q -z io,phs
call :sec "Protocol hierarchy"
set A=-q -z conv,ip
call :sec "IP conversations"
set A=-q -z conv,tcp
call :sec "TCP conversations (source / destination IP and ports)"
set A=-Y "tls.handshake.type == 1" -T fields -e ip.dst -e tls.handshake.extensions_server_name
call :sec "TLS server names (encrypted, but site name visible)"
set A=-Y "dns.flags.response == 0" -T fields -e ip.src -e ip.dst -e dns.qry.name
call :sec "DNS queries (domain names exposed)"
set A=-Y "http.request" -T fields -e ip.dst -e http.host -e http.request.uri
call :sec "HTTP (unencrypted) requests"
set A=-Y "http.request.method == \"POST\"" -T fields -e ip.dst -e http.host -e http.file_data
call :sec "HTTP POST in clear text"

type %OUT%
echo.
echo Saved to %OUT%. Empty HTTP sections = no plain-text web traffic (good).
exit /b 0

:sec
echo. >> %OUT%
echo ===== %~1 ===== >> %OUT%
"%TS%" -r "%F%" %A% >> %OUT% 2>nul
exit /b
