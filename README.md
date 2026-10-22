# Experiment 6 - Dynamic Routing, RIP v2 (GNS3 / Packet Tracer)

```
 [R1]Fa0/0 ---- Fa0/0[R2]Fa0/1 ---- Fa0/0[R3]Fa0/1 ---- Fa0/0[R4]
     10.0.12.0/24          10.0.23.0/24          10.0.34.0/24
 Loopback0: R1 1.1.1.1  R2 2.2.2.2  R3 3.3.3.3  R4 4.4.4.4
```

1. Add 4 routers, connect R1-R2, R2-R3, R3-R4 as shown.
2. Paste `R1.txt`..`R4.txt` (RIP v2) into each router.
   For OSPF instead, paste the files in `ospf/` (`router ospf 100`, area 0) - as in the lab manual.
3. Wait ~30 s (RIP) and run `verify.txt`. Routes marked `R` (RIP) or `O` (OSPF) are learnt dynamically.
4. Shut a link (`interface Fa0/1` / `shutdown`) and watch the route disappear from `show ip route`.

**Packet Tracer:** use 2811 routers (have Fa0/0, Fa0/1). On 1941/2911 routers replace
`FastEthernet0/0` with `GigabitEthernet0/0` and `FastEthernet0/1` with `GigabitEthernet0/1`.
**GNS3:** c3725 / c7200 with FastEthernet slots (c7200: add a PA-2FE-TX and swap names if needed).
