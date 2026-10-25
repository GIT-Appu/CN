# Raw Socket Packet Capture

Captures packets visible to the local Linux machine and prints Ethernet, IP, and TCP/UDP/ICMP header fields. Use it only on networks and machines you are authorized to inspect.

This example uses Linux packet-socket headers, so it will not compile on macOS or Windows.

```sh
gcc -Wall -Wextra packet-capture.c -o packet-capture
sudo ./packet-capture
```

Press `Ctrl+C` to stop. Root privileges (or the `CAP_NET_RAW` capability) are required to open the raw socket.
