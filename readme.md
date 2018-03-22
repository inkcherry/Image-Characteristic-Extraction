######以学习和实现目的的简单图像处理库，使用directx作为显示以及调试手段

##实现算法
* 基本
    * bmp位图读取（位深度4、24、32）  
    * D3DCOLOR（显示矩阵）与Mat（运算矩阵）转换
    * 灰度化
* 变换  
    * 傅里叶变换dft  
    * 傅里叶逆变换idft
    * 傅里叶频谱显示  
* 滤波  
    * 线性滤波  
        * 方框滤波
        * 均值滤波
        * 高斯滤波
    * 非线性滤波  
        * 中值滤波
        * 双边滤波
* 形态学
    * 膨胀
    * 腐蚀
    * 开运算
    * 闭运算
    * 形态学梯度
    * 顶帽 
    * 黑帽