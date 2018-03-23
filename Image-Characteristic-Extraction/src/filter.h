#pragma once
#include "Mat.h"
typedef std::pair<int, int> img_config;  //�涨ͼ��ĳ�����Ϣ  

struct kernel //�ں˺������ṩ���㹦��  �ں˺���
{	
	img_config main_config;
	//����
	kernel() :kernel_mat(new double *[3]),main_config(make_pair(3, 3))   //Ĭ�Ͼ���3*3 1��2��1     0 0 0  -1 -2 -3
	{
		int default_arr[9] = { 1,2,1,0,0,0,-1,-2,-1 };
		for (int i = 0; i < 3; i++)
		{
			kernel_mat[i] = new double[3];
			for (int j = 0; j < 3;j++)
			{
				kernel_mat[i][j] = default_arr[i * 3 + j];
			}
		}
	}


	explicit kernel(int &width, int &height) :kernel_mat(new double *[height]), main_config ( make_pair(width, height))
	{
		for (int i = 0; i < width; i++)
		{
			kernel_mat[i] = new double[width];
		}
	}
	//�����ʼ��
	explicit kernel( double** &kernel_mat_, int &width, int &height) :kernel_mat(kernel_mat_), main_config(make_pair(width, height)) {};
	explicit kernel(double** &kernel_mat_, int &&width, int &&height) :kernel_mat(kernel_mat_), main_config(make_pair(move(width), move(height))) {};
	void show_kernel() {
		if (kernel_mat == nullptr)
		{
			int msgboxID = MessageBox(
				NULL,

				(LPCSTR)L"NULLPTR(mat)",
				(LPCSTR)L"Account Details",
				MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
			);
			return;
		}

		string show_mat = "";
		for (int i = 0; i < main_config.second; i++)
		{
			for (int j = 0; j < main_config.first; j++)
			{


				show_mat += std::to_string(kernel_mat[i][j]) + " ";
			}
			show_mat += "\n";

		}
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)show_mat.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
	}
public:
	double **kernel_mat;
	double * operator[](int &index) { return kernel_mat[index]; }
	double * operator[](int &&index) { return kernel_mat[move(index)]; }

};


//class filter;
class kernel_factory  //������ ����   ��Щ�������ⶨ���  �����ʱδʵ��
{
public:
	enum kerneltype {box,blur,gaussianblur};
	kernel_factory(Mat* & main_mat_r,const int &k_width,const int &k_height, kerneltype  typ, const double &gaussian_sigma=0);
	kernel* get_factory_kernel() { return factory_kernel; }
private:
	kernel *factory_kernel;
	void init_box_kernel(Mat* &main_mat_r, const int &k_width,const  int &k_height);
	void init_gaussianblur_kernel(Mat* &main_mat_r,const int &k_size, const double &sigama);
	void init_blur_kernel(Mat* &main_mat_r,const int &k_width,const int &k_height);
};






class filter   //�˲��� �ṩһ����˲��ӿ�   ��ͨ���˲��޸�Mat��ֵ
{
public:
	explicit filter(Mat* &main_mat_r) ;
	~filter();
	double**  convolution();  //���  ��Ϊ��Ԫ��Ϊ����Ϊ��̬ѧ�����ṩ�ӿ�;

	/*�����˲����� */  //����Ϊ�˺�����С
	void boxblur(const int &kernel_width,const int &kernel_height);//�����˲�
	void blur(const int &kernel_width, const int &kernel_height);   //��ֵ�˲�
	void GaussianBlur(const int &kernel_size, const double &sigma);//��˹�˲�
	
	/*End*/





	/*�������˲�����*/
	/*�������˲�����������.�˲����������ؽ������*/
	Mat*  medianblur();       //��ֵ�˲�������ߵ� ��������ȥ����
	Mat*  bliateralblur(int r, int sigma_d, int sigma_r);   //˫���˲�
	/*End*/


	Mat *custom_kernel_op(kernel *&custom_kernel);   //�����ṩһ�������Զ���˵ĺ�������֧����sobel�����Ĳ���
	kernel*  get_kernel(){ return kernel_mat; }
private:
	kernel *kernel_mat ;
	int width, height;
	Mat *main_mat;
};


