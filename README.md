# Experiment 2 - Networking Commands

Run on any Windows PC (double-click or from CMD):

```
netcmds.bat
netcmds.bat 8.8.8.8
```

Runs: `hostname`, `ipconfig /all`, `getmac`, `ping`, `tracert`, `nslookup`, `arp -a`,
`netstat -an`, `route print`, `pathping`. Everything is also saved to `output.txt`.

| Command | Purpose |
|---|---|
| ping | Tests reachability with ICMP echo, shows RTT and loss |
| ipconfig | Shows IP, mask, gateway, DNS of each adapter |
| tracert | Shows each hop to the destination |
| netstat | Active connections and listening ports |
| nslookup | DNS name to IP lookup |
| arp | IP to MAC cache |
| route | Routing table |
| hostname | Name of this computer |
| pathping | ping + tracert with per-hop loss |
| getmac | MAC addresses of adapters |
