/*************************************************************************
	> File Name: simple_insert.c
	> Author: JianWei
	> Mail: wj_clear@163.com 
	> Created Time: 2022年02月20日 星期日 16时14分36秒
 ************************************************************************/

#include<stdio.h>
int simple_insert_sort_func(long *num_buf ,const int num_count)
{
	int pre ;	///< 记录成员该插入的位置
	long temp;	///< 记录成员值
	for(int i = 1   ; i < num_count ; i ++)	///< 默认第一个成员是排序完成的，从第二个开始向前搜索该值应该插入的位置
	{
		pre = i - 1  ;
		temp = num_buf[i];
		while(pre >= 0  && num_buf[pre] > temp)	///< 该位置应该满足坐标大于零且小于等于后一个值，找到则退出循环，否则该查找范围内的数应该向后挪出一个位置
		{
			num_buf[pre + 1] = num_buf [pre ];
			pre -- ;
		}
		num_buf[pre + 1 ] = temp;	
	}

	return 0;
}
