#pragma once
#include "image.h"
#include "dfa.h"
#include "D3DGraphics.h"
class Mat   //��Ҫ�ȻҶȻ�
{
public:
	Mat(img_config &image,D3DCOLOR *surface);  //ת���ɾ���
private:
	void _conver_to_mat(D3DCOLOR *surface);
	int width;
	int height;
	unsigned char **main_mat;//������
	~Mat();
};

