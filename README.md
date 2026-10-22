# Experiment 10 - DHCP Server and Client (Cisco Packet Tracer)

## Topology
| Device | Port | Switch 2960 port |
|---|---|---|
| Server-PT | FastEthernet0 | Fa0/1 |
| PC0 | FastEthernet0 | Fa0/2 |
| PC1 | FastEthernet0 | Fa0/3 |
| PC2 | FastEthernet0 | Fa0/4 |

All copper straight-through cables.

## Steps
1. Build the topology.
2. Configure the server and the DHCP pool exactly as in `server-config.txt`.
3. On each PC: Desktop > IP Configuration > DHCP. You should see "DHCP request successful"
   and addresses 192.168.1.10, .11, .12.
4. Command Prompt on PC0: `ipconfig`, `ping 192.168.1.11`.

## Simulation mode (DORA)
Edit Filters > show only DHCP, ICMP. On PC0 switch Static then DHCP again, press Play:

| # | Message | Direction |
|---|---|---|
| 1 | DHCPDISCOVER | Client -> Broadcast 255.255.255.255 |
| 2 | DHCPOFFER | Server -> Client |
| 3 | DHCPREQUEST | Client -> Broadcast |
| 4 | DHCPACK | Server -> Client |

GNS3 / router version: `router-dhcp.txt` (VPCS: `ip dhcp`).
