#include "filter.h"

filter::filter(Mat & main_mat_r):main_mat(&main_mat_r),
	width(main_mat_r.get_img_config().first),
	height(main_mat_r.get_img_config().second)
{
}

void filter::convolution()
{
}


//��ȡdftд�ĺܲ��Ѻõľ��飬ȫ��double���ˡ�
