/*************************************************************************
	> File Name: manger.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年03月07日 星期一 22时22分51秒
 ************************************************************************/

#include<stdio.h>
#include<pcap.h>
#include<pcap_analyse.h>

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
            {"method",  required_argument,  NULL,  'm' },
            {"help",    no_argument,        NULL,  'h' },
            {0,         0,                 0,  0 }
        };

        opcode = getopt_long(argc, argv, "m:h",
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
		case 'm':
			if(optarg)
				proc_type = atol(optarg);               
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

	int num = deal_with_cmdline(argc , argv);
	
	
	return 0;
}



