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
	long temp = *num_buffer;	///< 取第一个数作为标杆
	
	int left_num = low , right_num = high;	///< 记录左初始值与右初始值

	while(left_num  <  right_num )	///< 开始循环判断左右是否满足左边都小于标准值，右边都大于标准值，不满足则替换左右坐标位置上的数字,直到左右下标重合
	{
		while(left_num  < right_num && temp < num_buffer[right_num])
			right_num--;	///< 找到标杆右面第一个小于标杆的数字的的下标

		if(left_num < right_num )	///< 防止仅有一个数参与排序
		{
			num_buffer[left_num] = num_buffer[right_num];	///< 右面的数字赋值給左面
			left_num ++;	///< 左边下标的向右滑动

		}


		while(left_num  < right_num && temp >= num_buffer[left_num])	///< 找标杆左面大于标杆的数字
			left_num ++;

		if(left_num < right_num )	///< 同样是防止一个数的情况
		{
			num_buffer[right_num] = num_buffer[left_num];	///< 再次把数值替换给右下标的数值
			right_num --;			///< 右下标向左偏移
		}


	}
#if 1
	num_buffer[left_num] = temp ;	///< 标杆值放到当前左下标的位置

	if(low < left_num)	///< 一直排到左右下标处于统一位置,出栈回溯
		fast_sort_func(num_buffer + low , right_num -1 - low);	///< 递归排标杆左边的数组

	if(high > left_num)
		fast_sort_func(num_buffer + right_num + 1,  high - right_num -1);	///< 递归排标杆右面的数组
#endif	
	return 0 ;
}
