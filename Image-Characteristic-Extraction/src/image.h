#pragma once
#include "D3DGraphics.h"
#include "Mat.h"
#include <iostream>
class Mat;
const unsigned long  ANDD = 0x000000ff;
typedef std::pair<int, int> img_config;  //�涨ͼ��ĳ�����Ϣ  

class image
{
public:
	enum DirectionState
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	image(D3DGraphics &d3d_,D3DCOLOR *image_surface,const img_config &img_onfig) ;   
	image(D3DCOLOR * image_surface_, const img_config & img_config);
	~image();
	void show_initial_image()const;  //����ǰ��ͼ��
	void show_initial_image(const int &xoff,const int &yoff)const;
	void show_final_image()const;	//������ͼ��
	void show_fourier_image()const;
	
	//....
	//treat function
	void Grayscale(int way);// �ҶȻ����� wayΪ����
	void  ConverTo_Fourier_atlas(Mat &mat);  //ת��Ϊ����Ҷͼ��   ����Ϊ������Ҫ�ҶȻ�
	//
	void _draw_image(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf, DirectionState dec)const;
	unsigned char to_matrix_max(D3DCOLOR &color);           //��d3dcolorת��Ϊu char
	unsigned char to_matrix_avg(D3DCOLOR &color);           
public: img_config get_img_config() { return main_config; }
	D3DCOLOR *get_inital_surface() { return inital_image_surface; }
	D3DCOLOR *get_final_surface() { return final_image_surface; }
	
private:
	img_config main_config;
	D3DGraphics *main_d3d;
	D3DCOLOR *inital_image_surface;
	D3DCOLOR final_image_surface[30000];
	D3DCOLOR *fourier_surface;
};

