# Experiment 12 - Packet analysis for security issues (Wireshark)

1. Open Wireshark, select the active Ethernet/Wi-Fi interface, start capture.
2. Browse a few sites for a minute (optionally `http://neverssl.com` for plain HTTP), stop.
3. Apply filters `tcp`, `dns`, `http` (and others in `filters.txt`) and note src/dst IP and ports.
4. File > Save As `capture.pcapng`.

Automatic report (tshark, installed with Wireshark):
```
analyze.bat capture.pcapng
```
Writes `report.txt`: protocol hierarchy, IP conversations, TCP ports, TLS site names,
DNS queries, any plain-text HTTP requests and POSTs.

## Observation table
| Filter | Protocol | Observation | Security issue |
|---|---|---|---|
| tcp | TCP / TLSv1.2 | Traffic to port 443 | Encrypted payload, but IPs/ports/timing visible |
| dns | DNS | Queries and responses to local DNS server | Domain names exposed in clear text |
| http | HTTP | None (or neverssl.com) | Plain HTTP exposes full content |
| tls.handshake.extensions_server_name | TLS | Site names in Client Hello | SNI reveals visited site |
