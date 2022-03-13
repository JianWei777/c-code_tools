/*************************************************************************
	> File Name: manger.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年03月07日 星期一 22时22分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdint.h>
#include<pcap.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <arpa/inet.h>

#include"pcap_analyse.h"
#define PCAP_FILE_PATH  256
#define PCAP_ERRBUF_SIZE 256
static uint8_t target_pcap_file[PCAP_FILE_PATH];
static pcap_t *g_pcap_handle;
static volatile uint8_t g_print_flag;	///< 用于控制终端展示
static uint64_t g_pkt_num;		///< 用于进行包计数
static uint64_t g_ip_datasize;	///< 用于进行ip数据统计计数
/*展示工具用法*/
static void show_usage()
{
    puts("usage: exe -f pcap_file_path [-p / --print]");
    return;
}



/**************************************
 *note:
     struct option 
     {  
         const char *name;  
         int         has_arg;  
         int        *flag;  
         int         val;  
     }; 
 *      
 *breif: deal with cmd_param
 *retval: num_param count
 *************************************/
static int deal_with_cmdline(int argc ,char** argv)
{
    int opcode;  ///< 返回的操作码
    int digit_optind = 0;

    while (1) {
        int this_option_optind = optind ? optind : 1;   ///< 非常保守的初始化
        int option_index = 0;
        static struct option long_options[] = {
            {"file",  required_argument,  NULL,  'f' },
            {"help",    no_argument,        NULL,  'h' },
            {"print",    no_argument,        NULL,  'p' },
            {0,         0,                 0,  0 }
        };

        opcode = getopt_long(argc, argv, "f:hp",
                long_options, &option_index);
        if (opcode == -1)
            break;

		switch (opcode) {
		case 0:
			printf("option %s", long_options[option_index].name);
			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
			break;
		case 'f':
			if(optarg)
				memcpy(target_pcap_file , optarg , sizeof(target_pcap_file));               
			break;
		case 'p':
			g_print_flag = 1;
			break;
		case 'h':
		case '?':
			show_usage();                                                
			break;
		
		default:
			printf("?? getopt returned character code 0%o ??\n", opcode);
		}
	}
	int tmp;
    if (optind < argc) {
        tmp = optind ;
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    return argc - tmp;

}
/*
 *brief	：实现主要功能的回调接口
 *param[in]:
		用户使用的指针（传参用）
		帧头结构体指针	：指向每一帧的头部
		帧头数据		:frame head + 链路head + 网络头 + 传输层头 + payload
 *retval : NULL
 * */
static void pcap_callback(u_char* argument, const struct pcap_pkthdr* packet_header, const u_char* packet_content)
{
	g_pkt_num ++;
	comm_eth_head_t *eth_head_ptr = NULL ;
	comm_ip_head_t  *ip_head_ptr = NULL ;
	comm_tcp_head_t *tcp_head_ptr = NULL;
	comm_udp_head_t *udp_head_ptr = NULL;

	eth_head_ptr = (comm_eth_head_t *)packet_content;
	ip_head_ptr = (comm_ip_head_t*)(packet_content +  sizeof(comm_eth_head_t));
	g_ip_datasize += ntohs(ip_head_ptr->iplen);
	if(ip_head_ptr->protocol == 6)	///<tcp协议
		tcp_head_ptr = (comm_tcp_head_t*)(packet_content +  sizeof(comm_eth_head_t) + sizeof(comm_ip_head_t));
	else if(ip_head_ptr->protocol == 17)	///< udp协议
		udp_head_ptr = (comm_udp_head_t *)(packet_content +  sizeof(comm_eth_head_t) + sizeof(comm_ip_head_t));
	else
	{
		printf("we just support tcp/udp protocol \n'");
		return ;
	}
	
	uint32_t tmp_sip = ip_head_ptr->src_ip;
	uint8_t *tmp_src_Ptr = (uint8_t *)&tmp_sip;
	char sip_buf[16] = {};
	inet_ntop (AF_INET, tmp_src_Ptr, sip_buf, sizeof (sip_buf));

	uint32_t tmp_dip = ip_head_ptr->dst_ip;
	uint8_t *tmp_dst_Ptr =(uint8_t *) &tmp_dip;
	char dip_buf[16] = {};
	inet_ntop (AF_INET, tmp_dst_Ptr, dip_buf, sizeof (dip_buf));

	if(g_print_flag && tcp_head_ptr)
	{
		printf("sport:%d\t dport:%d\t sip:%s\t dip:%s\t protocol %d \n ",\
				htons(tcp_head_ptr->sport) ,htons(tcp_head_ptr->dport),\
				sip_buf , dip_buf,ip_head_ptr->protocol );

	}
	else if(g_print_flag && udp_head_ptr)
	{
		printf("sport:%d\t dport:%d\t sip:%s\t dip:%s\t protocol %d \n ",\
				htons(udp_head_ptr->sport) ,htons(udp_head_ptr->dport),\
				sip_buf , dip_buf,ip_head_ptr->protocol );

	}

	return ;
}

/*
 *brief		:工具内部初始化
 *
 *ret_val	:0 表示初始化成功
 *
 * */
int comm_init()
{
	char errbuf[PCAP_ERRBUF_SIZE] = {};
	g_pcap_handle = pcap_open_offline(target_pcap_file , errbuf);
	if(!g_pcap_handle)
	{
		printf("%s" , errbuf);
		return -1;
	}
	return 0;
}

/*
 *	brief: 程序执行的入口
 *	param in:入参个数，入参字符串列表
 *	retval:0 for success
 * */
int main(int argc ,char **argv)
{
	if(argc < 3)
	{
		printf("example usage : %s  -f path of pcap_file" , argv[0]);
		exit(1);
	}

	int num = deal_with_cmdline(argc , argv);	///< 处理命令行完毕
	
	int ret = comm_init();	///< 进行配置初始化
	if(ret)
	{
		puts("init failed\n");
		return -1;
	}
	
	pcap_loop(g_pcap_handle , -1 ,pcap_callback ,NULL);	///< libpcap提供的句柄，循环解析 ，回调函数 ，用户自由支配的指针	

	printf("proc over , pkts :%lu ip len :%lu\n" , g_pkt_num ,g_ip_datasize);
	return 0;
}



