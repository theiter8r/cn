# Experiment 8 - UDP File Transfer in C (Windows / Winsock), port 6000

## Build (MinGW gcc)
```
build.bat
```

## Run
Server PC, in the folder that has the file to send (e.g. `sample.txt`):
```
udp_server
```
Client PC:
```
udp_client 192.168.1.10 sample.txt
```
(or just `udp_client` and type the IP and file name). Use 127.0.0.1 to test on one PC.

The client saves the file as `received_<name>`. A missing file prints
`File not found`. The server keeps running for more requests (Ctrl+C to stop).
Allow the programs in the Windows Firewall prompt.
