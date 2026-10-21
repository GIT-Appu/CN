# Static Routing, OSPF, and RIPv2

Replace values in angle brackets with the addresses from the supplied topology. Configure router interfaces and `no shutdown` first.

## 1. Static routing

Add one route for every remote network on each router:

```text
enable
configure terminal
ip route <destination-network> <subnet-mask> <next-hop-ip>
end
show ip route
copy running-config startup-config
```

Example: on a router that reaches `192.168.3.0/24` through `10.0.12.2`:

```text
ip route 192.168.3.0 255.255.255.0 10.0.12.2
```

## 2. OSPF (single area)

Use the same process ID on every router; the process ID is locally significant, but matching it avoids confusion. Advertise all connected networks in area 0.

```text
enable
configure terminal
router ospf 1
router-id <unique-router-id>
network <network-address> <wildcard-mask> area 0
network <other-network-address> <wildcard-mask> area 0
end
show ip ospf neighbor
show ip route ospf
copy running-config startup-config
```

Common wildcard masks: `/24` → `0.0.0.255`; `/30` → `0.0.0.3`.

## 3. RIPv2

Advertise each directly connected major network and disable automatic summarization.

```text
enable
configure terminal
router rip
version 2
no auto-summary
network <directly-connected-network>
network <other-directly-connected-network>
end
show ip protocols
show ip route rip
copy running-config startup-config
```

## Verification checklist

1. `show ip interface brief` — interface IPs are correct and interfaces are up/up.
2. `show ip route` — remote networks appear with `S`, `O`, or `R` as appropriate.
3. Ping between PCs on different LANs.
4. Run `tracert <remote-PC-IP>` from a PC to confirm the intended path.
5. Save the Packet Tracer file and capture screenshots of the topology, a successful ping, and the routing table.
