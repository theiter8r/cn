# Experiment 3 - TCP and UDP traffic generation using NS2

NS2 runs on Linux. On Windows use WSL (Ubuntu):

```
sudo apt-get update
sudo apt-get install ns2 nam tcl      # if dpkg error: sudo dpkg --configure -a
sh run.sh
```

`run.sh` runs `ns exp3.tcl`, lists `out.tr` / `out.nam`, prints TCP and UDP sent/dropped/loss
using `analyze.awk`, and opens the animation in NAM.

Topology: n0 --2Mb-- n2 --1.7Mb-- n3, n1 --2Mb-- n2.
TCP (FTP) n0 -> n3 from 0.5s to 4.0s, UDP (CBR 1Mb, 1000 bytes) n1 -> n3 from 0.1s to 4.5s.
