#pragma once
#include "Mat.h"
class filter   //�˲��� �ṩһ����˲��ӿ�   ��ͨ���˲��޸�Mat��ֵ
{

public:
	filter(Mat &main_mat_r);
	~filter();
	void  convolution();  //���

	/*�����˲����� */
	void boxblur();//�����˲�
	void blur();   //��ֵ�˲�
	void GaussianBlur();//��˹�˲�
	
private:
	int width, height;
	Mat *main_mat;
};

