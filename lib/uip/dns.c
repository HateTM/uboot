/*  Copyright(c) 2009-2018 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		dns.c
 * brief	dns源文件主要实现解析dns数据包，然后构造dns回复报文
 *			更改IP为我们让用户要访问的IP地址。
 * details	
 *
 * author	Feng Biao
 * version	
 * date		24Oct18
 *
 * history 	\arg	
 */
#include "dns.h"

extern struct in_addr net_ip;

/**************************************************************************************************/
/*                                           DEFINES                                              */
/**************************************************************************************************/

/**************************************************************************************************/
/*                                           LOCAL_FUNCTIONS                                      */
/**************************************************************************************************/
/* 
 * fn		void dump(u8_t *head, int len)
 * brief	dump函数主要用来打印我们回复报文的每个字节
 *			的值，然后与wireshark抓取的数据包进行比较
 *			以便分析我们发送的数据与抓取的包是否一致。
 * details	
 *
 * param[in]	u8_t *head, int len
 * param[out]	字节信息
 *
 * return	void
 * retval	
 *
 * note		
 */
void dump(u8_t *head, int len)
{
	int i = 0;
	for(; i < len; i++){
		if(i % 16 == 0){
			printf("\n");
		}
		printf("%02x ", *head++);
	}
}


/* 
 * fn		static int getDNSReqLen(char* DNSReqData)
 * brief	得到dns包question偏移的长度，这个长度是可变的
 * details	
 *
 * param[in]	char* DNSReqData
 * param[out]	
 *
 * return	int
 * retval	
 *
 * note		
 */
int getDNSReqLen(char* DNSReqData)
{
	int len;
	len = 0;
	while(*DNSReqData)
	{
		len += (unsigned char)(*DNSReqData) + 1;
		DNSReqData += (unsigned char)(*DNSReqData) + 1;
		if(len > 512)
		{
			return -1;
		}
	}
	len ++;    //last 0x00
	len += 4;  //req type && req class;
	return len;
}


/* 
 * fn		void dns_init(void)
 * brief	dns初始化函数，主要用于与dns知名端口53建立
 *			绑定连接，以便处理dns请求包
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
void dns_init(void)
{
	uip_ipaddr_t addr;
	struct uip_udp_conn *conn;

	uip_ipaddr(addr, 255, 255, 255, 255);
	conn = uip_udp_new(&addr, HTONS(53));
	if(conn != NULL) {
		uip_udp_bind(conn, HTONS(53));
	}
}


/* 
 * fn		void create_dns_msg(void)
 * brief	首先解析dns报文，得到dns头部的数据，然后更改
 *			dns头部的flagg字段和回答数，然后在dns消息头和
 *			查询问题偏移后加入dnsans消息，然后发送数据包
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
void create_dns_msg(void)
{
	DNSANS dnsans;
	char *pDNSReqData = NULL;
	int DNSReqLen = 0;
	
	DNSHDR *dnshdr = (DNSHDR *)uip_appdata;

	/* 构造固定的DNS回复报文 */
	dnshdr->flags = htons(0x8580);
	dnshdr->answerRRs = htons(0x0001);
	
	pDNSReqData = (char *)((char *)dnshdr + sizeof(DNSHDR));
	DNSReqLen = getDNSReqLen(pDNSReqData);
	
	if(DNSReqLen < 0){
		printf("\ndns pkt error\n");
	} 

	dnsans.name = htons(0xc00c);
	dnsans._type = htons(0x0001);
	dnsans._class = htons(0x0001);
	dnsans.ttl = 0;
	dnsans.len = htons(0x0004);
	dnsans.ipaddr = net_ip.s_addr;//htonl(NetOurIP); //192.168.0.2
	memcpy((u8_t *)uip_appdata + sizeof(DNSHDR) + DNSReqLen, (u8_t *)&dnsans, sizeof(DNSANS));
	dump((u8_t *)uip_appdata + sizeof(DNSHDR) + DNSReqLen, sizeof(DNSANS));
	
	uip_send(uip_appdata, sizeof(DNSHDR) + DNSReqLen + sizeof(DNSANS));
}


/* 
 * fn		void handle_dns(void)
 * brief	用于被UIP_UDP_APPCALL函数调用，处理dns数据包
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
void handle_dns(void)
{
	if(uip_newdata()){
		create_dns_msg();
	}
}
