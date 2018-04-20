#include "filter.h"

class transform 
{
public:
	enum OP_TYPE{SCHARR_OP=1,PREWITT_OP=2}; //������������ scharr  prewitt

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



	Mat* hough_transform(double theta_length_ ,double r_length_,int tresh , bool is_binary_mat);             //����任 ����Ϊ��Ҫ�ȶ�ֵ��  Ĭ��Ϊ�Ѿ���ֵ��



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


