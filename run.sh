#!/bin/sh
# Run on Ubuntu / WSL with ns2 installed:
#   sudo apt-get update && sudo apt-get install ns2 nam tcl
#   (if dpkg error: sudo dpkg --configure -a)
ns exp3.tcl
ls -l out.*
awk -f analyze.awk out.tr
nam out.nam &
