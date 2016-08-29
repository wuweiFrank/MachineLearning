#include "stdafx.h"
#include <io.h>
#include <fstream>
#include "mnistFile.h"
#include "opencv/include/opencv2/highgui.hpp"
#include "opencv/include/opencv2/core.hpp"

using namespace std;
using namespace cv;
#pragma warning(disable : 4996)

//trans the image buffer from high level to low level
//only deal with 4 BYTEs data
void mnistFile::swapBuffer(char* buf)
{
	char temp;
	temp = *(buf);
	*buf = *(buf+3);
	*(buf+3) = temp;

	temp = *(buf+1);
	*(buf+1) = *(buf+2);
	*(buf+2) = temp;
}

/*trans mnist file to bmp file in dir of bmpDir
  get the link of label with the image
  so that in train process the image can be distinguished*/
long mnistFile::MnistToBmp(char* mnistPath,char* bmpDir,char* labelPath,char* link,int num/*=0*/)
{
	//Open image and label file
	ifstream lab_ifs(labelPath, ios_base::binary);
	ifstream ifs(mnistPath, ios_base::binary);
	ofstream ofs_link(link,ios_base::out);

	if( ifs.fail() == true )
		return -1;
	if( lab_ifs.fail() == true )
		return -1;
	if(ofs_link.is_open()!=true)
		return -1;

	char magicNum[4], ccount[4], crows[4], ccols[4];
	ifs.read(magicNum, sizeof(magicNum));ifs.read(ccount, sizeof(ccount));
	ifs.read(crows, sizeof(crows));ifs.read(ccols, sizeof(ccols));

	int count, rows, cols;
	swapBuffer(ccount);swapBuffer(crows);swapBuffer(ccols);
	memcpy(&count, ccount, sizeof(count));
	memcpy(&rows, crows, sizeof(rows));
	memcpy(&cols, ccols, sizeof(cols));

	//Just skip label header
	lab_ifs.read(magicNum, sizeof(magicNum));
	lab_ifs.read(ccount, sizeof(ccount));
	int intmagicNum, ccountint;
	swapBuffer(magicNum);swapBuffer(ccount);
	memcpy(&intmagicNum, magicNum, sizeof(magicNum));
	memcpy(&ccountint, ccount, sizeof(ccount));

	//image data of cols and rows 
	unsigned char* dataImage=new unsigned char[cols*rows];
	
	char label = 0;		//number label
	int total = 0;		//deal with image
	char bmpImagePath[256];
	
	ofs_link<<"bmp path dir is- "<<bmpDir<<endl;
	ofs_link<<"Name     "<<"Label  "<<endl;
	if(num==0)
		num=count;
	while(!ifs.eof())
	{
		total++;
		if(total>num)
			break;

		printf("\rtotal handle image of %d",total);
		//Read label
		lab_ifs.read(&label, 1);
		label = label + '0';
		ofs_link<<total<<".bmp   "<<label<<endl;

		//Read source data
		ifs.read((char*)dataImage, rows * cols);
		//image path
		sprintf(bmpImagePath,"%s\\%d.bmp",bmpDir,total);
		Mat img(cols,rows,CV_8UC1);
		img.data=dataImage;
		imwrite(bmpImagePath,img);
	}
	printf("\n");

	ifs.close();
	lab_ifs.close();
	ofs_link.close();
	delete[]dataImage;
	return 0;
}

//this is the test funtion
void mnistFile::mnist_func_test()
{
	char* bmphDir  ="H:\\程序备份\\代码备份\\libProject\\typetrans\\typetrans\\mnist\\bmp";
	char* pathmnist="H:\\程序备份\\代码备份\\libProject\\typetrans\\typetrans\\mnist\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte";
	char* pathlabel="H:\\程序备份\\代码备份\\libProject\\typetrans\\typetrans\\mnist\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte";
	char* pathLink ="H:\\程序备份\\代码备份\\libProject\\typetrans\\typetrans\\mnist\\link.txt";
	
	MnistToBmp(pathmnist,bmphDir,pathlabel,pathLink);

}