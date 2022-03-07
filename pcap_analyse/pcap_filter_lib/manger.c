/*************************************************************************
	> File Name: manger.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年03月07日 星期一 22时22分51秒
 ************************************************************************/

#include<stdio.h>
#include<pcap.h>
/*
 *	brief: 程序执行的入口
 *	param in:入参个数，入参字符串列表
 *	retval:0 for success
 * */
int main(int argc ,const char **argv)
{
	if(argc < 3)
	{
		printf("example usage : %s  -f pcap_file" , argv[0]);
		exit(1);
	}

	return 0;
}



