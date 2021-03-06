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


Mat * morph::open_op(const int & size)
{
	Mat *intial_main_mat = main_mat;
	//开闭运算都是以成员main_mat为基础，需要暂时修改main_mat的值并在最后还原之
	main_mat = erode(size, 1.0);
	Mat *res_mat= dilate(size, 1.0);


	delete main_mat;  //删除中间矩阵
	main_mat = intial_main_mat;

	return res_mat;
	return nullptr;
}

Mat * morph::close_op(const int & size)
{
	Mat *intial_main_mat = main_mat;
	//开闭运算都是以成员main_mat为基础，需要暂时修改main_mat的值并在最后还原之
	
	
	main_mat = dilate(size,1.0);
	Mat *res_mat = erode(size, 1.0);

	delete main_mat;
	main_mat = intial_main_mat;

	return res_mat;
	return nullptr;
}

Mat * morph::morph_grad(const int & size)
{
	double **res_mat = new double *[height];
	for (int i = 0; i < height; i++)
	{
		res_mat[i] = new double[width];
		for (int j = 0; j < width; j++)
			res_mat[i][j] = 0;
	}

	Mat *after_erode = erode(size,1);
	Mat *after_dilate = dilate(size,1);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			res_mat[i][j] = ((*after_dilate)[i][j]) - ((*after_erode)[i][j]);
		}
	Mat *res_mat_ = new Mat(res_mat, width, height);
	delete after_erode;
	delete after_dilate;
	return res_mat_;
	return nullptr;
}

Mat * morph::top_hat(const int &size)
{ 
	Mat *after_openop_mat = open_op(size);
	double **res_mat = new double *[height];
	for (int i = 0; i < height; i++)
	{
		res_mat[i] = new double[width];
		for (int j = 0; j < width; j++)
			res_mat[i][j] = 0;
	}
	

	

	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			res_mat[i][j] = ((*main_mat)[i][j]) - ((*after_openop_mat)[i][j]);
		}

	Mat *res_mat_ = new Mat(res_mat, width, height);
	delete after_openop_mat;
	return res_mat_;
	return nullptr;
}

Mat * morph::black_hat(const int & size)
{
	Mat *after_closeop_mat = close_op(size);
	double **res_mat = new double *[height];
	for (int i = 0; i < height; i++)
	{
		res_mat[i] = new double[width];
		for (int j = 0; j < width; j++)
			res_mat[i][j] = 0;
	}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			res_mat[i][j] = (*after_closeop_mat)[i][j] - (*main_mat)[i][j];
		}

	Mat *res_mat_ = new Mat(res_mat, width, height);
	delete after_closeop_mat;
	return res_mat_;
	return nullptr;
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
	double t_max=0,t_min=256;
	int l, r, t, b;
	if (!is_erode)    //膨胀  dilate（取最大值）
	{ 
		for (int i = edge; i < height-edge; i++)  //中心处理
		{
			 t_max = 0;
			for (int j = edge; j < width-edge; j++)
			{
				 l = j - edge, r = j + edge,  t = i - edge, b = i+edge;
				for(int k=t;k<=b;k++)  
					for (int s = l; s <= r; s++)
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
				l = j - edge, r = j + edge, t = i - edge, b = i+edge ;
				//对边远地带的越界处理  上部分  b（bottom)不会越界
				l = l < 0 ? 0 : l;
				r = r > width - 1 ? width - 1 : r;
				t = t < 0 ? 0 : t;
				
				for (int k = t; k <= b; k++)
					for (int s = l; s <= r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;

			}
		}
		
		for (int i = height - edge; i < height; i++)//边缘处理(下)
		{
			t_max = 0;

			for (int j = 0; j < width; j++)
			{
				l = j - edge, r = j + edge, t = i - edge, b = i+edge;
				//对边远地带的越界处理  下部分   t（top)不会越界
				l = l < 0 ? 0 : l;
				r = r > width - 1 ? width - 1 : r;
				
				b = b > height - 1 ? height - 1 : b;

				for (int k = t; k <= b; k++)
					for (int s = l; s <=r; s++)
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
				l = j - edge, r = j + edge, t = i - edge, b =i + edge;
				//对边远地带的越界处理  左部分r（right)不会越界
				l = l < 0 ? 0 : l;
				t = t < 0 ? 0 : t;
				b = b > height - 1 ? height - 1 : b;

				for (int k = t; k <= b; k++)
					for (int s = l; s <= r; s++)
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
				l = j - edge, r = j + edge, t = i - edge, b = i + edge;
				//对边远地带的越界处理  右部分l（left）不会越界
				r = r > width - 1 ? width - 1 : r;
				t = t < 0 ? 0 : t;
				b = b > height - 1 ? height - 1 : b;

				for (int k = t; k <= b; k++)
					for (int s = l; s <= r; s++)
					{
						if ((*main_mat)[k][s] > t_max)
							t_max = (*main_mat)[k][s];
					}
				res_mat[i][j] = t_max;
			}
		}
	}
	

	//
	//
	//
	//



else {
	for (int i = edge; i < height - edge; i++)  //中心处理
	{
		t_min = 256;
		for (int j = edge; j < width - edge; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			for (int k = t; k <= b; k++)
				for (int s = l; s <= r; s++)
				{
					if ((*main_mat)[k][s] < t_min)
						t_min = (*main_mat)[k][s];
				}
			res_mat[i][j] = t_min;
		}
	}

	for (int i = 0; i < edge; i++)  //边缘处理(上)
	{
		t_min = 256;

		for (int j = 0; j < width; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//对边远地带的越界处理  上部分  b（bottom)不会越界
			l = l < 0 ? 0 : l;
			r = r > width - 1 ? width - 1 : r;
			t = t < 0 ? 0 : t;

			for (int k = t; k <= b; k++)
				for (int s = l; s <= r; s++)
				{
					if ((*main_mat)[k][s] < t_min)
						t_min = (*main_mat)[k][s];
				}
			res_mat[i][j] = t_min;

		}
	}

	for (int i = height - edge; i < height; i++)//边缘处理(下)
	{
		t_min = 256;

		for (int j = 0; j < width; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//对边远地带的越界处理  下部分   t（top)不会越界
			l = l < 0 ? 0 : l;
			r = r > width - 1 ? width - 1 : r;

			b = b > height - 1 ? height - 1 : b;

			for (int k = t; k <= b; k++)
				for (int s = l; s <= r; s++)
				{
					if ((*main_mat)[k][s] <t_min)
						t_min = (*main_mat)[k][s];
				}
			res_mat[i][j] = t_min;

		}
	}

	for (int i = 0; i < height; i++)      //(左)
	{
		t_min = 256;

		for (int j = 0; j < edge; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//对边远地带的越界处理  左部分r（right)不会越界
			l = l < 0 ? 0 : l;
			t = t < 0 ? 0 : t;
			b = b > height - 1 ? height - 1 : b;

			for (int k = t; k <= b; k++)
				for (int s = l; s <= r; s++)
				{
					if ((*main_mat)[k][s] <t_min)
						t_min = (*main_mat)[k][s];
				}
			res_mat[i][j] = t_min;

		}
	}

	for (int i = 0; i < height; i++)  //(右)
	{
		

		for (int j = width - edge; j < width; j++)
		{
			t_min = 256;
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//对边远地带的越界处理  右部分l（left）不会越界
			r = r > width - 1 ? width - 1 : r;
			t = t < 0 ? 0 : t;
			b = b > height - 1 ? height - 1 : b;

			for (int k = t; k <= b; k++)
				for (int s = l; s <= r; s++)
				{
					if ((*main_mat)[k][s] < t_min)
						t_min = (*main_mat)[k][s];
				}
			res_mat[i][j] = t_min;
		}
	}

     }

	Mat* res_mat_ = new  Mat(res_mat,width,height);
	return res_mat_;
	return nullptr;
}

