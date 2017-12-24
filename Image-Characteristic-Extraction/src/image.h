#pragma once
#include "D3DGraphics.h"
#include <iostream>
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
	~image();
	void show_initial_image();  //����ǰ��ͼ��
	void show_final_image();	//������ͼ��
	
	//....
	//treat function

	//
	void Grayscale(int way);// �ҶȻ����� wayΪ����
	void _draw_image(int xoff, int yoff, int width, int height, const D3DCOLOR *xsurf, DirectionState dec);
	unsigned char to_matrix_max(D3DCOLOR &color);           //��d3dcolorת��Ϊu char
	unsigned char to_matrix_avg(D3DCOLOR &color);           

private:
	img_config main_config;
	D3DGraphics *main_d3d;
	D3DCOLOR *inital_image_surface;
	D3DCOLOR final_image_surface[30000];
};

