#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <string.h>

int main()
{
	int i,j,k,m,a,b,c,s,num1,num2;
	IplImage* pFrame = NULL;
	IplImage* pFrame1 = NULL;
	IplImage* pDest =NULL;
	CvSize dst_cvsize; //目标图像尺寸 
	char name[7][10]={"n1.jpg","n2.jpg","n3.jpg","n4.jpg","n5.jpg","n6.jpg","n7.jpg"};
	char namemodel[36][10]={"n10.jpg","n11.jpg","n12.jpg","n13.jpg","n14.jpg","n15.jpg","n16.jpg","n17.jpg","n18.jpg","n19.jpg"
		,"a.jpg","b.jpg","c.jpg","d.jpg","e.jpg","f.jpg","g.jpg","h.jpg","i.jpg","j.jpg","k.jpg"
		,"l.jpg","m.jpg","n.jpg","o.jpg","p.jpg","q.jpg","r.jpg","s.jpg","t.jpg","u.jpg","v.jpg"
		,"w.jpg","x.jpg","y.jpg","z.jpg"};
	char n[10]="n";
	cvNamedWindow("number1", 1);
	cvNamedWindow("number2", 1);
	for(i=2;i<7;i++)
	{
		s=b=c=0;
		pFrame=cvLoadImage(name[i],0);
		cvThreshold( pFrame, pFrame, 127,1, CV_THRESH_BINARY );   //大于127的都保持127，否则归0
/*	//	s=pFrame->height*pFrame->widthStep;
		s=num=0;
		cvThreshold( pFrame, pFrame, 127,1, CV_THRESH_BINARY );   //大于127的都保持127，否则归0
		for(j=0;j<pFrame->height;j++)
		{
			for(k=0;k<pFrame->widthStep;k++)
			{
				if( pFrame->imageData[j*pFrame->widthStep+k] == 1 )
					s++;
			}
		}
		for(j=0;j<pFrame->height-1;j++)
		{
			for(k=0;k<pFrame->widthStep;k++)
			{
				if( pFrame->imageData[j*pFrame->widthStep+k]+pFrame->imageData[(j+1)*pFrame->widthStep+k] == 2 )
					num++;
			}
		}
		printf("%d\n",num);
		s-=num;
		num=0;
		for(j=0;j<pFrame->height;j++)
		{
			for(k=0;k<pFrame->widthStep-1;k++)
			{
				if( pFrame->imageData[j*pFrame->widthStep+k]+pFrame->imageData[j*pFrame->widthStep+k+1] == 2 )
					num++;
			}
		}
		printf("%d\n",num);
		s-=num;
		num=0;
		for(j=0;j<pFrame->height-1;j++)
		{
			for(k=0;k<pFrame->widthStep-1;k++)
			{
				if( pFrame->imageData[j*pFrame->widthStep+k]+pFrame->imageData[(j+1)*pFrame->widthStep+k]+
					pFrame->imageData[(j+1)*pFrame->widthStep+k]+pFrame->imageData[(j+1)*pFrame->widthStep+k+1]== 4 )
					num++;
			}
		}
		printf("%d\n",num);
		s+=num;
		printf("%d\n",s);*/
		num1=num2=0;
		for(j=0;j<pFrame->height;j++)
		{
			num1+=pFrame->imageData[j*pFrame->widthStep+pFrame->widthStep/4];
			num2+=pFrame->imageData[j*pFrame->widthStep+pFrame->widthStep*3/4];
		}
		if(num1>num2)
		{
			if( (num1-num2)<num2/2 )
				s=1;
		}
		if(num2>=num1)
		{
			if( (num2-num1)<num1/2 )
				s=1;
		}
		num1=num2=0;
		for(j=0;j<pFrame->widthStep;j++)
		{
			num1+=pFrame->imageData[pFrame->widthStep/3*pFrame->widthStep+j];
			num2+=pFrame->imageData[pFrame->widthStep/3*2*pFrame->widthStep+j];
		}
		if(num1>num2)
		{
			if( (num1-num2)<num2/2 )
				s+=10;
		}
		if(num2>=num1)
		{
			if( (num2-num1)<num1/2 )
				s+=10;
		}
		num1=num2=0;
		for(j=pFrame->height*2/5;j<pFrame->height*3/5;j++)
		{
			num1+=pFrame->imageData[pFrame->widthStep/3*pFrame->widthStep+j];
		}
		if(num1<2 && s>=10)
		{
			s=1;
		}
		dst_cvsize.width = 40; //目标图像的宽为固定 40像素 
		dst_cvsize.height = 80;
		pDest = cvCreateImage( dst_cvsize, pFrame->depth, pFrame->nChannels); //构造目标图象 
		cvResize(pFrame, pDest, CV_INTER_LINEAR); //缩放源图像到目标图像 
		cvThreshold( pDest, pDest, 0,127, CV_THRESH_BINARY );   //大于127的都保持127，否则归0
		for(m=0;m<10;m++)
		{
		/*	switch(s)
			{
			case 0:  
				if(m==2 || m==4 || m==5 ||m==6 || m==7 || m==9)                                 //不对称2，4，5，6，7，9
				{
					goto lop;
				}
				goto lo; 
			case 1:printf("0\n");
				goto loop;
			case 10:   
				printf("3\n");//上下对称 3
				goto loop;
			case 11:        
				if( m==1 || m==8)//全对称0，1，8
				{
					goto lop;
				}
				goto lo;
			}//*/
lop:		a=0;
			num1=0;
			pFrame1=cvLoadImage(namemodel[m],0);
			//printf("%d %d\n",pFrame1->height,pFrame1->widthStep);
			cvThreshold( pFrame1, pFrame1, 127,127, CV_THRESH_BINARY ); 
			for(j=0;j<pDest->height;j++)
			{
				for(k=0;k<pDest->widthStep;k++)
				{
				//	printf("a:%d ",pDest->imageData[j*pDest->widthStep+k]);
				//	printf("b:%d ",pFrame1->imageData[j*pDest->widthStep+k]);
					if(pDest->imageData[j*pDest->widthStep+k]==pFrame1->imageData[j*pDest->widthStep+k]  && pDest->imageData[j*pDest->widthStep+k]==127)
					{
						a++;
					}
					if(pFrame1->imageData[j*pDest->widthStep+k]==127)
					{
						num1++;
					}
				}
			//	printf("\n");
			}
			a=a*10000/num1;
			if(a>c)
			{
				c=a;
				b=m;
			}
			printf("%d ",a);
		//	cvShowImage("number1", pDest);
		//	cvShowImage("number2", pFrame1);
lo:		;}
		printf("%d\n",b);
loop:	;//	cvWaitKey(0); 
		cvDestroyWindow("number1");
	//	cvDestroyWindow("number2");		
	}
	return 0;
}