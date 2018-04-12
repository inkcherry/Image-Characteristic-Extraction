#include"bitmap.h"
#include<stdio.h>
#include<assert.h>
#include<math.h>


void LoadBmp(img_config&config, D3DCOLOR*surfacee,std::string src)  //32λbmpͼ��
{  
	FILE  *bmpFile = fopen(src.c_str(), "rb");
	
	char signature[2];
	
	fread(&signature, sizeof(char), 2, bmpFile);
	

	BitmapFileHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	BitmapInfoHeader infoHeader;
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);
	
	fseek(bmpFile, fileHeader.offset, SEEK_SET);
	infoHeader.width = abs(infoHeader.width);
	infoHeader.height = abs(infoHeader.height);
	
	config.first = infoHeader.width;
	config.second = infoHeader.height;

	int nPixels = infoHeader.width*infoHeader.height;  //ͼ���������
	if (infoHeader.bits == 32)
	{
		for (int y = infoHeader.height - 1; y >= 0; y--)
		{
			for (int x = 0; x < infoHeader.width; x++)
			{
				Piexl32 pixel;
				fread(&pixel, sizeof(pixel), 1, bmpFile);
				//surface[x+y*infoHeader.width] = D3DCOLOR_XRGB(pixel.red, pixel.green, pixel.blue);
				surfacee[x + y*infoHeader.width] = D3DCOLOR_ARGB(pixel.alpha, pixel.red, pixel.green, pixel.blue);

			}
		}
	}
	else if (infoHeader.bits == 24)
	{
		int nBytesPerRow = infoHeader.width * 3;
		int nPaddingByresPerRow = (4 - (nBytesPerRow % 4))%4;   
		for (int y = infoHeader.height - 1; y >= 0; y--)       //bmp�ļ����Ե����ϴ洢������Ϣ   {  
		{
			for (int x = 0; x < infoHeader.width; x++)
			{
				Piexl24 pixel;                         //Piexl24Ϊ 3��unsigned char�����Ľṹ��  
				fread(&pixel, sizeof(pixel), 1, bmpFile);
				//surface[x+y*infoHeader.width] = D3DCOLOR_XRGB(pixel.red, pixel.green, pixel.blue);  
				surfacee[x + y*infoHeader.width] = D3DCOLOR_XRGB(pixel.red, pixel.green, pixel.blue);
			}
			fseek(bmpFile, nPaddingByresPerRow, SEEK_CUR);
		}
	}
	fclose(bmpFile);
}

void LoadBmp4(D3DCOLOR **surfacee, std::string src)  //4λbmpͼ��
{
	RGBQUAD ColorPla[256];
	FILE  *bmpFile = fopen(src.c_str(), "rb");

	char signature[2];
	fread(&signature, sizeof(char), 2, bmpFile);


	BitmapFileHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, bmpFile);
	BitmapInfoHeader infoHeader;
	fread(&infoHeader, sizeof(infoHeader), 1, bmpFile);
	for (unsigned int nCounti = 0; nCounti < infoHeader.ncolours; nCounti++)  //��ȡ��ɫ��
	{
		fread((char *)&(ColorPla[nCounti].rgbBlue), 1, sizeof(BYTE), bmpFile);
		fread((char *)&(ColorPla[nCounti].rgbGreen), 1, sizeof(BYTE), bmpFile);
		fread((char *)&(ColorPla[nCounti].rgbRed), 1, sizeof(BYTE), bmpFile);
		fread((char *)&(ColorPla[nCounti].rgbReserved), 1, sizeof(BYTE), bmpFile);
	}
	infoHeader.width = abs(infoHeader.width);
	infoHeader.height = abs(infoHeader.height);
	fclose(bmpFile);
}