#pragma once
#include "filter.h"

class morph     //���� ��filter��morphдһ������ 
{
	
	explicit morph(Mat* &main_mat_r);
	explicit morph(Mat* &main_mat_r, double **kernel);
	Mat *erode(const int& size, const double &element) { morph_operate(true); };
	Mat *dilate(const int & size, const double &element) { morph_operate(false); };
	double**  convolution();
	//�˲�Ӧ����Ϊ��Ա �����Ѿ����˿� Ҫ΢Ц���������ȥ


private:
	Mat *morph_operate(bool is_erode);
	kernel *kernel_mat;
	int width, height;
	Mat *main_mat;
};
