# Experiment 9 - Wireshark capture and display filters

1. Open Wireshark, pick the active Wi-Fi/Ethernet interface, start capture.
2. Log in to Facebook / Instagram / YouTube in the browser, then stop the capture.
3. Use the filters in `filters.txt` (a, b, c). The packet count is shown in the status bar.
4. Save as `capture.pcapng`.

Automatic counting (uses tshark, installed with Wireshark):
```
count.bat capture.pcapng 142.251.221.238
```
Prints total TCP, SYN/PSH/RST counts with percentages, and TCP/HTTP packets
sent to / received from the server IP. Output is saved to `result.txt`.

Find the server IP with filter `dns.qry.name contains "youtube"` (look at the answer)
or `tls.handshake.extensions_server_name contains "youtube"` (destination IP).
