# Lab 10  

## IP GRID

| Name                  | Interface         | Address/Mask         |
|-----------------------|-------------------|----------------------|
| **WAN Network**       |                   | 132.235.205.0/25     |
| VyOS-1                | eth0             | 132.235.205.3     |
| (WAN Gateway)         |                  | 132.235.205.126   |
| **LAN1 Network**      |                   | 192.168.15.0/25      |
| DHCP Pool Start       |                   | 192.168.15.10/25     |
| DHCP Pool Stop        |                   | 192.168.15.100    |
| VyOS-1 (LAN1 Gateway) | eth6             | 192.168.15.126      |
| **LAN2 Network**      |                   | 192.168.15.160/30    |
| VyOS-1 (LAN2 Gateway) | eth1             | 192.168.15.162    |
| VyOS-2 (LAN2 Client)  | eth0             | 192.168.15.161    |
| **LAN3 Network**      |                   | 192.168.14.0/24      |
| DHCP Pool Start       |                   | 192.168.14.10     |
| DHCP Pool Stop        |                   | 192.168.14.200    |
| VyOS-2 (LAN3 Gateway) | eth7             | 192.168.14.254      |
| **LAN4 Network**      |                   | 192.168.15.128/27    |
| DHCP Pool Start       |                   | 192.168.15.130    |
| DHCP Pool Stop        |                   | 192.168.15.150    |
| VyOS-2 (LAN4 Gateway) | eth6             | 192.168.15.158    |

## VyOS 1 Bash Script

```bash
config
set interfaces ethernet eth0 address 132.235.205.3/25
set interfaces ethernet eth0 description WAN
set protocols static route 0.0.0.0/0 next-hop 132.235.205.126
set system name-server 132.235.9.75
set system name-server 132.235.200.41
################# LAN 1 #####################
set interfaces ethernet eth6 address 192.168.15.1/25
set interfaces ethernet eth6 description LAN1_Gateway
set service dhcp-server shared-network-name LAN1_POOL subnet 192.168.15.0/25 range 0 start 192.168.15.10
set service dhcp-server shared-network-name LAN1_POOL subnet 192.168.15.0/25 range 0 stop 192.168.15.100
set service dhcp-server shared-network-name LAN1_POOL subnet 192.168.15.0/25 default-router 192.168.15.126
set service dhcp-server shared-network-name LAN1_POOL subnet 192.168.15.0/25 lease 120
set service dhcp-server shared-network-name LAN1_POOL subnet 192.168.15.0/25 name-server 132.235.9.75
set service dhcp-server shared-network-name LAN1_POOL subnet 192.168.15.0/25 name-server 132.235.200.41
################ LAN 2 ####################
set interfaces ethernet eth1 address 192.168.15.162/30
set interfaces ethernet eth1 description LAN2_Gateway
################ NAT ######################
set nat source rule 100 outbound-interface eth0
set nat source rule 100 source address 192.168.14.0/23
set nat source rule 100 translation address masquerade
set protocols static route 192.168.14.0/24 next-hop 192.168.15.161
set protocols static route 192.168.15.128/27 next-hop 192.168.15.161

commit
```

## VyOS 2 Bash Script

```bash
config
set interfaces ethernet eth0 address 192.168.15.161/30

set interfaces ethernet eth7 address 192.168.14.254/24
set interfaces ethernet eth7 description LAN3_Gateway
set service dhcp-server shared-network-name LAN3_POOL subnet 192.168.14.0/24 range 0 start 192.168.14.10
set service dhcp-server shared-network-name LAN3_POOL subnet 192.168.14.0/24 range 0 stop 192.168.14.200
set service dhcp-server shared-network-name LAN3_POOL subnet 192.168.14.0/24 default-router 192.168.14.254
set service dhcp-server shared-network-name LAN3_POOL subnet 192.168.14.0/24 lease 120
set service dhcp-server shared-network-name LAN3_POOL subnet 192.168.14.0/24 name-server 132.235.9.75
set service dhcp-server shared-network-name LAN3_POOL subnet 192.168.14.0/24 name-server 132.235.200.41

set interfaces ethernet eth6 address 192.168.15.128/27
set interfaces ethernet eth6 description LAN4_Gateway
set service dhcp-server shared-network-name LAN4_POOL subnet 192.168.15.128/27 range 0 start 192.168.15.130
set service dhcp-server shared-network-name LAN4_POOL subnet 192.168.15.128/27 range 0 stop 192.168.15.150
set service dhcp-server shared-network-name LAN4_POOL subnet 192.168.15.128/27 default-router 192.168.15.158
set service dhcp-server shared-network-name LAN4_POOL subnet 192.168.15.128/27 lease 120
set service dhcp-server shared-network-name LAN4_POOL subnet 192.168.15.128/27 name-server 132.235.9.75
set service dhcp-server shared-network-name LAN4_POOL subnet 192.168.15.128/27 name-server 132.235.200.41
set protocols static route 0.0.0.0/0 next-hop 192.168.15.162
commit
```
