/*************************************************************************
  > File Name: fast_sort.c
  > Author: JianWei
  > Mail: wj_clear@163.com 
  > Created Time: 2022年01月16日 星期日 16时05分27秒
 ************************************************************************/
#include "all_sort.h"
int fast_sort_func_inter(long* num_buffer ,const int low , const int high)
{
	uint32_t  pivot  = low, temp;
	int left_num = low , right_num = high;	///< 记录左初始值与右初始值
	
	if(high > low)
	{
		left_num = low ; 
		right_num = high;	///< 记录左初始值与右初始值

		while(left_num  <  right_num )	///< 开始循环判断左右是否满足左边都小于标准值，右边都大于标准值，不满足则互换左右坐标位置上的数字,直到左右下标重合
		{
			while(left_num  < high && num_buffer[left_num] <= num_buffer[pivot])	///< 从前向后找大于标杆的数字下标
				left_num ++;

			while(num_buffer[pivot] < num_buffer[right_num])
				right_num--;	///< 从后向前找小于等于标杆的数字的的下标

			if(left_num < right_num )	///< 防止仅有一个数参与排序
			{
				temp = num_buffer[left_num];
				num_buffer[left_num] = num_buffer[right_num];	
				num_buffer[right_num] = temp;	///< 交换位置
			}
		}

		temp = num_buffer[pivot] ;	///< 存pivot的数值
		num_buffer[pivot] = num_buffer[right_num];
		num_buffer[right_num] = temp;
		fast_sort_func_inter(num_buffer ,low, right_num - 1);	///< 递归排标杆左边的数组
		fast_sort_func_inter(num_buffer ,right_num + 1,high);	///< 递归排标杆右面的数组
	}

	return 0 ;
}

int fast_sort_func(long* num_buffer ,const int num_count)
{
	fast_sort_func_inter(num_buffer , 0 , num_count - 1);
	return 0;
}
