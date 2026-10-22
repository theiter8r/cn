BEGIN { sent=0; dropped=0; tsent=0; tdrop=0 }
{
    if ($5=="cbr" && $1=="+") sent++
    if ($5=="cbr" && $1=="d") dropped++
    if ($5=="tcp" && $1=="+") tsent++
    if ($5=="tcp" && $1=="d") tdrop++
}
END {
    print "UDP Packets Sent: " sent
    print "UDP Packets Dropped: " dropped
    if (sent > 0) print "UDP Packet Loss Rate: " (dropped/sent)*100 "%"
    print "TCP Packets Sent: " tsent
    print "TCP Packets Dropped: " tdrop
    if (tsent > 0) print "TCP Packet Loss Rate: " (tdrop/tsent)*100 "%"
}
