#include "filter.h"
//filter::filter(Mat & main_mat_r):main_mat(&main_mat_r),
//width(main_mat_r.get_img_config().first),
//height(main_mat_r.get_img_config().second),
//kernel_mat(kernel())  //Ĭ�Ϲ���
//{
//}


filter::~filter()
{
	delete main_mat;
}

void filter::convolution()  //mat�������
{
}
//��ȡdftд�ĺܲ��Ѻõľ��飬ȫ��double���ˡ�
