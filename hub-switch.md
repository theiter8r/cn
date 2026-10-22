# Hub vs Switch topology (Packet Tracer)

1. Place 1 Hub-PT, 1 Switch 2960 and 6 PCs.
2. PC0, PC1, PC2 -> Hub-PT (Copper Straight-Through).
3. PC3, PC4, PC5 -> Switch (Copper Straight-Through).
4. Hub <-> Switch with Copper Cross-Over.
5. IPs 192.168.1.1 to 192.168.1.6, mask 255.255.255.0.
6. Switch to Simulation mode, send a PDU from PC0 to PC1:
   - Hub floods the frame to every port (all PCs see it).
   - Switch learns MACs and forwards only to the destination port (check `show mac address-table`).
7. Ping all PCs to verify.
