/*************************************************************************
	> File Name: fast_sort.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年01月16日 星期日 16时05分27秒
 ************************************************************************/

#include "all_sort.h"

int fast_sort_func(long* num_buffer ,const int num_count)
{
	const int low = 0 , high = num_count - 1 ;
	long temp = *num_buffer;	///< 取第一个数作为标准值
	
	int left_num = low , right_num = high;

	while(left_num  <  right_num )
	{
		while(left_num  < right_num && temp < num_buffer[right_num])
			right_num--;

		if(left_num < right_num )
		{
			num_buffer[left_num] = num_buffer[right_num];
			left_num ++;

		}


		while(left_num  < right_num && temp >= num_buffer[left_num])
			left_num ++;

		if(left_num < right_num )
		{
			num_buffer[right_num] = num_buffer[left_num];
			right_num --;
		}


	}
	
	num_buffer[left_num] = temp ;

	if(low < left_num)
		fast_sort_func(num_buffer + low , right_num  - low);

	if(high > left_num)
		fast_sort_func(num_buffer + right_num,  high - right_num );
		

	return 0 ;

}
