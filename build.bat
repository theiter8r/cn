@echo off
gcc udp_server.c -o udp_server.exe -lws2_32 || goto :err
gcc udp_client.c -o udp_client.exe -lws2_32 || goto :err
echo Build OK: udp_server.exe udp_client.exe
goto :eof
:err
echo Build failed. Make sure MinGW gcc is in PATH.
