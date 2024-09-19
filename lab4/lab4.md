# Lab4

My Guide for lab 4 with my numbers and IPs

## QUICK-LINKS

[CHEAT-SHEET](https://github.com/OHIO-ECT/Lab-Notebook-Cheat-Sheet)

[LAB-04](https://github.com/OHIO-ECT/ITS-2300-Lab-04-IP-Subnetting)

## Section 1

Instructions for task 1

### In VyOS

```bash
set interfaces ethernet eth0 address 132.235.205.40/25
set interfaces ethernet eth0 description WAN
set protocols static route 0.0.0.0/0 next-hop 132.235.205.126
set system name-server 132.235.9.75
set system name-server 132.235.200.41
commit
```

### Show Route Table

```bash
run show ip route
```

### Ping Google

```bash
ping 8.8.8.8
```

### Ping Gateway

```bash
ping 132.235.205.126
```

### Configure NAT for VyOS

```bash
set nat source rule 100 outbound-interface eth0
set nat source rule 100 source address 10.40.0.0/16
set nat source rule 100 translation address masquerade
commit
```

---

## Section 2

Instructions for task 2

### VyOS Configuration (VPCS)

```bash
configure
set interfaces ethernet eth6 address 10.40.1.1/24 # config eth6
commit
save
exit
```

Now go into VPCS

### VPCS Configuration

set ip -> show ip -> ping

```bash
ip 10.40.1.10/24 10.40.1.1
show ip 
ping 8.8.8.8 
```

## Section 3

### VyOS Configuration (Ubuntu GUI)

```bash
configure
set interfaces ethernet eth7 address 10.40.2.1/24
commit
save
exit
```

Now go into the Ubuntu GUI

### Ubuntu GUI CLI

Go Into Network Settings

Fill in where told in IPV4 Manual mode

| Setting  | Value           |
|----------|-----------------|
| IP       | 10.40.2.10      |
| MASK     | 255.255.255.0   |
| GATEWAY  | 10.40.2.1       |

Time for a Ping / Sanity Check

pinging google

```bash
ping 8.8.8.8
```

or the "RIGHT" way (CLI)  

### Ubuntu CLI

```bash
sudo nmcli general hostname Ubuntu-GUI
sudo nmcli con mod "Wired connection 1" ipv4.addresses 10.40.2.10/24
sudo nmcli con mod "Wired connection 1" ipv4.gateway 10.40.2.1
sudo nmcli con mod "Wired connection 1" ipv4.dns 132.235.9.75
sudo nmcli con mod "Wired connection 1" ipv4.method manual
sudo nmcli connection down "Wired connection 1"
sudo nmcli connection up "Wired connection 1"
```

### VyOS + Ubuntu <--> Routing Table

Commands for:

<i>Vyos</i>

```bash
show ip route
```

&

<i>Ubuntu</i>

```bash
ip route show
```

## Task 4

Make a diagram & fill out a diagram!

### Diagram

### IP Table

| Name                | Interface | IP/Mask           | Gateway        |
|---------------------|-----------|-------------------|----------------|
| WAN                 |           | 132.235.205.40/25 | 132.235.205.126|
| Internal Network    |           | 10.40.0.0/16      |                |
| WAN                 |           |                   |                |
| VyOS-1              | eth0      | 132.235.205.40/25 | 132.235.205.126|
| LAN1                |           |                   |                |
| VyOS-1 (LAN1 Gateway)| eth6      | 10.40.1.1/24      |                |
| PC1 (VPCS)          | e0        | 10.40.1.10/24     | 10.40.1.1      |
| LAN2                |           |                   |                |
| VyOS-1 (LAN2 Gateway)| eth7      | 10.40.2.1/24      |                |
| Ubuntu-GUI-1        | e0        | 10.40.2.10/24     | 10.40.2.1      |
