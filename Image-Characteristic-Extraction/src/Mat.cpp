#include "Mat.h"
#include "dft.h"

Mat::Mat( img_config &image,  D3DCOLOR *surface): width(image.first), height(image.second),need_delete_mainmat(false)
{
	_conver_to_mat(surface);
}

Mat::Mat(double ** arr, int width_, int height_):width(width_),height(height_),need_delete_mainmat(false)
{
	main_mat = arr;   //非copy 
}

Mat::Mat(int width, int height) : width(width), height(height), need_delete_mainmat(true)
{
	main_mat = new double*[height];
	for (int i = 0; i < height; i++)
	{
		main_mat[i] = new double[width];
		for (int j = 0; j < width; j++)
		{
			main_mat[i][j] = 0;
			double a = main_mat[i][j];
			int ap=1;
		}
	}
	int b = main_mat[2][2];
	//this->show_main_mat();
	
}


 shared_ptr<D3DCOLOR> Mat::conver_to_d3dmat()
{
	
	std::shared_ptr<D3DCOLOR>d3d_surface(new D3DCOLOR[height*width + 1], std::default_delete<D3DCOLOR[]>());
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			unsigned char temppixel = main_mat[i][j];
		    d3d_surface.get()[i*width+j] = D3DCOLOR_XRGB(temppixel, temppixel, temppixel);
		}


	return d3d_surface;
	return nullptr;
}

 void Mat::show_ascii_art()
 {
	 const char ascii_table[11] = " .,:;ox%#@";
	

	 //char *buffer  = new char[ width*height+height+3];  //+height是 换行
	 char *buffer  = new char[width+1];  //+height是 换行

	 int ascii_table_len = strlen(ascii_table);
	 if (main_mat == nullptr) 
	{
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)L"NULLPTR(mat)",
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
		return;
	}

	 string show_mat = "";
	 FILE *fp = fopen("ascii_art.txt", "w");
	 FILE *test = fopen("test.txt", "w");
	 if (fp == nullptr||test== nullptr)
	 {
		 exit(1);
	 }
	

	 int buffer_index = 0;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				
				int index = ascii_table_len - ((int)((main_mat[i][j]) / 29))-2;
				/*if (index >= 10)index = 9;*/
				show_mat += ascii_table[index];             //show_mat 是messagebox试图打印的 ，但是有一些间距问题  暂时调整为输出txt
				buffer[j] = ascii_table[index];
				//buffer[buffer_index] = ascii_table[index];
				//buffer_index++;

				string a = std::to_string((int)main_mat[i][j]);
				fputs(a.c_str(), test);
				fputs(" ", test);

			}
		/*	buffer_index++;*/
			
			show_mat += "\n";
			fputs(buffer, fp);
			fputs("\n", fp);


			fputs("\n", test);

		}
		
		fclose(fp);
		fclose(test);


		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)show_mat.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

	 if (main_mat == nullptr)
	 {
		 int msgboxID = MessageBox(
			 NULL,

			 (LPCSTR)L"NULLPTR(mat)",
			 (LPCSTR)L"Account Details",
			 MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		 );
		 return;
	 }


 }

 void Mat:: _conver_to_mat(D3DCOLOR *surface)
{
	int n_piexls = width*height;   //定义全部像素
	//
	//for (int i = 0; i < n_piexls; i++)
	//{
	//	unsigned char  m = (unsigned char)(surface[i]&ANDD);
	//	if (m > 0)
	//	{
	//	}
	//}


	main_mat= new double*[height];  // 定义一个 用于处理的矩阵
	for (int i = 0; i < height; i++)   //将D3D换成mat矩阵 
	{
		main_mat[i] = new double[width];
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
void Mat::show_main_mat()    //调试 以messagebox形式打印矩阵 （应该还有更好的办法）
{   
	if (main_mat == nullptr) 
	{
		int msgboxID = MessageBox(
			NULL,

			(LPCSTR)L"NULLPTR(mat)",
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
		return;
	}

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
	if(need_delete_mainmat)
	delete main_mat;
	
}
f_2A_matrix<double> Mat::dft()
{
	f_1A_matrix<double> inputarray;
	f_2A_matrix<double> outputarray;
	f_1A_matrix<double> inversearray; //逆变换回后
	init_matrix(main_mat, this->height, this->width, inputarray);  //初始化矩阵

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
		int msgboxID2 = MessageBox(					//实部
			NULL,

			(LPCSTR)show_mat_real.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
		int msgboxID3 = MessageBox(					//虚部
			NULL,

			(LPCSTR)show_mat_img.c_str(),
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

	};

	//std::function<void (M2) > show_m2 = [&](M2 show_mat_) {};

	//测试 show array before dft
	//show_m1(inputarray);
	//
	
	dft_2d(inputarray, outputarray);         //转换后ouypuy矩阵为 要处理的矩阵
	return outputarray;
	//show_m2(outputarray);

	/*idft_2d(outputarray, inversearray);*/

	/*show_m1(inversearray);*/

	//测试 show array after dft
	//

	
	//测试 show array after idft

	//




}

D3DCOLOR * Mat::get_fourier_surface()
{
	//typedef f_2A_matrix<double> M2;
	//std::function<void(M2)> show_m2 = [&](M2 mat_) {
	//	string show_mat_real = "";
	//	string show_mat_img = "";
	//	for (int i = 0; i < height; i++)
	//	{
	//		for (int j = 0; j < width; j++)
	//		{
	//			show_mat_real += std::to_string(mat_[i][j].real) + " ";
	//			show_mat_img += std::to_string(mat_[i][j].img) + " ";
	//		}
	//		show_mat_real += "\n";
	//		show_mat_img += "\n";
	//	}
	//	int msgboxIDM2R = MessageBox(					//实部
	//		NULL,

	//		(LPCSTR)show_mat_real.c_str(),
	//		(LPCSTR)L"Account Details",
	//		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
	//	);
	//	int msgboxIDM2I = MessageBox(					//虚部
	//		NULL,

	//		(LPCSTR)show_mat_img.c_str(),
	//		(LPCSTR)L"Account Details",
	//		MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
	//	);

	//};


	typedef unsigned char** MA;
	std::function<void(MA)> show_mat = [&](MA mat_) {
		string show_mat_real = "";
	
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				show_mat_real += std::to_string(mat_[i][j]) + " ";
			}
			show_mat_real += "\n";
		
		}
		LPCSTR ma_content = (LPCSTR)show_mat_real.c_str();

		int msgboxIDMA = MessageBox(					//实部
			NULL,
			ma_content,
			(LPCSTR)L"Account Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

	};


	typedef  D3DCOLOR* MD;
	std::function<void(MD )> show_d3d = [&](MD mat_) {
		string show_mat_real = "";
		string show_mat_img = "";
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				show_mat_real += std::to_string(mat_[i*width+j]&ANDD) + " ";
			}
			show_mat_real += "\n";
		
		}
		int msgboxIDMD = MessageBox(					//实部
			NULL,
			(LPCSTR)show_mat_real.c_str(),
			(LPCSTR)L"Bccount Details",
			MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);

	};

	D3DCOLOR *fourier_surface=new D3DCOLOR[height*width+1];
	/*return nullptr;*/
	f_2A_matrix<double> mat = this->dft();  //效率有点低

	//show_m2(mat);

	unsigned char **temp=new unsigned char* [height];//test


	unsigned char temppixel;
	for (int i = 0; i < (this->height); i++)
	{
		temp[i] = new unsigned char[width];  //test

		for (int j = 0; j< (this->width); j++)
		{
			//temp[i][j] = abs(mat[i][j].img);  //test 频域 虚数部分 正数  ，暂时没取对数




			if (mat[i][j].img != 0)
			{
				temp[i][j] = (unsigned char)abs(log10(mat[i][j].img));
			}  //test 频域 虚数部分 正数  ，暂时没取对数
			else { temp[i][j] = 254; }


			//temppixel = (unsigned char)(abs(mat[i][j].img));  //未使用对数方法
			//temppixel = (unsigned char)(abs(log10(mat[i][j].img)));
		
				temppixel= (unsigned char)abs(log10(mat[i][j].img)*20);
			 //test 频域 虚数部分 正数  ，暂时没取对数
			

			//fourier_surface[i*width + j] = D3DCOLOR_ARGB(temppixel,temppixel, temppixel, temppixel); //
		
			fourier_surface[i*width + j] = D3DCOLOR_XRGB(temppixel, temppixel, temppixel);
		}
		
		
	}
	show_mat(temp);//test


	show_d3d(fourier_surface);

	return fourier_surface;
}
