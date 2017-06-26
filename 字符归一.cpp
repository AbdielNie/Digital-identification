#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

int main()
{
	int i,j,k,num,flag,a,b,c,d;
	IplImage* pFrame = NULL;
	IplImage* pFrame1 = NULL;
	IplImage* pFrame_d = NULL;
	IplImage* pDest =NULL;
	CvSize dst_cvsize; //Ŀ��ͼ��ߴ� 
	CvSize size;
	char name[7][10]={"n1.jpg","n2.jpg","n3.jpg","n4.jpg","n5.jpg","n6.jpg","n7.jpg"};
	num=flag=a=0;
	for(i=0;i<7;i++)
	{
			pFrame=cvLoadImage(name[i],0);
			pFrame1=cvLoadImage(name[i],0);
		cvThreshold( pFrame, pFrame, 127,1, CV_THRESH_BINARY );
		b=pFrame->height;
		for(j=3;j<pFrame->height;j++)
		{
			for(k=0;k<pFrame->widthStep;k++)
			{
				num+=pFrame->imageData[j*pFrame->widthStep+k];
				printf("%d ",pFrame->imageData[j*pFrame->widthStep+k]);
			}
			printf("\n");
			if(num>4)
			{
				a=j;
				num=0;
				goto log1;
			}
			num=0;
		}
log1:		for(j=pFrame->height-2;j>0;j--)
		{
			for(k=0;k<pFrame->widthStep;k++)
			{
				num+=pFrame->imageData[j*pFrame->widthStep+k];
				printf("%d ",pFrame->imageData[j*pFrame->widthStep+k]);
			}
      			if(num>4)
			{
				b=j;
				goto log2;
			}
			printf("\n");
			num=0;
		}

log2:		size= cvSize(pFrame->width,b-a+1);//�����С
		cvSetImageROI(pFrame1,cvRect(0,a,size.width, size.height));//����Դͼ��ROI
		pFrame_d = cvCreateImage(size,pFrame->depth,pFrame->nChannels);//����Ŀ��ͼ��
		cvCopy(pFrame1,pFrame_d,NULL); //����ͼ��
		cvResetImageROI(pFrame1);//Դͼ����������ROI


		dst_cvsize.width = 40; //Ŀ��ͼ��Ŀ�Ϊ�̶� 100 ���� 
		dst_cvsize.height = 80; // ��ͬ�����Ŵ� 
		pDest = cvCreateImage( dst_cvsize, pFrame->depth, pFrame->nChannels); //����Ŀ��ͼ�� 
		cvResize(pFrame_d, pDest, CV_INTER_LINEAR); //����Դͼ��Ŀ��ͼ�� 
		cvSaveImage(name[i],pDest);//����Ŀ��ͼ��
		cvReleaseImage(&pDest);
	}
}
