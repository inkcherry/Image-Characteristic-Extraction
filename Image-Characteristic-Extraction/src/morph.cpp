#include "morph.h"

morph::morph(Mat *& main_mat_r) :main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second),
kernel_mat(nullptr)//Ĭ��
{
	double **default_kernel = new double *[3];    //Ĭ�Ͼ��κ�
	for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			default_kernel[i][j] = 1;
		}
	kernel_mat = new kernel(default_kernel,3,3);
}

double ** morph::convolution()//��Ϊ���͸�ʴ  ��һ����Ҫ ƽ̹  �������ط���Ҫ��д
{
	
}
