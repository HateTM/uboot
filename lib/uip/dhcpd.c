/*  Copyright(c) 2009-2018 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		dhcpd.c
 * brief	该文件主要用于实现处理用户PC发来的DHCPDiscover报文和
 *			DHCPRequest报文，然后回复DHCPOffer报文和DHCPAck报文，
 *			从而达到给用户分配IP的目的，本文件还实现了填充dhcp选项值
 *			的各个函数以及分配IP的函数以及UIP_UDP_APPCALL函数的实现
 * details	
 *
 * author	Feng Biao
 * version	
 * date		27Oct18
 *
 * history 	\arg	
 */

#include "dhcpd.h"
#include <malloc.h>

/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/
struct dhcp_client *head_dhcpd;
typedef struct dhcp_client NODE;

static struct dhcpd_state s;

static int ipindex = 1;

//分配的IP地址，在dhcpd.c和uip_arp.c中检查地址冲突
u32_t allocate_addr;

/*
 * server,dns,netmask,leasetime
 */
extern struct in_addr net_ip;
static u32_t uip_server_netmask = (255<<24)|(255<<16)|(255<<8)|(0);
static u32_t uip_dhcp_leasetime = 3600 * 24;	//24h

/* ARP结构 */
struct uip_arp_hdr {
  struct uip_eth_hdr ethhdr;
  u16_t hwtype;
  u16_t protocol;
  u8_t hwlen;
  u8_t protolen;
  u16_t opcode;
  struct uip_eth_addr shwaddr;
  u16_t sipaddr[2];
  struct uip_eth_addr dhwaddr;
  u16_t dipaddr[2]; 
};

//发ARP包
extern uchar *net_tx_packet;

//发送ARP报文数组
u8_t arp_uip_buf[UIP_BUFSIZE+2];

//指向ARP报文开始位置
#define ARPBUF ((struct uip_arp_hdr *)&arp_uip_buf[0])

//源MAC
static const struct uip_eth_addr arp_src_ethaddr =
  {{0x00,0x00,0x00,0x00,0x00,0x00}};

//目的MAC
static const struct uip_eth_addr arp_dest_ethaddr =
  {{0x00,0x00,0x00,0x00,0x00,0x00}};

//广播MAC
static const struct uip_eth_addr arp_broadcast_ethaddr =
  {{0xff,0xff,0xff,0xff,0xff,0xff}};


/**************************************************************************************************/
/*                                           LOCAL_FUNCTIONS                                      */
/**************************************************************************************************/
/* 
 * fn		static u8_t * add_msg_type(u8_t *optptr, u8_t type)
 * brief	dhcp回复报文中添加消息类型，53代表dhcp消息类型
 * details	
 *
 * param[in]	u8_t *optptr, u8_t type
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_msg_type(u8_t *optptr, u8_t type)
{
	*optptr++ = DHCP_OPTION_MSG_TYPE;
	*optptr++ = 1;
	*optptr++ = type;
	return optptr;
}


/* 
 * fn		static u8_t * add_dhcpd_server_id(u8_t *optptr)
 * brief	在dhcp回复报文中添加服务器标识符，同时设置服务器IP
 *			为net_ip（192.168.0.2）
 * details	
 *
 * param[in]	u8_t *optptr
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_dhcpd_server_id(u8_t *optptr)
{
	u32_t server_id;
	*optptr++ = DHCP_OPTION_SERVER_ID;
	*optptr++ = 4;
	server_id = net_ip.s_addr;
	memcpy(optptr, &server_id, 4);
	return optptr + 4;
}


/* 
 * fn		static u8_t * add_dhcpd_default_router(u8_t *optptr)
 * brief	在dhcp回复报文中添加路由地址为net_ip（192.168.0.2）
 * details	
 *
 * param[in]	u8_t *optptr
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_dhcpd_default_router(u8_t *optptr)
{
	u32_t default_router;
	*optptr++ = DHCP_OPTION_ROUTER;
	*optptr++ = 4;
	default_router = net_ip.s_addr;
	memcpy(optptr, &default_router, 4);
	return optptr + 4;
}


/* 
 * fn		static u8_t * add_dhcpd_dns_server(u8_t *optptr)
 * brief	在dhcp回复报文中添加域名服务器，dns服务器的IP设置
 *			为net_ip（192.168.0.2）
 * details	
 *
 * param[in]	u8_t *optptr
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_dhcpd_dns_server(u8_t *optptr)
{
	u32_t dns;
	*optptr++ = DHCP_OPTION_DNS_SERVER;
	*optptr++ = 4;
	dns = net_ip.s_addr;
	memcpy(optptr, &dns, 4);
	return optptr + 4;
}


/* 
 * fn		static u8_t * add_dhcpd_lease_time(u8_t *optptr)
 * brief	在dhcp回复报文中添加租约时间，本次设为24h
 * details	
 *
 * param[in]	u8_t *optptr
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_dhcpd_lease_time(u8_t *optptr)
{
	u32_t leasetime;

	*optptr++ = DHCP_OPTION_LEASE_TIME;
	*optptr++ = 4;
	leasetime = uip_dhcp_leasetime;
	optptr = memcpy(optptr, &leasetime, 4);
	
	return optptr + 4;
}


/* 
 * fn		static u8_t * add_dhcpd_subnet_mask(u8_t *optptr)
 * brief	在dhcp回复报文中设置子网掩码选项，子网掩码设置为
 *			255.255.255.0，选项值为1
 * details	
 *
 * param[in]	u8_t *optptr
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_dhcpd_subnet_mask(u8_t *optptr)
{
	u32_t subnet_mask;
	*optptr++ = DHCP_OPTION_SUBNET_MASK;
	*optptr++ = 4;
	subnet_mask = ntohl(uip_server_netmask);
	memcpy(optptr, &subnet_mask, 4);
	return optptr + 4;
}


/* 
 * fn		static u8_t * add_end(u8_t *optptr)
 * brief	在dhcp回复报文中设置结束选项，选项值
 *			为255
 * details	
 *
 * param[in]	u8_t *optptr
 * param[out]	
 *
 * return	u8_t *
 * retval	
 *
 * note		
 */
static u8_t *
add_end(u8_t *optptr)
{
	*optptr++ = DHCP_OPTION_END;
	return optptr;
}

/* 
 * fn		static int list_add(NODE *node, int ipaddr, u8_t *hw_addr)  
 * brief	将dhcp offer分配的IP加入链表中
 * details	
 *
 * param[in]	NODE *node, int ipaddr, u8_t *hw_addr
 * param[out]	
 *
 * return	int
 * retval	
 *
 * note		
 */
static int dhcp_list_add(NODE *node, int ipaddr, u8_t *hw_addr){
	NODE *phead = node;
	
	u8_t array[16] = {0};
	while(phead->next && (strcmp(phead->next->hwaddr, array))){
		phead = phead->next;
	}
	if(phead->next){
		phead->next->ipaddr.addr = ipaddr;
		memcpy(phead->next->hwaddr, hw_addr, DHCPD_CHADDR_LEN);
	}
	else{
		printf("list full\n");
		return -1;
	}

	return 0;
}


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
u32_t allocate_new_ipaddr()
{
	u32_t ipaddr;
	if((ipindex < 0) || ((ipindex + DHCPD_ADDR_START) > DHCPD_ADDR_END)){
		printf("allocate ip failed.\n");
		return 0;
	}
	/*net_ip is bigendian, fix it*/
	//ipaddr = net_ip.s_addr & 0xffffff00;
	ipaddr = net_ip.s_addr & 0x00ffffff;
	ipaddr += ((ipindex + DHCPD_ADDR_START) << 24);
	ipindex++;
	return ipaddr;
}


/* 
 * fn		static u8_t parse_dhcp_options(u8_t *optptr, int len)
 * brief	解析dhcp选项类型
 * details	
 *
 * param[in]	u8_t *optptr, int len
 * param[out]	
 *
 * return	u8_t
 * retval	
 *
 * note		
 */
static u8_t
parse_dhcp_options(u8_t *optptr, int len)
{
	u8_t *end = optptr + len;
	u8_t type = 0;

	while(optptr < end) {
		switch(*optptr) {
			case DHCP_OPTION_SUBNET_MASK:
				memcpy(s.netmask, optptr + 2, 4);
				break;
			case DHCP_OPTION_ROUTER:
				memcpy(s.default_router, optptr + 2, 4);
				break;
			case DHCP_OPTION_DNS_SERVER:
				memcpy(s.dnsaddr, optptr + 2, 4);
				break;
			case DHCP_OPTION_MSG_TYPE:
				type = *(optptr + 2);
				break;
			case DHCP_OPTION_SERVER_ID:
				memcpy(s.serverid, optptr + 2, 4);
				break;
			case DHCP_OPTION_LEASE_TIME:
				memcpy(s.lease_time, optptr + 2, 4);
				break;
			case DHCP_OPTION_REQ_IPADDR:
				memcpy(s.ipaddr, optptr + 2, 4);
				break;
			case DHCP_OPTION_END:
				return type;
		}
		optptr += optptr[1] + 2;
	}
	return type;
}


/* 
 * fn		static u8_t parse_dhcp_msg(void)
 * brief	解析dhcp消息，如果是dhcp请求则根据
 *			选项的值判断是discover还是request报文
 * details	
 *
 * param[in]	
 * param[out]	
 *
 * return	u8_t
 * retval	
 *
 * note		
 */
static u8_t
parse_dhcp_msg(void)
{
	struct dhcpd_msg *m = (struct dhcpd_msg *)uip_appdata;
	//判断是否是DHCP请求
	if(m->op == 1){//DHCP_REQUEST) {
		return parse_dhcp_options(&m->options[4], uip_datalen());
	}
	return 0;
}


/* 
 * fn		int dhcpd_arp_check(NODE* head)
 * brief	对分配的IP地址发送ARP请求
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
int dhcpd_arp_check(u32_t addr)
{
	uip_ipaddr_t ipaddr;
	volatile uchar *arptmpbuf = net_tx_packet;
	int i;

	//源地址0.0.0.0
	uip_ipaddr(ipaddr, 0, 0, 0, 0);

	//发送ARP请求
	memcpy(ARPBUF->ethhdr.dest.addr, arp_broadcast_ethaddr.addr, 6);
	memcpy(ARPBUF->ethhdr.src.addr, arp_src_ethaddr.addr, 6);
	ARPBUF->ethhdr.type = htons(UIP_ETHTYPE_ARP);

	ARPBUF->hwtype = htons(0x0001);
	ARPBUF->protocol = htons(0x0800);
	ARPBUF->hwlen = 0x6;//htons(0x0006);
	ARPBUF->protolen = 0x4;//htons(0x0004);
	ARPBUF->opcode = htons(0x0001);

	memcpy(ARPBUF->shwaddr.addr, arp_src_ethaddr.addr, 6);
	memcpy(ARPBUF->sipaddr, &ipaddr, 4);
	memcpy(ARPBUF->dhwaddr.addr, arp_dest_ethaddr.addr, 6);
	memcpy(ARPBUF->dipaddr, &addr, 4);
	
	uip_len = sizeof(struct uip_arp_hdr);
	
	for(i = 0; i < uip_len; i++){
		arptmpbuf[i] = arp_uip_buf[i];
	}
	
	dump(arp_uip_buf, uip_len);

	//发送ARP请求，检查IP是否冲突
	eth_send(net_tx_packet, uip_len);
	return 1;
}


/* 
 * fn		static int dhcpd_relay_offer(NODE* head)
 * brief	解析dhcp消息，遍历链表得到IP地址，然后
 *			填充选项信息，通过uip_send函数填充uip中
 *			uip_sappdata和uip_slen回复dhcp offer报文
 * details	
 *
 * param[in]	dhcp_client *
 * param[out]	
 *
 * return	int
 * retval	
 *
 * note		
 */
static int dhcpd_reply_offer(NODE* head)
{
	u8_t *end;
    u32_t addr;
	NODE *p;
	p = head;

	//解析dhcp报文
	struct dhcpd_msg *m = (struct dhcpd_msg *)uip_appdata;
	
	//根据MAC判断是否分配过IP
 	while((p->next) && (strcmp(p->next->hwaddr, m->chaddr)))
		p = p->next;
	
	if(p->next){
		addr = p->next->ipaddr.addr;
		printf("offer used ipaddr: %d.%d.%d.%d\n",
		(p->next->ipaddr.addr&0xff000000)>>24, (p->next->ipaddr.addr&0x00ff0000)>>16,
		(p->next->ipaddr.addr&0x0000ff00)>>8, p->next->ipaddr.addr&0x000000ff);
	}else{
		printf("can't find ip by MAC\n");
		return -1;
	}

	m->op = DHCP_REPLY;
	memcpy(m->yiaddr, &addr, sizeof(m->yiaddr));//设置IP地址

	end = add_msg_type(&m->options[4], DHCPOFFER);
	end = add_dhcpd_server_id(end);
	end = add_dhcpd_default_router(end);
    end = add_dhcpd_dns_server(end);
	end = add_dhcpd_lease_time(end);
	end = add_dhcpd_subnet_mask(end);
	end = add_end(end);
	
	uip_send(uip_appdata, end - (u8_t *)uip_appdata);
	
	return 1;
}


/* 
 * fn		static int dhcpd_replay_ask(NODE* head)
 * brief	根据dhcp request报文，填充dhcp ack报文
 * details	
 *
 * param[in]	NODE* head
 * param[out]	
 *
 * return	int
 * retval	
 *
 * note		
 */
static int dhcpd_reply_ack(NODE* head)
{
	u8_t *end;
    u32_t addr;
	int ack = 1;
	NODE *p;
	p = head;

	struct uip_udp_conn *udp_conn = uip_udp_conn;

	//解析dhcp报文
	struct dhcpd_msg *m = (struct dhcpd_msg *)uip_appdata;
	
	//根据MAC匹配Offer阶段分配的IP
 	while((p->next) && (strcmp(p->next->hwaddr, m->chaddr)))
     	p = p->next;
	
	if(p->next){
		printf("Find available ipaddr from list\n");
		addr = p->next->ipaddr.addr;
		/*
		 * 续租功能，如果收到的request报文中ciaddr有值，说明
		 * 是续租发来的request报文，这时候应该回复单播包。
		 */
		if(uip_ipaddr_cmp(m->ciaddr, &addr)){
			memcpy(udp_conn->ripaddr, &addr, 4);
		}
		
		ack = 1;
	}
	else{
		ack = 0;
	}
	
	m->op = DHCP_REPLY;
	if(ack){
		printf("dhcpd set client ipaddr: %d.%d.%d.%d\n",
			(addr&0xff000000)>>24, (addr&0x00ff0000)>>16, 
			(addr&0x0000ff00)>>8, addr&0x000000ff);
		memcpy(m->yiaddr, &addr, sizeof(m->yiaddr));//设置IP地址
		end = add_msg_type(&m->options[4], DHCPACK);
		end = add_dhcpd_server_id(end);
		end = add_dhcpd_default_router(end);
		end = add_dhcpd_dns_server(end);
		end = add_dhcpd_lease_time(end);
		end = add_dhcpd_subnet_mask(end);
	}
	else{
		end = add_msg_type(&m->options[4], DHCPNAK);
	  	end = add_dhcpd_server_id(end);
	}
	end = add_end(end);
	uip_send(uip_appdata, end - (u8_t *)uip_appdata);

	return 1;
}


/* 
 * fn		void  handle_dhcpd(void)
 * brief	UIP_UDP_APPCALL回调函数调用处理dhcp报文
 *			如果有新数据，则判断是discover报文还是
 *			request报文分别回复offer报文和ack报文
 * details	
 *
 * param[in]	void
 * param[out]	
 *
 * return	void
 * retval	
 *
 * note		
 */
void 
handle_dhcpd(void)
{
	unsigned char state;

	//标志，新客户端第一次和第二次发来discover报文
	static int dhcp_flag = 0;

	int ret;
	
	NODE *p = head_dhcpd;
	if(uip_newdata()){
		state = parse_dhcp_msg();
		
		if(state == DHCPDISCOVER){
			/*
			 * 对收到的第一个dhcp discover报文，先分配IP
			 * 然后将分配的IP发送ARP探测是否冲突，如果没有
			 * 则存入链表，再对第二个discover则回复offer
			 */
			 
			 //解析消息
			struct dhcpd_msg *m = (struct dhcpd_msg *)uip_appdata;

			/*
			 * 对到达的第二个discover报文，将新地址和mac绑定存入链表
			 * 回复offer报文，这时候ip不会冲突
			 */
			if(dhcp_flag == 1){
				ret = dhcp_list_add(head_dhcpd, allocate_addr, m->chaddr);
				if(ret == -1){
					return;
				}
				dhcpd_reply_offer(head_dhcpd);
				dhcp_flag = 0;
			}
		
			while((p->next) && (strcmp(p->next->hwaddr, m->chaddr)))
     			p = p->next;
			/*
			 * 如果没有找到，说明是新客户端，则分配地址并发ARP探测IP是否冲突
			 * 如果冲突，则在收到ARP Reply之后再次分配新地址，保证分配的地址不会冲突
			 */
			if(!p->next){
				allocate_addr = allocate_new_ipaddr();
				if(allocate_addr == 0){
					return;
				}
				printf("dhcpd allocate new ipaddr:%d.%d.%d.%d\n",
				(allocate_addr&0xff000000)>>24, (allocate_addr&0x00ff0000)>>16, 
				(allocate_addr&0x0000ff00)>>8, allocate_addr&0x000000ff);

				//ARP Request
				dhcpd_arp_check(allocate_addr);
				dhcp_flag = 1;
			}else{
				dhcpd_reply_offer(head_dhcpd);
				dhcp_flag = 0;
			}
		}
		else if(state == DHCPREQUEST){
			dhcpd_reply_ack(head_dhcpd);
		}
	}
	return;
}


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
int
dhcpd_init(void)
{
	int i;
	//初始化链表
	head_dhcpd = (NODE *)malloc(sizeof(NODE));
	if (head_dhcpd == NULL){
		printf("allocated head_dhcpd failed.\n");
		return -1;
	}
	head_dhcpd->next = NULL;

	NODE *p = head_dhcpd;
	for(i = 0; i < LIST_LEN; i++){
		NODE *node = (NODE *)malloc(sizeof(NODE));
		if(node == NULL){
			return -1;
		}
		memset(node, 0, sizeof(NODE));
		p->next = node;
		p = p->next;
	}

	uip_ipaddr_t addr;
	s.mac_len = DHCP_HLEN_ETHERNET;
	uip_ipaddr(addr, 255, 255, 255, 255);
	s.conn = uip_udp_new(&addr, HTONS(DHCPC_CLIENT_PORT));
	if(s.conn != NULL){
		uip_udp_bind(s.conn, HTONS(DHCPC_SERVER_PORT));
	}

	return 1;
}

/**************************************************************************************************/
/*                                           PUBLIC_FUNCTIONS                                     */
/**************************************************************************************************/
/* 
 * fn		void udp_appcall(void)
 * brief	UIP_UDP_APPDATA函数的具体实现，它是UIP协议栈中
 *			处理所有udp数据包的入口，本次模块主要处理dhcp
 *			报文和dns报文
 * details	
 *
 * param[in]	void
 * param[out]	
 *
 * return	void
 * retval	
 *
 * note		
 */
void udp_appcall(void)
{
	struct uip_udp_conn *udp_conn = uip_udp_conn;
	u16_t lport;

	/*lport is already in network byte order, see udp_bind*/
	lport = udp_conn->lport;//HTONS(udp_conn->lport);

	if (htons(DHCPC_SERVER_PORT) == lport){
		handle_dhcpd();
	}
	if(htons(53) == lport){
		handle_dns();
	}
	return;
}
