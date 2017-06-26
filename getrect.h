void getrect(IplImage* pFrame1,int* rowlow,int* rowhigh,int* lineleft,int* lineright)
{
	int n,num,i,j,len,flag,row,line;
	row=len=line=0;
	*rowlow=*lineleft=1;
	*rowhigh=*lineright=300;
	
	//up-------------------------down
	for(i=pFrame1->height;i>0;i--)
	{
		n=0;
		num=0;
		for(j=1;j<pFrame1->widthStep;j++)
		{
			if((pFrame1->imageData[i*pFrame1->widthStep+j] && !pFrame1->imageData[n]) || 
				(!pFrame1->imageData[i*pFrame1->widthStep+j] && pFrame1->imageData[n]))
			{
				n=i*pFrame1->widthStep+j;
				num++;
			}
		}
		if(num>14 )
		{
			if((row-1)==i)
			{
				len++;
			}
			if(len==10)
			{
				*rowlow=i+10;
				flag=1;
			}
			row=i;
		}
		else
		{
			if(1==flag)
			{
				if(len>=20 )
				{
					*rowhigh=i;
					len=0;
					break;
				}
				len=0;
			}
		}
	}
	flag=0;
	//left------------------------right
	for(i=0;i<=(pFrame1->width/2);i++)
	{
		n=*rowhigh*pFrame1->widthStep+i;
		num=0;
		for(j=*rowhigh+1;j<=*rowlow;j++)
		{
			if( (pFrame1->imageData[j*pFrame1->widthStep+i] && !pFrame1->imageData[n]) ||
				(!pFrame1->imageData[j*pFrame1->widthStep+i] && pFrame1->imageData[n]))
			{
				n=j*pFrame1->widthStep+i;
				num++;
			}
		}
		if(num<8 )
		{
			if((line+1)==i)
			{
				len++;
			}
			if(len>30)
			{
				flag=1;
			}
			else flag=0;
			line=i;
		}
		else
		{
			if(1==flag)
			{
				if(len>30 )
				{
					*lineleft=i-5;
				}
			}
			len=0;
		}
	}
	flag=0;
	for(i=pFrame1->width;i>=(pFrame1->width/2);i--)
	{
		n=*rowhigh*pFrame1->widthStep+i;
		num=0;
		for(j=*rowhigh+1;j<=*rowlow;j++)
		{
			if( (pFrame1->imageData[j*pFrame1->widthStep+i] && !pFrame1->imageData[n]) ||
				(!pFrame1->imageData[j*pFrame1->widthStep+i] && pFrame1->imageData[n]))
			{
				n=j*pFrame1->widthStep+i;
				num++;
			}
		}
		if(num<8 )
		{
			if((line-1)==i)
			{
				len++;
			}
			if(len>30)
			{
				flag=1;
			}
			line=i;
		}
		else
		{
			if(flag==1)
			{
				if(len>30)
				{
					*lineright=i+5;
				}
			}
			len=0;
		}
	}
//	*rowlow=*rowlow-5;
//	*rowhigh=*rowhigh+5;
//	*lineleft=*lineleft+5;
//	*lineright=*lineright-5;
}
