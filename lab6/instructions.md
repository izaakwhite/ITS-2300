# NAT and NMap

## Goals
- Configure NAT on VyOS
- Using NMap perform network discovery

## Resources
- Configuration examples from previous labs

# Task 1 - Design

### Lab Network Conventions (aka Local Best Practices)
These conventions MUST be used for IP address assignment. These conventions will be in effect for all assignments for the entire semester.
- A. Default Gateway (Router) will use the last usable address in the IP Network
- B. All other static assigned IPs (including other routers that are not the default gateway) start at the beginning of the range
- C. DHCP pools between the statically addressed clients and the Default Gateway
- D. Unless stated otherwise use the following DNS Name servers: 132.235.9.75, 132.235.200.41

**HINT:** Think about the "goto" subnet sizes talked about in lecture. Don't over complicate the process.

 1. Complete the following IP grid, with the following policy.
    - Access https://www.its.ohio.edu/randonet and generate a **SINGLE (as in ONE)** random **PRIVATE** network number
    - Use a /16 mask for the random network
    - Use that network for interior networks
    - Split the network provided into at least two networks
    - LAN1 100 Hosts + 50 additional (for growth)
    - LAN2 250 Hosts + 50 additional (for growth)
    - Follow all other course conventions for Gateway selection and DHCP Pool locations listed above.
    - **HINT:** Think about the "goto" subnet sizes talked about in lecture. Don't over complicate the process.

| Name           | Interface     | Address/Mask     |
|----------------|---------------|------------------|
|WAN Network     |               | 132.235.205.0/25 |
|LAN1 Network    ||
|LAN2 Network    ||
||
|**WAN**
|VyOS-1          |eth0           |132.235.205.**X**/25
|(WAN Gateway)         |         |132.235.205.**Y**
||
|**LAN1 Network**      ||
|DHCP Pool Start       ||
|DHCP Pool Stop        ||
|VyOS-1 (LAN1 Gateway) |eth6|
||
|**LAN2 Network**      ||
|DHCP Pool Start       ||
|DHCP Pool Stop        ||
|VyOS-2 (LAN2 Gateway) |eth7|

## Network Diagram and Recipe

![](./images/nat-network-diag1.png)

2. Using previous recipes **as a template**, create a **new** recipe with using information from IP Grid and Network Diagram the addresses selected above that configures VyOS NICs, default route, and DHCP pools.

# Task 2 - Deploy the Network

3. Open GNS3 and start a new project, name it: ``ITS-2300-Lab-NAT-NMAP``. Create the network shown in the Network Diagram.

4. Apply the VyOS recipe developed in the pre-lab.

5. Start VPCSs (if not already running).

6. Using skills and commands learned from previous lab confirm both VPCS obtain a DHCP IPs.

7. From the both VPCS Console run the following commands:

    a. See stats about the IP just obtained using `show ip`
    
    b. Ping the local gateway using `ping <LAN_GATEWAY_IP>`

### Pre-Lab Deliverable
- IP Grid
- Recipe

```diff
@@ Students should **at least** be to this point by their Thursday lab session @@
```
![](./images/Pre-Lab-Deliverable.png)

# Task 3 - Network Address Translation

8. Start a packet capture on the connection between VyOS and the WAN cloud.

9. Ping a reliable IP address from PC-1. (The ping will fail, but you will see traffic in the packet capture).

10. Filter for `icmp` and save packets with "Export Specified Packets" for later processing.

11. Stop packet capture. Using the following template to configure NAT on the VyOS router.

```
set nat source rule 100 outbound-interface <OUTBOUND_ETH_INTERFACE>
set nat source rule 100 source address <RANDONET_NETWORK>/<RANDONET_MASK>
set nat source rule 100 translation address masquerade
```
**Note:** IP address and mask used must encompass BOTH subnets.

12. Start two packet captures between:
    - a. VyOS-1 and WAN Cloud<br>
    - b. VyOS-1 and PC-1<br>

13. Ping a reliable IP address on PC-1.

14. Filter for `icmp` and save packets with "Export Specified Packets" on each packet capture for later processing.

# Task 4 - Network Update!

15. Update your project to reflect the network diagram shown below. The addition of the gHost will not appear in GNS3, but you will need to add it to your diagram. gHost will act as a web browser for the NAT forwarding task.

    ![](./images/nat-network-diag2.png)

16. Start Win-Desktop-1 and Ubuntu-CLI-1 and make sure they get DHCP IPs.

# Task 5 - NAT Forwarding

17. In VyOS-1 configure NAT forwarding for HTTP (port 80) to Ubuntu-CLI-1:
```
set nat destination rule 10 description 'Port Forward: Public HTTP (8080) to Ubuntu-CLI-1 HTTP (80)'
set nat destination rule 10 destination port 8080
set nat destination rule 10 inbound-interface eth0
set nat destination rule 10 protocol tcp
set nat destination rule 10 translation address <Ubuntu-CLI-1-IP>
set nat destination rule 10 translation port 80
```

18. From you gHost Firefox browser go to http://132.235.205.X:8080 Verify you get the default Apache page. 

    **Note:** X is the VyOS-1 WAN IP address

19. From on VyOS-1 on a NON-config prompt use the command:
    `show nat destination rule` 

20. On Ubuntu-CLI-1 start a ``ping 8.8.8.8`` and let it run. Then go to VyOS in a NON-config prompt. Use the following commands to see NAT statistics:<br>
    `show nat source rules` <br>
    `show nat destination rules` <br>
    `show nat source statistics` <br>
    `show nat destination statistics`<br>
    `show nat source translations detail` <br>
    `show nat destination translations detail`

21. Stop Ubuntu-CLI-1 ping.

# Task 6 - Nmap and Zenmap

22. In Win-Desktop-1 find and start ``Zenmap``.

23. In Zenmap under `Target:` input your LAN2 network number (check your IP Grid). Under `Profile:` set to `Quick scan`. Press `Scan` button. **Note: This will take a few minutes to complete.**

24. Using Zenmap ping scan the network `10.101.8.0/27`.

25. Using Zenmap quick scan `mesp.ohio.edu`.

26. Copy/Paste all of the output from mesp.ohio.edu scan in the `Nmap Output` pane into a text file for use in your lab report. 
**Hint:** For Zenmap collecting results Ctrl+A is your friend!

# Task 7 - Documentation and Deliverables

27. Create a table/chart (in Excel or Google Sheets) similar to the chart below. Expand the IP Grid to show the addresses used for each of the devices during the lab.

|Name |Interface| Address/Mask|
|---  |--- |--------|
|WAN Network ||132.235.205.0/25
|LAN1 Network ||
|LAN2 Network ||
||
|**WAN**
|VyOS-1|eth0|132.235.205.**X**/25
|(WAN Gateway) ||
||
|**LAN1 Network**
|DHCP Pool Start ||
|VPCS|e0||
|Ubuntu-CLI-1|||
|DHCP Pool Stop ||
|VyOS-1 (LAN1 Gateway) |eth6|
||
|**LAN2 Network**
|DHCP Pool Start ||
|VPCS|e0||
|Win-Desktop-1|||
|DHCP Pool Stop ||
|VyOS-2 (LAN2 Gateway) |eth7|
||
|gHost IP|||

28. Using information from Draw.IO from lecture/lab/YouTube, develop a network diagram of this project in Draw.io. It will include:
    - Use shapes from ITS scratchpad
    - Turn in as a PNG file
    - Please interface names on the diagram in the appropriate places
    - Place IPv4 IPs on the diagram for all objects with appropriate interface name
    - Add colored background to denote networks and add network numbers with mask to the colored squares
    - Inside colored network boxes denote DHCP range(s) used

### Student Deliverable
29. Complete appropriate lab assignment on Blackboard.