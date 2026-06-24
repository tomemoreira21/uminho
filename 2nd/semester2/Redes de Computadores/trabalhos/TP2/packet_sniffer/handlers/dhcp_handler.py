from scapy.layers.dhcp import BOOTP

#DHCP

#Hash table xid -> mensagens DHCP da transação xid
dhcp_transactions = {}

#lista de dhcp_info
dhcp_infos = []

def handle_dhcp(packet, info):
    dhcp = packet[BOOTP]
    key = dhcp.xid

    if key not in dhcp_transactions:
        dhcp_transactions[key] = []

    dhcp_transactions[key].append(info)

def process_transactions():
    for xid, packets in dhcp_transactions.items():

        # ordenar por tempo
        packets.sort(key=lambda p: p.timestamp)

        base_time = None

        info = {
            "xid": xid,
            "discover": None,
            "offer": None,
            "request": None,
            "ack": None,
            "has_discover": False,
            "has_offer": False,
            "has_request": False,
            "has_ack": False,
            "total_time": None
        }

        has_discover = False

        for p in packets:
            t = p.timestamp

            if p.summary == "DHCP discover":
                base_time = t
                has_discover = True
                info["discover"] = 0
                info["has_discover"] = True

            elif p.summary == "DHCP offer" and base_time is not None:
                info["offer"] = (t - base_time) * 1000
                info["has_offer"] = True

            elif p.summary == "DHCP request" and base_time:
                if not has_discover:
                    base_time = t
                info["request"] = (t - base_time) * 1000
                info["has_request"] = True

            elif p.summary == "DHCP ack" and base_time:
                info["ack"] = (t - base_time) * 1000
                info["has_ack"] = True
                info["total_time"] = (t - base_time) * 1000

        dhcp_infos.append(info)

    return dhcp_infos

def print_dhcp_flows():
    print("\n=== DHCP Flows (per XID) ===\n")

    for xid, packets in dhcp_transactions.items():
        print(f"DHCP Transaction XID: {xid}")

        # ordenar por tempo
        packets_sorted = sorted(packets, key=lambda p: p.timestamp)

        if not packets_sorted:
            continue

        base_time = packets_sorted[0].timestamp

        for p in packets_sorted:
            rel_time = (p.timestamp - base_time) * 1000  # ms

            print(f"[{rel_time:8.2f} ms] "
                  f"{p.summary:<15} | "
                  f"{p.src_ip} → {p.dst_ip} | "
                  f"{p.src_mac} → {p.dst_mac}")

        print("-" * 70)

def get_dhcp_message_type(options):
    for opt in options:
        if opt[0] == 'message-type':
            return opt[1]
    return None