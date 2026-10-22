@echo off
gcc chat_server.c -o chat_server.exe -lws2_32 || goto :err
gcc chat_client.c -o chat_client.exe -lws2_32 || goto :err
gcc calc_server.c -o calc_server.exe -lws2_32 || goto :err
gcc calc_client.c -o calc_client.exe -lws2_32 || goto :err
echo Build OK: chat_server.exe chat_client.exe calc_server.exe calc_client.exe
goto :eof
:err
echo Build failed. Make sure MinGW gcc is in PATH.
