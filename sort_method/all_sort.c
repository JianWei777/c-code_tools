/*************************************************************************
  > File Name: all_sort.c
  > Author: JianWei
  > Mail: wj_clear@163.com 
  > Created Time: 2021年12月26日 星期日 19时03分35秒
 ************************************************************************/

#include"all_sort.h"

#define MAX_BUF_LEN 65535


static enum sort_type
{
	/*比较排序*/
	bubble_sort,		///< 冒泡排序
	fast_sort,			///< 快排
	simple_insert_sort,	///< 简单插入排序
	xier_insert_sort,	///< 希尔插入排序
	simple_select_sort,	///< 简单选择排序
	heap_sort,			///< 堆排序
	double_merge_sort,	///< 二路归并排序
	muti_merge_sort,	///< 多路归并排序
	/*非比较排序*/
	count_sort,			///< 计数排序
	bucket_sort,		///< 桶排序
	basic_sort			///< 基数排序
}sort_method_e;


static long int num_buf[MAX_BUF_LEN];
static long proc_type; 
static void show_usage()
{
	puts("usage: exe -m/--method sort_type  N1 N2 N3 N4 ...Nx");
	puts("sort type :");
	puts("0  > 冒泡排序");
	puts("1  > 快速排序");
	puts("2  > 简单插入排序");
	puts("3  > 希尔插入排序");
	puts("4  > 简单选择排序");
	puts("5  > 堆排序");
	puts("6  > 二路归并排序");
	puts("7  > 多路归并排序");
	puts("8  > 计数排序");
	puts("9  > 桶排序");
	puts("10 > 基数排序");
	return;
}
/*********************************************
 *@brief	:
 *@param[in]:
 *@note		:
 *@retval	:
 * ******************************************/
int sort_num_byorder(long proc_type ,int  num_count)
{
	switch(proc_type )
	{
		case(bubble_sort):
			bubble_sort_func(num_buf , num_count);
			break;

		case(fast_sort):
			fast_sort_func(num_buf , num_count);
			break;

		case(simple_insert_sort):
			simple_insert_sort_func(num_buf , num_count);
			break;

			/*
			   case(simple_select_sort):
			   simple_select_sort_func(num_buf , num_count);
			   break;

			   case(xier_insert_sort):
			   xier_insert_sort_func(num_buf , num_count);
			   break;

			   case(heap_sort):
			   heap_sort_func(num_buf , num_count);
			   break;

			   case(double_merge_sort):
			   double_merge_sort_func(num_buf , num_count);
			   break;

			   case(muti_merge_sort):
			   muti_merge_sort_func(num_buf , num_count);
			   break;

			   case(count_sort):
			   count_sort_func(num_buf , num_count);
			   break;

			   case(bucket_sort):
			   bucket_sort_func(num_buf , num_count);

			   break;

			   case(basic_sort):
			   basic_sort_func(num_buf , num_count);
			   break;
			   */
		default:
			printf("sorry, we haven't support %ld sort_func\n" ,proc_type);
			return -1;
			break;
	}

	return 0;
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
	int opcode;	 ///< 返回的操作码
	int digit_optind = 0;

	while (1) {
		int this_option_optind = optind ? optind : 1;	///< 非常保守的初始化
		int option_index = 0;
		static struct option long_options[] = {
			{"method",	required_argument,	NULL,  'm' },
			{"help",	no_argument,		NULL,  'h' },
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

	for( int i =0 ; i < (argc - tmp ) ; i ++)
		num_buf[i] = atol(argv[i + tmp]);	///< fill global buffer use shell params
	return argc - tmp;
}


/*********************************************
 *@brief	:
 *@param[in]:
 *@note		:
 *@retval	:
 * ******************************************/
int main(int argc ,char** argv)
{
	static const uint8_t  default_type = bubble_sort ;

	int i = 0 , ret = -1;

	if(argc < 4)
	{
		show_usage();
		return -1;
	}

	int num = deal_with_cmdline(argc , argv);

	if( proc_type < bubble_sort || proc_type >  basic_sort )
	{
		fprintf(stderr ," sort type is invalid ! use default sort_type %d\n" , default_type );
		proc_type = default_type ; 
	}

	ret = sort_num_byorder(proc_type , num);	///< tell sort_func_type and num 
	if(!ret)
	{
		printf("sort over! sorted list :\n");
		for(i = 0 ; i < num; i++)
			printf("%ld " ,num_buf[i]);
		putchar(10);
	}

	return 0;
	///< 测试git功能
}
