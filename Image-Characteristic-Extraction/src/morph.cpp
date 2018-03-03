#include "morph.h"

morph::morph(Mat *& main_mat_r) :main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second),
kernel_mat(nullptr)//默认
{
	double **default_kernel = new double *[3];    //默认矩形核
	for (int i = 0; i < 3; i++)
	{
		default_kernel[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{
			default_kernel[i][j] = 1;
		}
	}
	kernel_mat = new kernel(default_kernel,3,3);
}

Mat * morph::morph_operate(bool is_erode)  //
{
	double ** res_mat = new double *[height];
	for (int i = 0; i < height; i++)
	{
		res_mat[i] = new double[width];
	}
	//默认核是平坦的 
	if (kernel_mat->main_config.first != kernel_mat->main_config.second) //方形检测
		exit(-1);
	
	if (kernel_mat->main_config.first % 2 != 1)
		exit(-1);
	
	const int size = kernel_mat->main_config.first;
	const int edge = size / 2;   //floor

	const int bottom = height - size - 1;
	const int right = width - size - 1;
	double t_max;
	int l, r, t, b;
	if (!is_erode)    //膨胀 （取最大值）
	{ 
		for (int i = edge; i < height-edge; i++)  //中心处理
		{
			 t_max = 0;
			for (int j = edge; j < width-edge; j++)
			{
				 l = i - edge, r = i + edge,  t = j - edge, b = edge + 1;
				for(int k=t;k<b;k++)  
					for (int s = l; s < r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;
			}
		}

		for (int i = 0; i < edge; i++)  //边缘处理(上)
		{
			 t_max = 0;
			for (int j = 0; j < width; j++)
			{
				l = i - edge, r = i + edge, t = j - edge, b = edge + 1;
				//对边远地带的越界处理  上部分  b（bottom)不会越界
				l = l < 0 ? 0 : l;
				r = r > width - 1 ? width - 1 : r;
				t = t < 0 ? 0 : t;
				
				for (int k = t; k < b; k++)
					for (int s = l; s < r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;

			}
		}
		
		for (int i = height - edge; i < height-1; i++)//边缘处理(下)
		{
			t_max = 0;

			for (int j = 0; j < width; j++)
			{
				l = i - edge, r = i + edge, t = j - edge, b = edge + 1;
				//对边远地带的越界处理  下部分   t（top)不会越界
				l = l < 0 ? 0 : l;
				r = r > width - 1 ? width - 1 : r;
				t = t < 0 ? 0 : t;
				b = b > height - 1 ? height - 1 : b;

				for (int k = t; k < b; k++)
					for (int s = l; s < r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;

			}
		}

		for (int i = 0; i < height; i++)      //(左)
		{
			t_max = 0;

			for (int j = 0; j < edge; j++)
			{
				l = i - edge, r = i + edge, t = j - edge, b = edge + 1;
				//对边远地带的越界处理  左部分r（right)不会越界
				l = l < 0 ? 0 : l;
				t = t < 0 ? 0 : t;
				b = b > height - 1 ? height - 1 : b;

				for (int k = t; k < b; k++)
					for (int s = l; s < r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;

			}
		}

		for (int i = 0; i < height; i++)  //(右)
		{
			t_max = 0;

			for (int j = width - edge; j < width; j++)
			{
				l = i - edge, r = i + edge, t = j - edge, b = edge + 1;
				//对边远地带的越界处理  右部分l（left）不会越界
				l = l < 0 ? 0 : l;
				t = t < 0 ? 0 : t;
				b = b > height - 1 ? height - 1 : b;

				for (int k = t; k < b; k++)
					for (int s = l; s < r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;
			}
		}
	}

	else
	{

	}
	Mat* res_mat_ = new  Mat(res_mat,width,height);
	return res_mat_;
	return nullptr;
}

