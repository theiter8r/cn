# Experiment 11 - Basic terminal security commands (GNS3 / Packet Tracer)

Topology: R1 Fa0/0 (192.168.1.1) --- switch --- PC/VPCS (192.168.1.10/24, gw 192.168.1.1).
VPCS: `ip 192.168.1.10/24 192.168.1.1`.

1. Open R1 console, paste `R1-security.txt`.
   (`crypto key generate rsa` may ask for a size: enter 1024.)
2. Run the checks in `verify.txt`.

| Command | Purpose |
|---|---|
| enable secret | Encrypted privileged-mode password |
| line console 0 / password / login | Console password |
| exec-timeout 5 0 | Auto logout when idle |
| service password-encryption | Hides plain-text passwords (type 7) |
| security passwords min-length | Minimum password length |
| banner motd | Warning banner at login |
| login block-for | Stops brute-force login attempts |
| username / login local | Local user database |
| transport input ssh | Allow only SSH on VTY |
| no ip http server, no cdp run | Turn off unused services |

Packet Tracer 1941: replace `FastEthernet0/0` with `GigabitEthernet0/0`.
Default passwords here are for the lab only.
