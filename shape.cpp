#include "shape.h"

void detect_edge(IplImage *in, IplImage *out, Point p)
{
	//CvtGray(in, out);
	IplImage *gray = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 1);
	IplImage *merge = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);
	double r, g, b;
	
	//canny edge
	cvCvtColor(in, gray, CV_BGR2GRAY);
	cvCanny(gray, gray, 200, 200, 3);
	cvMerge(gray, gray, gray, NULL, out);


	//extracted pixels counting
	int count = 0;
	for(int w = 0; w < out->width; w++)
	{
		for(int h = 0; h < out->height; h++)
		{			
			b = ((unsigned char)(out->imageData[w*3 +h*out->widthStep])) / 255;
			g = ((unsigned char)(out->imageData[w*3 +h*out->widthStep+1])) / 255;
			r = ((unsigned char)(out->imageData[w*3 +h*out->widthStep+2])) / 255;

			if(b == 1 && g == 1 && r == 1)
			{
				count++;
			} 
		}
	}
	
	int *x; 	x = new int[count];
	int *y; 	y = new int[count];
	
	//printf("ÁÂÇ¥°ª : %d, %d\n", in->width, in->height);


	//extracted pixel 
	int index = 0;
	for(int w = 0; w < out->width; w++)
	{
		for(int h = 0; h < out->height; h++)
		{
			b = ((unsigned char)(out->imageData[w*3 +h*out->widthStep+0])) / 255;
			g = ((unsigned char)(out->imageData[w*3 +h*out->widthStep+1])) / 255;
			r = ((unsigned char)(out->imageData[w*3 +h*out->widthStep+2])) / 255;

			if(b == 1 && g == 1 && r == 1)
			{
				//printf("%d: (%d	%d)\n",index, w, h);
				x[index] = w;
				y[index] = h;
				index++;				
			}
		}
	}


	//fiding centroid of extracted pixels
	int sumX = 0;
	int sumY = 0;
	for(int i = 0; i < count; i++)
	{
		sumX += x[i];
		sumY += y[i];
	}
	sumX = sumX / count;
	sumY = sumY / count;
	//printf("%d	%d\n", sumX, sumY);
	
	//computing the distance of each pixel from centroid
	double *dist; 	dist = new double[count];
	for(int i = 0; i < count; i++)
	{
		dist[i] = distance(x[i], y[i], sumX, sumY);	
		//printf("%d: %d\n", i, dist[i]);
	}

	//Fourier transformed coefficients
	double *fourier; fourier = new double[count];
	fourier2(dist, fourier, count);


	//fourier(dist, inimag, outreal, count);	
	//for(int i = 0; i < count; i++)
	//{
	//	printf("%d: %.2f\n", i, fourier[i]);
	//}
	//printf("fourier: %.2f\n", outreal[0]);
	//printf("fourier: %.2f		%.2f\n", outreal[0], outimag[0]);



	//Standardize fourier coefficients
	double *stand;	stand = new double[count];
	for(int i = 0; i < count; i++)
	{
		stand[i] = ABSOLUTE(fourier[i] / fourier[0]);
		//printf("%d: %.2f\n", i, stand[i]);
	}
	p.n = count;
	p.arr = stand;
////////////////////////////////////////////////////////////////////////////////
	delete[] x;
	delete[] y;	
	delete[] dist;
	delete[] fourier;
	delete[] stand;
}




void fourier(double inreal[], double inimag[], double outreal[], int n)
{
	int k;
	for(k = 0; k < n; k++)
	{
		double sumreal = 0;
		double sumimag = 0;
		int t;
		for(t = 0; t < n; t++)
		{
			double angle = 2*PI*t*k / n;
			sumreal += inreal[t]*cos(angle) + inimag[t]*sin(angle);
			sumimag += -inreal[t] * sin(angle) + inimag[t] * cos(angle);
		}
		outreal[k] = sumreal + sumimag;
	}

}

void fourier2(double inreal[],double outreal[], int n)
{
	int k;
	for(k = 0; k < n; k++)
	{
		double sumreal = 0;
		double sumimag = 0;
		int t;
		for(t = 0; t < n; t++)
		{
			double angle = 2*PI*t*k / n;
			sumreal += inreal[t]*cos(angle);
			sumimag += -inreal[t] * sin(angle);
		}
		outreal[k] = sumreal + sumimag;
	}

}






	//int **img;
	//img = new int*[count];
	//for(int i = 0;  i < count; i++)
	//	img[i] = new int[count];



	//for(int i = 0; i < count; i++)
	//	delete[] img[i];
	//delete[] img;









////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CannyEdge(IplImage *in, IplImage *out)
{
}
void BuildGaussianMask(int masksize/*È¦¼ö*/, float sigma, float **gaussianMask)
{
	int i,j;
	float div = pow(2.0f*(float)(PI)*sigma*sigma, 0.5f);
	int ct = masksize/2;	//center
	float sum=0.0f;
	float r2;
	
	for (i=0; i<masksize; i++)
	{
		for (j=0; j<masksize; j++)
		{
			r2 = (i-ct)*(i-ct)+(j-ct)*(j-ct);
			gaussianMask[i][j] = pow(EXPF, -r2/(2.0f*sigma*sigma)) / div;
			sum += gaussianMask[i][j];
		}
	}
	printf("\n");
	for (i=0; i<masksize; i++)
	{
		for (j=0; j<masksize; j++)
		{
			gaussianMask[i][j] /=  (sum / 100);
		}
	}
}
void GaussianFilter(IplImage *in, IplImage *out, float sigma)
{
	//CvtGray(in, in);
	//Mask »ý¼º
	int masksize = 13;
	int center = masksize / 2;
	float gaussianMask[13][13];	
	float div = pow(2.0f*(float)(PI)*sigma*sigma, 0.5f);
	float sum = 0.0f;
	for(int i = 0; i<masksize; i++)
	{
		for(int j = 0; j<masksize; j++)
		{
			float r2 = (i-center)*(i-center) + (j-center)*(j-center);
			gaussianMask[i][j] = pow(EXPF, -r2 / (2.0f * sigma * sigma)) / div;
			sum += gaussianMask[i][j];
		}
	}
	for(int i = 0; i<masksize; i++)
	{
		for(int j = 0; j<masksize; j++)
		{
			gaussianMask[i][j] /= (sum / 100);
		}
	}


	int row, col, rowOffset, colOffset, rowTotal, colTotal;
	int red, green, blue;
	int newPixel;

	for ( row = 0; row < in->widthStep; row+=3)
	{
		for( col= 0; col < in->height; col++)
		{					
			newPixel = 0;
			for(rowOffset = -center; rowOffset <= center; rowOffset++)
			{
				for(colOffset = -center; colOffset <=center; colOffset++)
				{
					rowTotal = row + rowOffset * 3;
					colTotal = col + colOffset;
					
					if(rowTotal < 0 || colTotal < 0 || rowTotal >= in->widthStep || colTotal >= in->height )
					{
						continue;
					}
				
					newPixel += (unsigned char)in->imageData[rowTotal+colTotal*in->widthStep+2] * gaussianMask[center+rowOffset][center+colOffset];
				}
			} 
			out->imageData[row+col*out->widthStep+2] = (unsigned char)((float)newPixel/100.0f);	//b
			out->imageData[row+col*out->widthStep+1] = (unsigned char)((float)newPixel/100.0f);	//g
			out->imageData[row+col*out->widthStep]   = (unsigned char)((float)newPixel/100.0f);	//r
			
		}
	}
	
}
//void CvtGray(IplImage *in, IplImage *out)
//{
//	unsigned char b, g, r, gray;
//
//	for(int i = 0; i<out->height; i++)
//	{
//		for(int j = 0; j<out->width; j++)
//		{
//			b = (unsigned char)in->imageData[(i*in->widthStep) + j * 3 + 0];		//b = *(in->imageData + i * 3 + 0);
//			g = (unsigned char)in->imageData[(i*in->widthStep) + j * 3 + 1];		//g = *(in->imageData + i * 3 + 1);
//			r = (unsigned char)in->imageData[(i*in->widthStep) + j * 3 + 2];		//r = *(in->imageData + i * 3 + 2);
//
//			gray = (unsigned char)((r+g+b)/3.0);			
//			
//			if(gray > 255)
//			{
//				gray = 255;
//			}
//			out->imageData[(i*out->widthStep) + j * 3 ] = gray;				//*(out->imageData + i) = gray;
//			out->imageData[(i*out->widthStep) + j * 3 + 1] = gray;
//			out->imageData[(i*out->widthStep) + j * 3 + 2] = gray;
//			
//		}
//	}
//}
