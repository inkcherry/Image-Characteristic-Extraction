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

	////��� g=f*h  ����һ���µľ���
	//double **res_mat=new double *[height];  //������� ������ԭ������ͬ
	//for (int i = 0; i < height; i++)
	//	res_mat[i] = new double[width];



	//int h_main_mat = height;
	//int w_main_mat = width;
	//int h_kernel_mat = kernel_mat.main_config.first;
	//int w_kernel_mat = kernel_mat.main_config.second;
	////Mat *res_Mmat = new Mat(width, height);
	//
	//	double temp;

	//	for (int i = 0; i < h_main_mat + h_kernel_mat - 1; i++)
	//	{
	//		for (int j = 0; j < w_main_mat + w_kernel_mat - 1; j++)
	//		{
	//			temp = 0;
	//			for (int m = 0; m < h_main_mat; m++)
	//			{
	//				for (int n = 0; n < w_main_mat; n++)
	//				{
	//					if ((i - m) >= 0 && (i - m) < h_kernel_mat && (j - n) >= 0 && (j - n) < w_kernel_mat)
	//					{
	//						temp += main_mat[m][n] * kernel_mat[i - m][j - n];
	//					}
	//				}
	//			}
	//			res_mat[i][j] = temp;

	//		}
	//	}
	//
}
//��ȡdftд�ĺܲ��Ѻõľ��飬ȫ��double���ˡ�
