
#include <stdio.h>

#include "haralick.h"


void CalculateCoocurrenceMatrix ( void )
{
	int x, y;
	int d=1; //거리
	for (y = 0; y<img_height; y++)
	{
		for(x= 0; x <img_width; x++ )
		{
			//	printf("%d\n",y);
			UpdatePixel ( x, y, x-d, y-d );
			UpdatePixel ( x, y, x, y-d );
			UpdatePixel ( x, y, x+d, y-d );
			UpdatePixel ( x, y, x-d, y );
			UpdatePixel ( x, y, x+d, y );
			UpdatePixel ( x, y, x-d, y+d );
			UpdatePixel ( x, y, x, y+d );
			UpdatePixel ( x, y, x+d, y+d );
		}
	}
	for(int i=0; i<256; i++)
	{
		for(int j=0; j<256; j++)
		{
			normal = normal+m_COM[i][j]; 
		}
	}
	
	
	for (int i=0;i<256;i++)
		for(int j=0;j<256;j++)
			m_COM [i][j] = m_COM [i][j]/normal ;

	int i, j;
	for ( i = 0; i <256; i++ )
	{
		for( j = 0; j <256; j++ )
		{
			m_fEnergy += m_COM [i][j]* m_COM [i][j]; 
			m_fContrast += ((i-j)*(i-j))* m_COM [i][j]; 
			m_fHomogeneity += m_COM [i][j ]/(1+(i-j)*(i-j)); 
			if( m_COM [i][j] != 0 )
				m_fEntropy += m_COM [i][j]* log( m_COM [i][j]) ;
			uy= uy + j* m_COM [i][j]; 
			pxy [i+j] += m_COM [i][j]; 
			if (i >=j) pdxy [i-j] += m_COM [i][j]; 
			else pdxy [j-i] += m_COM [i][j];
			px[i] += m_COM [i][j];
		}
	}
	for ( i = 0; i <256; i++ )
	{
		for( j = 0; j <256; j++ )
		{
		
			stdDevix += ((i-ux)*(i-ux)* m_COM [i][j]);
			stdDeviy += ((j-uy)*(j-uy)* m_COM [i][j]);
			m_fVariance += (i-ux)*(i-ux)* m_COM [i][j];
		}

		if( px[i] != 0 ) hx = hx + px[i]* log(px[i]);

		DiffAver = DiffAver + i* pdxy [i];
		m_fSumAver += (2*i)*pxy [2*i] ;
		m_fSumAver += (2*i+1)*pxy [2*i+1] ;

		if( pxy [2*i ]!= 0 )
			m_fSumEntr += pxy [2*i]* log(pxy [2*i]); 
		if( pxy [2*i +1]!= 0 )
			m_fSumEntr += pxy [2*i +1]* log(pxy [2*i +1]) ;
		if( pdxy [i] != 0 )
			m_fDiffEntr += pdxy [i]* log( pdxy [i]); 

	}
	for( i = 0; i < 256; i++ )
	{
		for ( j = 0; j < 256; j++) 
		{
			m_fCorrelation +=((i-ux)*(j-ux)* m_COM [i][j]) /( stdDevix * stdDevix );
			if (( px[i ]!= 0) &&( px[j ]!= 0))
			{
				hxy1 += m_COM [i][j]* log(px[i]* px[j]);
				hxy2 += px[i]* px[j]* log(px[i]* px[j]);
			}
		}
		m_fSumVri +=(2*i- m_fSumAver ) *(2*i- m_fSumAver )*pxy [2*i];
		m_fSumVri +=(2* i+1- m_fSumAver ) *(2* i+1- m_fSumAver )*pxy [2*i +1];
		m_DiffVari +=(i- DiffAver )*(i- DiffAver )* pdxy [i ];
	}
	hxy1 = -hxy1 ;
	hxy2 = -hxy2 ;
	m_flnMeaCor1 = ( m_fEntropy - hxy1 )/hx; 
	m_flnMeaCor2 = sqrt (1- exp ( -2*( hxy2 - m_fEntropy ))); 
}
void inline UpdatePixel ( int x1 , int y1 , int x2 , int y2)
{
	
	if( x2 < 0 || x2 >= ( int) img_width
		|| y2 < 0|| y2 >= ( int) img_height)
		return ;

	unsigned char pixel , neighbour ;
	pixel = img_gray->imageData [y1*img_width+x1 ];
	neighbour = img_gray->imageData [y2*img_width+x2 ];
	m_COM [ pixel ][ neighbour ] += 1 ;

}
void haralick(IplImage* inputimage)
{	
	int normal=0;	
	img_gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	cvCvtColor(image, img_gray,CV_RGB2GRAY);
	
	CalculateCoocurrenceMatrix();
	printf("%f, %f, %f, %f",m_fEntropy, m_fEnergy, m_fContrast,m_fVariance);
	cvReleaseImage(&img_gray);
}

int main() 
{
	FILE *file = fopen("test1.txt","a+");
	
	image = cvLoadImage("sea-03.jpg");
	img_width = image->width;
	img_height = image->height;
	haralick(image);

	fprintf(file,"%f, %f, %f, %f \n",m_fEntropy, m_fEnergy, m_fContrast,m_fVariance);
	
	fclose(file);
	
	system("pause");
	
	cvReleaseImage(&image);
	return 0;
}
