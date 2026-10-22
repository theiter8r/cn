# Experiment 4 - Mesh Topology (Cisco Packet Tracer)

Devices: 4 PCs, 4 Cisco 2960 switches, 4 straight-through, 6 cross-over cables.

## Cabling (full mesh)
| Link | Cable |
|---|---|
| Switch0 Fa0/2 - Switch1 Fa0/2 | Cross-Over |
| Switch0 Fa0/3 - Switch2 Fa0/3 | Cross-Over |
| Switch0 Fa0/4 - Switch3 Fa0/4 | Cross-Over |
| Switch1 Fa0/5 - Switch2 Fa0/5 | Cross-Over |
| Switch1 Fa0/6 - Switch3 Fa0/6 | Cross-Over |
| Switch2 Fa0/7 - Switch3 Fa0/7 | Cross-Over |
| PC0 - Switch0 Fa0/1 | Straight |
| PC1 - Switch3 Fa0/1 | Straight |
| PC2 - Switch2 Fa0/1 | Straight |
| PC3 - Switch1 Fa0/1 | Straight |

## Steps
1. Build the topology above.
2. Optional: paste `Switch0.txt`..`Switch3.txt` into each switch CLI (names the switches).
3. Set PC IPs from `pc-ips.txt`.
4. Ping between PCs. Orange links = ports blocked by STP (normal, prevents loops).

`hub-switch.md` covers the hub/switch version of this experiment.
