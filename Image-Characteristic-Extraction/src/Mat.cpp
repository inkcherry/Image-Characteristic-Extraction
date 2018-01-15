#include "Mat.h"
#include "dft.h"

Mat::Mat( img_config &image,  D3DCOLOR *surface): width(image.first), height(image.second)
{
	_conver_to_mat(surface);
}


void Mat:: _conver_to_mat(D3DCOLOR *surface)
{
	int n_piexls = width*height;   //����ȫ������
	//
	//for (int i = 0; i < n_piexls; i++)
	//{
	//	unsigned char  m = (unsigned char)(surface[i]&ANDD);
	//	if (m > 0)
	//	{
	//	}
	//}


	main_mat= new unsigned char*[height];  // ����һ�� ���ڴ���ľ���
	for (int i = 0; i < height; i++)   //��D3D����mat���� 
	{
		main_mat[i] = new unsigned char[width];
		for (int j = 0; j < width; j++)
		{
			//zhelijiang d3dcolor fanyichengzhongwen
		/*	unsigned long m = surface[i+width*j]>>24;
			int k = (unsigned char)(surface[i*width + j] >> 24);*/
			main_mat[i][j] = (unsigned char)(surface[i*width + j] & ANDD);
			//main_mat[i][j] = 0;   //test
		}

	}

	
	

}
void Mat::show_main_mat()    //���� ��messagebox��ʽ��ӡ���� ��Ӧ�û��и��õİ취��
{
	string show_mat = "";
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			show_mat += std::to_string(main_mat[i][j]) + " ";
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
Mat::~Mat()
{
	delete main_mat;
}
void Mat::dft()
{
	f_1A_matrix<double> inputarray;
	f_2A_matrix<double> outputarray;
	f_1A_matrix<double> inversearray; //��任�غ�
	init_matrix(main_mat, this->height, this->width, inputarray);  //��ʼ������

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			int k = inputarray[i][j];
			if (k > 0)
				std::cout <<k;   //test
		}
	typedef f_1A_matrix<double> M1;
	typedef f_2A_matrix<double> M2;



	std::function<void(M1)> show_m1 = [&](M1 mat_) {
		string show_mat = "";
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				show_mat += std::to_string(mat_[i][j]) + " ";
			}
			show_mat += "\n";

		}
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)show_mat.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
	
	};

	std::function<void(M2)> show_m2 = [&](M2 mat_) {
		string show_mat_real = "";
		string show_mat_img = "";
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				show_mat_real += std::to_string(mat_[i][j].real) + " ";
				show_mat_img += std::to_string(mat_[i][j].img) + " ";
			}
			show_mat_real += "\n";
			show_mat_img += "\n";
		}
		int msgboxID2 = MessageBox(					//ʵ��
			NULL,

			(LPCSTR)show_mat_real.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
		int msgboxID3 = MessageBox(					//�鲿
			NULL,

			(LPCSTR)show_mat_img.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

	};

	//std::function<void (M2) > show_m2 = [&](M2 show_mat_) {};

	//���� show array before dft
	show_m1(inputarray);
	//
	
	dft_2d(inputarray, outputarray);         //ת����ouypuy����Ϊ Ҫ����ľ���
	show_m2(outputarray);
	idft_2d(outputarray, inversearray);
	show_m1(inversearray);

	//���� show array after dft
	//

	
	//���� show array after idft

	//




}