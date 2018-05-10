#include "filter.h"
#include <typeindex>
#include <typeinfo>
#include <map>
#include <unordered_map>
struct affine_mat //���ڷ���任�ľ���
{
	double main_affine_mat[6] = { 0 };
	int width, height;
	explicit affine_mat() {

	}


	Mat* operator *( Mat *&main_mat)
	{
		
		int res_mat_height = height * 2;
		int res_mat_width = width * 2;
		Mat *test_res_mat = new Mat(res_mat_height,res_mat_width);   //���Ծ���
		
		for(int y=0;y<res_mat_height;y++)
			for (int x= 0; x < res_mat_width; x++)
			{

				int new_x = round((main_affine_mat[0] + main_affine_mat[1] + main_affine_mat[2])*(double)x);
				int new_y = round((main_affine_mat[3] + main_affine_mat[4] + main_affine_mat[5])*(double)y);
				
				(*test_res_mat)[new_x][new_y] = (*main_mat)[y][x];
			}
		return test_res_mat;
	}
	virtual ~affine_mat() {};   
};





struct rotate_affine_mat:public affine_mat
{
	explicit rotate_affine_mat(double theta,double ) {
		main_affine_mat[4]=main_affine_mat[0] = cos(theta);
		main_affine_mat[3] = sin(theta);
		main_affine_mat[1] = -1 * main_affine_mat[3]; //-sin(theata);
	}
	~rotate_affine_mat() {};
};


enum AFFINE_TYPE { ROTATE = 1 };

class transform 
{
public:
	enum OP_TYPE { SCHARR_OP = 1, PREWITT_OP = 2 }; //������������ scharr  prewitt
	void canny(double threshod1,double threshod2, int size=3);  //sizeΪsobel�׾���С
	//�Զ��������� sobel���ɻ�ûд ��
	Mat* sobel(int dx, int dy, int size, bool type = 1);
	Mat* laplacian(int ksize, double scale);
	
	//ģ�����ӣ������ӹ�������
	Mat* sobel(bool type=1);
	Mat* laplacian();
	Mat* treshold(int tresh);   //��ֵ���� ȫ����ֵ �Զ���Ĵ�ʵ��

	Mat* scharr();
	Mat* prewitt();

	Mat* op(pair<kernel*,kernel*>kernel_,bool type);  //��������


	 Mat *affine(AFFINE_TYPE type, int para1, int para2)
	{
		std::unordered_map < AFFINE_TYPE, type_index> affine_chart;
		//affine_chart[ROTATE] = typeid(rotate_affine_mat);  //�˾���׳�error ����map��Ƶߵ� ����insert
		
		//affine_chart.insert(make_pair(ROTATE, typeid(rotate_affine_mat))); �˾���׳�error
		//affine_chart.try_emplace(make_pair(ROTATE, typeid(rotate_affine_mat)));
		affine_chart.emplace(make_pair(ROTATE, typeid(rotate_affine_mat)));


		//affine_<affine_chart[type]>(type, para1, para2); û������ һ�ι��ڴ�����̬����ʧ�ܵĳ���



		if (affine_chart[type] == typeid(rotate_affine_mat))
		{

			return affine_<rotate_affine_mat>(type, para1, para2);

		}


		return nullptr;

	};
	template<typename T>
	Mat* affine_(AFFINE_TYPE type,int parax,int para2);   //����任


	Mat* hough_transform(double rho,int r_tresh, bool is_binary_mat);             //����任 ����Ϊ��Ҫ�ȶ�ֵ��  Ĭ��Ϊ�Ѿ���ֵ��



	explicit transform(Mat* &main_mat_r);
	~transform();
	int width, height;
	Mat *main_mat;
private:
	

	pair<kernel*, kernel*> get_sobel(int size);//��ȡsobel���� Ĭ�ϵ�sobel����
	kernel* get_laplacian(int mask_type=1);//��ȡ����������,Ĭ����ģΪ1���͵�����

	pair<kernel*, kernel*> get_sobel(int dx, int dy, int size);//�Զ����soble�ں� dx dy�ֱ��ʾx y�ϵĲ�ֽ���
	kernel* get_laplacian(int ksize,double scale);//ksize ���ڼ�����׵��˲����׾��ߴ磬scale��ʾ��ѡ�������� 



	//������������

	pair<kernel*, kernel*>get_op(OP_TYPE type);   //��ȡ����

	//pair<kernel*, kernel*> get_scharr();
	//pair<kernel*, kernel*> get_prewitt();
};


