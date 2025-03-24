/*  Copyright(c) 2009-2018 Shenzhen TP-LINK Technologies Co.Ltd.
 *
 * file		dns.h
 * brief		
 * details	
 *
 * author	Feng Biao
 * version	
 * date		27Oct18
 *
 * history 	\arg	
 */
#ifndef __DNS_H__
#define __DNS_H__

#include <linux/string.h>
#include <common.h>
#include <command.h>
#include <net.h>

#include "uip.h"
#include "dhcpd.h"

//一字节对齐
#pragma pack(1)
/* DNS报文头部 */
typedef struct _DNSHDR{
	unsigned short id;
	unsigned short flags;
	unsigned short questions;
	unsigned short answerRRs;
	unsigned short authorityRRs;
	unsigned short additionalRRs;
}DNSHDR;

/*DNS应答报文数据段格式*/
typedef struct _DNSANS{
	unsigned short name;
	unsigned short _type;
	unsigned short _class;
	unsigned int ttl;
	unsigned short len;
	unsigned int ipaddr;
}DNSANS;


/**************************************************************************************************/
/*                                           FUNCTIONS                                            */
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
void dump(u8_t *head, int len);

/* 
 * fn		static int getDNSReqLen(char* DNSReqData)
 * brief	得到dns包question偏移的长度，这个长度是可变的
 * details	
 *
 * param[in]	char* DNSReqData
 * param[out]	
 *
 * return	int长度
 * retval	
 *
 * note		
 */
int getDNSReqLen(char* DNSReqData);

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
void dns_init(void);

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
void handle_dns(void);

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
void create_dns_msg(void);

#endif	/* __DNS_H__ */
