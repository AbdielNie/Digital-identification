#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "getrect.h"

void getnumber()
{
	int n,num,i,j,k,len,line,flag,x;
	IplImage* pFrame = NULL;
	IplImage* pFrame1 = NULL;
	CvSize size;
	IplImage* pDest =NULL;
	char name[7][10]={"n1.jpg","n2.jpg","n3.jpg","n4.jpg","n5.jpg","n6.jpg","n7.jpg"};
	k=num=n=flag=j=len=x=0;
	line=-1;

	pFrame=cvLoadImage("111.jpg",0);
	pFrame1=cvLoadImage("111.jpg",0);
	cvThreshold( pFrame, pFrame, 127,1, CV_THRESH_BINARY );
	//	cvThreshold( pFrame, pFrame ,180, 260, CV_THRESH_BINARY ); 
	//	cvCanny(pFrame, pFrame, 225, 320, 3 );                  //��Ե���
	printf("%d",pFrame->width);
	for(i=0;i<pFrame->width;i++)
	{
		for(j=0;j<pFrame->height;j++)
		{
			num+=pFrame->imageData[j*pFrame->widthStep+i];
		}
		if(num>4)
		{
			if( (line+1) == i )
			{
				len++;
			}
			if( len > (pFrame->width/11) )
			{
				n=i-len;
				flag=1;
			}
			line=i;
		}
		else
		{
			if(flag==1)
			{
				k=i-1;
				flag=0;
			}
			else
			{
				len=0;
			}
		}
		if(k!=0)
		{
			cvLine( pFrame1, cvPoint(n,0), cvPoint(n,pFrame->height), cvRealScalar(145 ),1, 8, 0 );
			cvLine( pFrame1, cvPoint(k,0), cvPoint(k,pFrame->height), cvRealScalar(145 ),1, 8, 0 );
			size= cvSize(k-n+1,pFrame->height);//�����С
			cvSetImageROI(pFrame1,cvRect(n,0,size.width, size.height));//����Դͼ��ROI
			pDest = cvCreateImage(size,pFrame->depth,pFrame->nChannels);//����Ŀ��ͼ��
			cvCopy(pFrame1,pDest,NULL); //����ͼ��
			cvResetImageROI(pFrame1);//Դͼ����������ROI
			cvSaveImage(name[x++],pDest);//����Ŀ��ͼ��
			k=0;
		}

		printf("%d ",num);
		num=0;
	}	
	cvNamedWindow("number", 1);
	cvShowImage("number", pFrame1);
	cvWaitKey(0); 
	cvDestroyWindow("video");
	
}


int main(int argc,char **argv)
{
	int rowlow,rowhigh;
	int lineleft,lineright;
	CvSize size;
	IplImage* pFrame = NULL;
	IplImage* pFrame1 = NULL;
	IplImage* pDest =NULL;
	pFrame=cvLoadImage("3.jpg",0);
		cvNamedWindow("video1", 1);
		cvShowImage("video1", pFrame);
		cvWaitKey(0); 
		cvDestroyWindow("video1");
	pFrame1 = cvCreateImage(cvGetSize(pFrame),IPL_DEPTH_8U,1); 
	cvCanny(pFrame, pFrame1, 225, 320, 3 );                  //��Ե���
	getrect(pFrame1,&rowlow,&rowhigh,&lineleft,&lineright);  //��λ����
	cvRectangle( pFrame1, cvPoint(lineleft,rowhigh ), cvPoint(lineright,rowlow), cvRealScalar(245 ), 2, 8, 0 );
	
	size= cvSize(lineright-lineleft,rowlow-rowhigh);//�����С
	cvSetImageROI(pFrame,cvRect(lineleft,rowhigh,size.width, size.height));//����Դͼ��ROI
	pDest = cvCreateImage(size,pFrame->depth,pFrame->nChannels);//����Ŀ��ͼ��
	cvCopy(pFrame,pDest,NULL); //����ͼ��
	cvResetImageROI(pFrame);//Դͼ����������ROI
	cvSaveImage("111.jpg",pDest);//����Ŀ��ͼ��
	
	getnumber();
		cvNamedWindow("video", 1);
		cvShowImage("video", pFrame1);
		cvWaitKey(0); 
		cvDestroyWindow("video");
	cvReleaseImage(&pFrame1); 
	return 0;
}