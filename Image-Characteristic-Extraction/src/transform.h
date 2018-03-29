#include "filter.h"

class transform 
{
public:
	void canny(double threshod1,double threshod2, int size=3);  //sizeΪsobel�׾���С
	//�Զ���������
	Mat* sobel(int dx, int dy, int size, bool type = 1);
	Mat* laplacian(int ksize, double scale);
	//ģ�����ӣ������ӹ�������
	Mat* sobel(bool type=1);
	Mat* laplacian();


	explicit transform(Mat* &main_mat_r);
	~transform();
	int width, height;
	Mat *main_mat;
private:

	pair<kernel*, kernel*> get_sobel(int size);//��ȡsobel���� Ĭ�ϵ�sobel����
	kernel* get_laplacian(int mask_type=1);//��ȡ����������,Ĭ����ģΪ1���͵�����

	pair<kernel*, kernel*> get_sobel(int dx, int dy, int size);//�Զ����soble�ں� dx dy�ֱ��ʾx y�ϵĲ�ֽ���
	kernel* get_laplacian(int ksize,double scale);//ksize ���ڼ�����׵��˲����׾��ߴ磬scale��ʾ��ѡ��������
};


