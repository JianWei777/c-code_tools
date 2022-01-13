/*************************************************************************
	> File Name: all_sort.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2021年12月26日 星期日 19时03分35秒
 ************************************************************************/

#include<stdio.h>
#include<stdint.h>

#define MAX_BUF_LEN 65535

static enum sort_type
{
	bubble_sort,		///< 
	fast_sort,
	simple_insert_sort,
	xier_insert_sort,
	simple_select_sort,
	heap_sort,
	double_merge_sort,
	muti_merge_sort,
	count_sort,
	bucket_sort,
	basic_sort
}


char num_buf[MAX_BUF_LEN];


/*********************************************
 *@brief	:
 *@param[in]:
 *@note		:
 *@retval	:
 * ******************************************/
int sort_num_byorder(uint8_t proc_type)
{
	switch(proc_type )
	{
		case(bubble_sort)
			bubble_sort_func(num_buf);
		break:

		case(fast_sort)
			fast_sort_func(num_buf);
		break:
		
		case(simple_insert_sort)
			simple_insert_sort_func(num_buf);
		break:
		
		case(simple_select_sort)
			simple_select_sort_func(num_buf);
		break:
		
		case(xier_insert_sort)
			xier_insert_sort_func(num_buf);
		break:
		
		case(heap_sort)
			heap_sort_func(num_buf);
		break:
		
		case(double_merge_sort)
			double_merge_sort_func(num_buf);
		break:
		
		case(muti_merge_sort)
			muti_merge_sort_func(num_buf);
		break:
		
		case(count_sort)
			count_sort_func(num_buf);
		break:
		
		case(bucket_sort)
			bucket_sort_func(num_buf);
		
		break:
		
		case(basic_sort)
			basic_sort_func(num_buf);
		break:

		default:
			printf("sorry, we haven't support %d sort_func\n" ,proc_type);
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
	if(argc < 3)
	{
		printf("usage : exe [0-9] [num1 ... numN] \n ");
		return -1;
	}

	puts("input your nums");
	for(int i =0 ; i < argc ; i ++)
		num_buf[i] = atoi(argv[i + 2]);	///< fill global buffer use shell param 
	
	uint8_t proc_type = atoi(argv[1]);	
	sort_num_byorder(proc_type);
	
	printf("sort over!\n");

}
