#pragma once
#include "filter.h"

class morph     //���� ��filter��morphдһ������ 
{
public:
	explicit morph(Mat* &main_mat_r);
	explicit morph(Mat* &main_mat_r, double **kernel);
	Mat *erode(const int& size, const double &element) { return morph_operate(true); }  //min
	Mat *dilate(const int & size, const double &element) {return morph_operate(false); } //max
	//�˲�Ӧ����Ϊ��Ա �����Ѿ����˿� Ҫ΢Ц���������ȥ


	//
	Mat *open_op(const int &size);   //��ʴmin+����max �����
	Mat *close_op(const int &szie);//����+��ʴ ���� ��
	Mat *morph_grad(const int &size);   //�ݶ�
	Mat *top_hat(const int &szie);//��ñ  ԭͼ���뿪����֮��
	Mat *black_hat(const int &szie); //��ñ	ԭͼ���������֮��

private:
	Mat *morph_operate(bool is_erode);
	kernel *kernel_mat;
	int width, height;
	Mat *main_mat;
};
