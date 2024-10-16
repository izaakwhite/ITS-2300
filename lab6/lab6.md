# Lab 6

NAT & NMAP LAB

## My Network

![Uhm Whatttt](image.png)

## IP Grid - Task 1

| Name           | Interface     | Address/Mask     |
|----------------|---------------|------------------|
|WAN Network     | eth0          | 132.235.205.0/25 |
|LAN1 Network    | eth6          | 172.19.2.0/24    |
|LAN2 Network    | eth7          | 172.19.0.0/23    |
|                |               |                  |
|**WAN**         |               |                  |
|VyOS-1          | eth0          |132.235.205.3/25  |
|(WAN Gateway)   |               |132.235.205.126   |
|                |               |                  |
|**LAN1 Network**|               |                  |
|DHCP Pool Start |               |172.19.2.10       |
|DHCP Pool Stop        |         |172.19.2.160      |
|VyOS-1 (LAN1 Gateway) |eth6     |172.19.2.254      |
||||
|**LAN2 Network**      |||
|DHCP Pool Start       ||172.19.0.10|
|DHCP Pool Stop        ||172.19.1.55|
|VyOS-2 (LAN2 Gateway) |eth7|172.19.1.254|

## Task 2  - Recipe

```bash
config
set interfaces ethernet eth0 address 132.235.205.3/25
set interfaces ethernet eth0 description WAN
set protocols static route 0.0.0.0/0 next-hop 132.235.205.126
set system name-server 132.235.9.75
set system name-server 132.235.200.41
set nat source rule 100 outbound-interface eth0
set nat source rule 100 source address 172.19.0.0/16
set nat source rule 100 translation address masquerade
set interfaces ethernet eth6 address 172.19.2.254/24
set interfaces ethernet eth6 description LAN1
set interfaces ethernet eth7 address 172.19.1.254/23
set interfaces ethernet eth7 description LAN2
set service dhcp-server shared-network-name LAN1_POOL subnet 172.19.2.0/24 range 0 start 172.19.2.10
set service dhcp-server shared-network-name LAN1_POOL subnet 172.19.2.0/24 range 0 stop 172.19.2.160
set service dhcp-server shared-network-name LAN1_POOL subnet 172.19.2.0/24 default-router 172.19.2.254
set service dhcp-server shared-network-name LAN1_POOL subnet 172.19.2.0/24 lease 120
set service dhcp-server shared-network-name LAN1_POOL subnet 172.19.2.0/24 name-server 132.235.9.75
set service dhcp-server shared-network-name LAN1_POOL subnet 172.19.2.0/24 name-server 132.235.200.41
set service dhcp-server shared-network-name LAN2_POOL subnet 172.19.0.0/23 range 0 start 172.19.0.10
set service dhcp-server shared-network-name LAN2_POOL subnet 172.19.0.0/23 range 0 stop 172.19.1.55
set service dhcp-server shared-network-name LAN2_POOL subnet 172.19.0.0/23 default-router 172.19.1.254
set service dhcp-server shared-network-name LAN2_POOL subnet 172.19.0.0/23 lease 120
set service dhcp-server shared-network-name LAN2_POOL subnet 172.19.0.0/23 name-server 132.235.9.75
set service dhcp-server shared-network-name LAN2_POOL subnet 172.19.0.0/23 name-server 132.235.200.41
commit
```
