#pragma once
#include "image.h"
#include "dft.h"
#include "D3DGraphics.h"
#include <cstring>
#include <string>
#include <iostream>
#include <functional>
#include <memory>
typedef std::pair<int, int> img_config;  //规定图像的长宽信息  
class Mat   //需要先灰度化
{
public:
	
	explicit Mat(img_config &image, D3DCOLOR *surface);  //像素矩阵转换为Mat
	explicit Mat(double **arr, int width, int height);   //普通2d矩阵转换为Mat
	explicit Mat(int width, int heiight);                //默认生成的全是0的矩阵
	void show_main_mat();
	~Mat();
	f_2A_matrix<double> dft();//change  
	D3DCOLOR *get_fourier_surface();   //获取傅里叶图谱 
	img_config get_img_config() { return std::make_pair(width, height); }
	double * operator [](int &index) { return main_mat[index]; };
	double * operator [](const int &index) { return main_mat[index]; };
	double * operator [](int &&index) { return main_mat[move(index)]; };
	shared_ptr<D3DCOLOR> conver_to_d3dmat();  //把mat还原为d3dcolor数组

	inline void set_value(int &i, int &j, double &value) { main_mat[i][j] = value; }
	
	void show_ascii_art();

private:
	bool  need_delete_mainmat;  //初始化方式标志，如果是外部矩阵指针直接初始化 析构Mat不会析构外部指针
	void _conver_to_mat(D3DCOLOR *surface);
	int width;
	int height;
	double **main_mat;//主矩阵

};

