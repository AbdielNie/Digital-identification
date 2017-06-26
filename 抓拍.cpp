#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

int main()
{
	IplImage* pFrame = NULL; 
	CvCapture* pCapture = NULL;
	
	//��������
	cvNamedWindow("video", 1);
	cvMoveWindow("video", 30, 0);	
	
	if( !(pCapture = cvCaptureFromCAM(-1)))
	{
		fprintf(stderr, "Can not open camera.\n");
		return -2;
	}
	pFrame = cvQueryFrame( pCapture );
	cvShowImage("video", pFrame);
	cvSaveImage("1.jpg", pFrame);//��ͼ��д���ļ�
	cvWaitKey(0); 
		
	//���ٴ���
	cvDestroyWindow("video");
	
	//�ͷ�ͼ��;���	
	cvReleaseCapture(&pCapture);	
	return 0;
}