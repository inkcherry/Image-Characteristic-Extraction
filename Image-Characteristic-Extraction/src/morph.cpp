#include "morph.h"

morph::morph(Mat *& main_mat_r) :main_mat(main_mat_r),
width(main_mat_r->get_img_config().first),
height(main_mat_r->get_img_config().second),
kernel_mat(nullptr)//Ĭ��
{
	double **default_kernel = new double *[3];    //Ĭ�Ͼ��κ�
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
	//Ĭ�Ϻ���ƽ̹�� 
	if (kernel_mat->main_config.first != kernel_mat->main_config.second) //���μ��
		exit(-1);
	
	if (kernel_mat->main_config.first % 2 != 1)
		exit(-1);
	
	const int size = kernel_mat->main_config.first;
	const int edge = size / 2;   //floor

	const int bottom = height - size - 1;
	const int right = width - size - 1;
	double t_max=0,t_min=256;
	int l, r, t, b;
	if (!is_erode)    //���� ��ȡ���ֵ��
	{ 
		for (int i = edge; i < height-edge; i++)  //���Ĵ���
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

		for (int i = 0; i < edge; i++)  //��Ե����(��)
		{
			 t_max = 0;
			for (int j = 0; j < width; j++)
			{
				l = j - edge, r = j + edge, t = i - edge, b = i+edge ;
				//�Ա�Զ�ش���Խ�紦��  �ϲ���  b��bottom)����Խ��
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
		
		for (int i = height - edge; i < height; i++)//��Ե����(��)
		{
			t_max = 0;

			for (int j = 0; j < width; j++)
			{
				l = j - edge, r = j + edge, t = i - edge, b = i+edge;
				//�Ա�Զ�ش���Խ�紦��  �²���   t��top)����Խ��
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

		for (int i = 0; i < height; i++)      //(��)
		{
			t_max = 0;

			for (int j = 0; j < edge; j++)
			{
				l = j - edge, r = j + edge, t = i - edge, b =i + edge;
				//�Ա�Զ�ش���Խ�紦��  �󲿷�r��right)����Խ��
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

		for (int i = 0; i < height; i++)  //(��)
		{
			t_max = 0;

			for (int j = width - edge; j < width; j++)
			{
				l = j - edge, r = j + edge, t = i - edge, b = i + edge;
				//�Ա�Զ�ش���Խ�紦��  �Ҳ���l��left������Խ��
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
	for (int i = edge; i < height - edge; i++)  //���Ĵ���
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

	for (int i = 0; i < edge; i++)  //��Ե����(��)
	{
		t_min = 256;

		for (int j = 0; j < width; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//�Ա�Զ�ش���Խ�紦��  �ϲ���  b��bottom)����Խ��
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

	for (int i = height - edge; i < height; i++)//��Ե����(��)
	{
		t_min = 256;

		for (int j = 0; j < width; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//�Ա�Զ�ش���Խ�紦��  �²���   t��top)����Խ��
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

	for (int i = 0; i < height; i++)      //(��)
	{
		t_min = 256;

		for (int j = 0; j < edge; j++)
		{
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//�Ա�Զ�ش���Խ�紦��  �󲿷�r��right)����Խ��
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

	for (int i = 0; i < height; i++)  //(��)
	{
		

		for (int j = width - edge; j < width; j++)
		{
			t_min = 256;
			l = j - edge, r = j + edge, t = i - edge, b = i + edge;
			//�Ա�Զ�ش���Խ�紦��  �Ҳ���l��left������Խ��
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

