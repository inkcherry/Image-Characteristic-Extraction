#pragma once
#include "filter.h"

class morph     //���� ��filter��morphдһ������ 
{
public:
	explicit morph(Mat* &main_mat_r);
	explicit morph(Mat* &main_mat_r, double **kernel);
	Mat *erode(const int& size, const double &element) { return morph_operate(true); };
	Mat *dilate(const int & size, const double &element) {return morph_operate(false); };
	//�˲�Ӧ����Ϊ��Ա �����Ѿ����˿� Ҫ΢Ц���������ȥ


private:
	Mat *morph_operate(bool is_erode);
	kernel *kernel_mat;
	int width, height;
	Mat *main_mat;
};
