#pragma once
#include"opencv/include/opencv2/ml.hpp"
#include "opencv/include/opencv2/core/core.hpp"
#include"opencv/include/opencv2/imgproc.hpp"
#include "opencv/include/opencv2/highgui/highgui.hpp"
#include"opencv/include/opencv2/objdetect.hpp"
#include "LibImport.h"

using namespace std;
//using namespace cv;
using namespace cv::ml;

//���ݼ�����
enum DatasetTypes
{
	DATASET_MNIST = 0,
	ENVI_IMAGEROI = 1,
	IMAGE_LIST	  = 3
};

//����ѧϰѵ���㷨
class CVMachineLearningTrain
{
public:
	//BP������ѵ��MNIST�Ⲣ��ѵ��������
	void CV_ANN_BP_Train(const char* pathDataset, const char* pathLabelSet, const char* pathNet, DatasetTypes datasetType);

	//SVM������
	void CV_SVM_Train(const char* pathDataset,double C, const char* pathLabelSet, const char* pathSVM, DatasetTypes datasetType);

	//logistic regression�߼��ع�ѵ����
	void CV_LogisticRegression_Train(const char* pathDataset, const char* pathLabelSet, const char* pathLogisticRegression, DatasetTypes datasetType);

	//AdaBoost�㷨
	void CV_AdaBoostTrain(const char* pathPosVec, const char* pathNegList, const char* pathAdaboost,int posNum,int negNum);
	
public:
	//��ȡѵ�����ݼ�
	void CV_GetMnistTrainData(const char* pathMnist,const char* pathLabel, cv::Mat &trianMat, cv::Mat &labelMat);
	//��ȡ����ʶ�����ݼ�
	void CV_GetVehicleTrainData(const char* pathDataset, cv::Mat &trainMat, cv::Mat &label);
	//��ȡѵ�����ݼ�
	//��������������
	void CV_HaarSampleDescriptor(const char* pathPosSampleList,const char* pathOutVec, int width, int height,int num );

};

//����ѧϰԤ���㷨
class CVMachineLearningPredict
{
public:
	//�����㷨��Mnist���ݽ���Ԥ��
	void CV_ANN_BP_PredictMnist(const char* pathPredict, const char* pathNet, const char* pathLabel = NULL);
	void CV_SVM_PredictMnist(const char* pathPredict, const char* pathSVM,const char* pathLabel=NULL);
	void CV_LogisticRegression_PredictMnist(const char* pathPredict, const char* pathLogisticRegression, const char* pathLabel = NULL);

	//svm�Գ������ݼ�����ʶ��
	void CV_SVM_PredictVehicle(const char* pathPredictImg, const char* pathSVM);
};