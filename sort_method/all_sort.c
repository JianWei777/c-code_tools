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
/*
   case(fast_sort):
			fast_sort_func(num_buf , num_count);
		break;
		
		case(simple_insert_sort):
			simple_insert_sort_func(num_buf , num_count);
		break;
		
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
/*********************************************
 *@brief	:
 *@param[in]:
 *@note		:
 *@retval	:
 * ******************************************/
int main(int argc ,const char** argv)
{
	static const uint8_t  default_type = bubble_sort ;
	
	int i = 0 , ret = -1;

	if(argc < 3)
	{
		printf("usage : exe [0-9] [num1 ... numN] \n ");
		return -1;
	}

	for( i =0 ; i < argc - 2; i ++)
		num_buf[i] = atol(argv[i + 2]);	///< fill global buffer use shell param 
	
	long proc_type = atol(argv[1]);


	if( proc_type < bubble_sort || proc_type >  basic_sort )
	{
		fprintf(stderr ," sort type is invalid ! use default sort_type %d\n" , default_type );
		proc_type = default_type ; 
	}

	ret = sort_num_byorder(proc_type , argc - 2);	///< tell sort_func_type and num 
	if(!ret)
	{
		printf("sort over! sorted list :\n");
		for(i = 0 ; i < argc - 2; i++)
			printf("%ld " ,num_buf[i]);
		putchar(10);
	}

	return 0;

}
