/*
 *      BIRD -- OSPF
 *
 *      (c) 1999--2004 Ondrej Filip <feela@network.cz>
 *
 *      Can be freely distributed and used under the terms of the GNU GPL.
 *
 */

#ifndef _BIRD_OSPF_PACKET_H_
#define _BIRD_OSPF_PACKET_H_

void ospf_pkt_fill_hdr(struct ospf_iface *ifa, void *buf, u8 h_type);
unsigned ospf_pkt_maxsize(struct ospf_iface *ifa);
int ospf_rx_hook(sock * sk, int size);
void ospf_tx_hook(sock * sk);
void ospf_err_hook(sock * sk, int err);
void ospf_send_to_agt(sock * sk, struct ospf_iface *ifa, u8 state);
void ospf_send_to_bdr(sock * sk, struct ospf_iface *ifa);
void ospf_send_to(sock *sk, ip_addr ip, struct ospf_iface *ifa);


#endif /* _BIRD_OSPF_PACKET_H_ */
