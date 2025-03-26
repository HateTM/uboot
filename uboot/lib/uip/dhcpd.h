/*  Copyright(c) 2009-2018 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		dhcpd.h
 * brief	dhcp头文件，主要定义dhcp选项值，dhcp消息结构体等	
 * details	
 *
 * author	Feng Biao
 * version	
 * date		27Oct18
 *
 * history 	\arg	
 */
#ifndef __DHCPD_H__
#define __DHCPD_H__

#include <linux/string.h>
#include <common.h>
#include <command.h>
#include <net.h>

#include "uip.h"
#include "dns.h"
#include "uip_arp.h"

/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/
typedef unsigned int u32_t;

/* dhcp地址池100——200 */
#ifndef DHCPD_ADDR_START
#define  DHCPD_ADDR_START 100
#endif

#ifndef DHCPD_ADDR_END 
#define  DHCPD_ADDR_END 200
#endif

#define DHCPD_CHADDR_LEN 16U

//链表长度
#define LIST_LEN 128

/*
 * 请求，应答，硬件类型、长度
 */
//#define DHCP_REQUEST        1
#define DHCP_REPLY          2
#define DHCP_HTYPE_ETHERNET 1
#define DHCP_HLEN_ETHERNET  6
#define DHCP_MSG_LEN      236

#define DHCPC_SERVER_PORT  67
#define DHCPC_CLIENT_PORT  68

/*
 * DHCP消息类型
 */
#define DHCPDISCOVER  1
#define DHCPOFFER     2
#define DHCPREQUEST   3
#define DHCPDECLINE   4
#define DHCPACK       5
#define DHCPNAK       6
#define DHCPRELEASE   7

/* 选项option */
#define DHCP_OPTION_SUBNET_MASK   1
#define DHCP_OPTION_ROUTER        3
#define DHCP_OPTION_DNS_SERVER    6
#define DHCP_OPTION_DOMAIN_NAME  15
#define DHCP_OPTION_REQ_IPADDR   50
#define DHCP_OPTION_LEASE_TIME   51
#define DHCP_OPTION_MSG_TYPE     53
#define DHCP_OPTION_SERVER_ID    54
#define DHCP_OPTION_REQ_LIST     55
#define DHCP_OPTION_END         255
#define DHCP_OPTION_OVER		0x34

//32位IP
struct ip_addr {
  u32_t addr;
};

/* dhcp client结构，存放IP+MAC */
struct dhcp_client{
 	u8_t hwaddr[DHCPD_CHADDR_LEN];
 	struct ip_addr ipaddr;
    struct dhcp_client *next;
};

/* dhcp state结构 */
struct dhcpd_state {
  	char state;
  	struct uip_udp_conn *conn;
  	u16_t ticks;
  	u8_t mac_addr[16];
  	int mac_len;
  	u32_t xid;
  	u8_t serverid[4];
  	u16_t lease_time[2];
  	u16_t ipaddr[4];
  	u16_t netmask[4];
  	u16_t dnsaddr[4];
  	u16_t default_router[4];
};

/* dhcp消息结构 */
struct dhcpd_msg {
  u8_t op, htype, hlen, hops;
  u8_t xid[4];
  u16_t secs;
  u16_t flags;
  u8_t ciaddr[4];
  u8_t yiaddr[4];
  u8_t siaddr[4];
  u8_t giaddr[4];
  u8_t chaddr[16];
  u8_t sname[64];
  u8_t file[128];
  u8_t options[312];
};


/**************************************************************************************************/
/*                                           FUNCTIONS                                            */
/**************************************************************************************************/
/* 
 * fn		int dhcpd_init(void)
 * brief	dhcpd初始化函数，主要建立与dhcp报文的67
 *			和68端口的udp连接
 * details	
 *
 * param[in]	void
 * param[out]	
 *
 * return	int
 * retval	
 *
 * note		
 */
int dhcpd_init(void);

/* 
 * fn		u32_t allocate_new_ipaddr(NODE *head)
 * brief	给客户端分配IP地址
 * details	
 *
 * param[in]
 * param[out]	
 *
 * return	u32_t地址
 * retval	
 *
 * note		
 */
u32_t allocate_new_ipaddr(void);

/* 
 * fn		int dhcpd_arp_check(NODE* head)
 * brief	对分配的IP地址发送ARP请求，看是否地址冲突
 * details	
 *
 * param[in]	u32_t addr
 * param[out]	
 *
 * return	int
 * retval	
 *
 * note		
 */
int dhcpd_arp_check(u32_t addr);

//UIP_UDP_APPCALL函数
#define UIP_UDP_APPCALL udp_appcall

#endif
