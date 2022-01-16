/*************************************************************************
	> File Name: bubble_sort.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年01月15日 星期六 23时29分35秒
 ************************************************************************/
#include "all_sort.h"
int bubble_sort_func(long* num_buffer , int num_count)
{
	long temp;
	int cycle_out = 0,cycle_inter = 0;
	for( ;cycle_out < num_count - 1 ; cycle_out ++ )
	{
		for(cycle_inter = 0 ; cycle_inter < num_count - cycle_out - 1 ; cycle_inter ++)
		{
			if(num_buffer[cycle_inter] > num_buffer[cycle_inter + 1])
			{
				temp = num_buffer[cycle_inter + 1];				
				num_buffer[cycle_inter + 1] = num_buffer[cycle_inter];
				num_buffer[cycle_inter ] = temp;
			}
		}
	}
	return 0;
};
