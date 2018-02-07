#pragma once
#include "image.h"
#include "dft.h"
#include "D3DGraphics.h"
#include <cstring>
#include <string>
#include <iostream>
#include <functional>
typedef std::pair<int, int> img_config;  //�涨ͼ��ĳ�����Ϣ  
class Mat   //��Ҫ�ȻҶȻ�
{
public:
	
	explicit Mat(img_config &image, D3DCOLOR *surface);  //���ؾ���ת��ΪMat
	explicit Mat(double **arr, int width, int height);   //��ͨ2d����ת��ΪMat
	void show_main_mat();
	~Mat();
	f_2A_matrix<double> dft();//change  
	D3DCOLOR *get_fourier_surface();   //��ȡ����Ҷͼ�� 
	img_config get_img_config() { return std::make_pair(width, height); }
	double * operator [](int &index) { return main_mat[index]; };
	double * operator [](const int &index) { return main_mat[index]; };
	double * operator [](int &&index) { return main_mat[move(index)]; };

private:
	void _conver_to_mat(D3DCOLOR *surface);
	int width;
	int height;
	double **main_mat;//������

};

