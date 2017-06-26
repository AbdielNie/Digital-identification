#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

int main()
{
	IplImage* pFrame = NULL; 
	CvCapture* pCapture = NULL;
	
	//创建窗口
	cvNamedWindow("video", 1);
	cvMoveWindow("video", 30, 0);	
	
	if( !(pCapture = cvCaptureFromCAM(-1)))
	{
		fprintf(stderr, "Can not open camera.\n");
		return -2;
	}
	pFrame = cvQueryFrame( pCapture );
	cvShowImage("video", pFrame);
	cvSaveImage("1.jpg", pFrame);//把图像写入文件
	cvWaitKey(0); 
		
	//销毁窗口
	cvDestroyWindow("video");
	
	//释放图像和矩阵	
	cvReleaseCapture(&pCapture);	
	return 0;
}