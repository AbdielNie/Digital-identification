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
	CvSize dst_cvsize; //目标图像尺寸 
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

log2:		size= cvSize(pFrame->width,b-a+1);//区域大小
		cvSetImageROI(pFrame1,cvRect(0,a,size.width, size.height));//设置源图像ROI
		pFrame_d = cvCreateImage(size,pFrame->depth,pFrame->nChannels);//创建目标图像
		cvCopy(pFrame1,pFrame_d,NULL); //复制图像
		cvResetImageROI(pFrame1);//源图像用完后，清空ROI


		dst_cvsize.width = 40; //目标图像的宽为固定 100 像素 
		dst_cvsize.height = 80; // 高同比例放大 
		pDest = cvCreateImage( dst_cvsize, pFrame->depth, pFrame->nChannels); //构造目标图象 
		cvResize(pFrame_d, pDest, CV_INTER_LINEAR); //缩放源图像到目标图像 
		cvSaveImage(name[i],pDest);//保存目标图像
		cvReleaseImage(&pDest);
	}
}
