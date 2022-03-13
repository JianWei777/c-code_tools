/*************************************************************************
	> File Name: pcap_analyse.h
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年03月08日 星期二 22时33分06秒
 ************************************************************************/

#pragma once
#pragma pack(push , 1)
	/*常用的LinkType（链路类型）：参考博主：meteor^_^
   0              BSD loopback devices, except for later OpenBSD
   1              Ethernet, and Linux loopback devices
   6              802.5  Token Ring
   7              ARCnet
   8              SLIP
   9			  PPP
   10             FDDI
   101            "raw IP", with no link
   102             BSD/OS  SLIP
   103             BSD/OS  PPP
   104             Cisco  HDLC
   105             802.11
   108             later OpenBSD loopback devices (with the AF_value in network byte order)
   113             special  Linux  "cooked"  capture
   114             LocalTalk
   */
typedef struct _pcap_file_head{
	uint32_t  magic;		///< pcap文件的幻数
	uint16_t  version_major;	///< 当前文件的主要版本号，一般为0x0200
	uint16_t  version_minor;	///< 当前文件的次要版本号，一般为0x0400
	uint32_t  thiszone;		///< 当地的标准时间，如果用的是GMT则全零，一般全零
	uint32_t  sigfigs;    ///< 时间戳的精度，一般为全零
	uint32_t  snaplen;    ///< 最大的存储长度，设置所抓获的数据包的最大长度，如果所有数据包都要抓获，将值设置为65535
	uint32_t  linktype;   ///< 链路类型。解析数据包首先要判断它的LinkType，所以这个值很重要。一般的值为1，即以太网
}pcap_file_t;

typedef struct _frame_head{
	uint32_t Timestamp_sec;	 ///< 时间戳高位，精度 秒
	uint32_t Timestamp_usec; ///< 时间戳低位，精度 微秒
	uint32_t Caplen;		///< 到下一帧的偏移
	uint32_t Len;			///< 实际上下一帧的偏移，绝大多数情况下等于caplen，可能会小于caplen
}frame_head_t;


typedef struct _comm_eth_head{
	uint8_t src_mac[6];		///< 源mac地址
	uint8_t dst_mac[6];		///< 目标mac地址
	uint16_t type;			///<  请求类型  0x0800 ip数据 0x0806 arp 请求 0x8035 rarp 请求
}comm_eth_head_t;

typedef struct _comm_ip_head{
	uint8_t version:4,	///< 版本
			headlen:4;	///< 头部实际长度
	uint8_t TOS;		///< type of service
	uint16_t iplen;		///< ip数据报总长度
	uint16_t flag;		///< 16位标识
	uint16_t falg:3,	///< 3位标志
			 offset:13;///< 13位片偏移
	uint8_t  ttl;	///< time to live 生存时间
	uint8_t  protocol;
	uint16_t checksum;
	uint32_t src_ip;
	uint32_t dst_ip;
	/*变长部分暂不关心*/
}comm_ip_head_t;

typedef struct _comm_tcp_head{
	uint16_t sport;			///< 源端口
	uint16_t dport;			///< 目的端口
	uint32_t seq;			///< 序号字段
	uint32_t ack;			///< 确认序号应当是上次已成功收到数据字节序号加 1
	uint16_t head_len:4,	///< 首部长度
			 reserved:6,	///< 保留位
			 UGR:1,		///< 紧急指针 
			 ACK:1,		///< 确认序号有效
			 PSH:1,		///< 接收方应该尽快将这个报文段交给应用层
			 RST:1,		///< 重建连接
			 SYN:1,		///< 同步序号用来发起一个连接
			 FIN:1;		///< 发端完成发送任务
	uint16_t win_size;		///< 窗口大小，T C P的流量控制由连接的每一端通过声明的窗口大小来提供
	uint16_t checksum;		///< 检验和覆盖了整个的 T C P报文段：T C P首部和T C P数据
	uint16_t urgent_ptr;	///< T C P的紧急方式是发送端向另一端发送紧急数据的一种方式。
		/*其他选项*/
}comm_tcp_head_t;

typedef struct _comm_udp_head{
	uint16_t  sport;
	uint16_t  dport;
	uint16_t  headlen;	///< UDP首部和UDP数据的字节长度
	uint16_t  check_sum;///< udp校验和
}comm_udp_head_t;

#pragma (pop)
