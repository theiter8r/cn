# Experiment 7 - TCP Socket Programming in C (Windows / Winsock)

| Part | Program | Port |
|---|---|---|
| a | Hello + Chatbot (`chat_server.c`, `chat_client.c`) | 5000 |
| b | Calculator + Factorial (`calc_server.c`, `calc_client.c`) | 5001 |

## Build (MinGW gcc)
```
build.bat
```
or manually: `gcc chat_server.c -o chat_server -lws2_32`

## Run
Server PC (allow it in the Windows Firewall prompt):
```
chat_server
```
Client PC (use the server's IP from `ipconfig`, or 127.0.0.1 on the same PC):
```
chat_client 192.168.1.10
```
Chat: `hello`, `what is your name`, `how are you`, `what is tcp`, `bye`.

Calculator: run `calc_server`, then `calc_client 192.168.1.10` and type
`12 + 5`, `7 * 3`, `10 / 4`, `2 ^ 8`, `fact 5` or `5!`, `exit`.

Cisco Packet Tracer / GNS3: put both PCs in the same subnet (or routed),
check with `ping <server-ip>` first, then run the programs on real/VM Windows hosts.
