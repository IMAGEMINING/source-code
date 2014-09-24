#include "Image.h"

double distance(int x1, int y1, int x2, int y2) // x1, y1 픽셀 위치(x햇) x2, y2 인접한 픽셀 위치(xout->imageData[i+j*in->widthStep+2])
{
	return sqrt(pow((float)x2-x1, 2) + pow((float)y2-y1, 2));
}
void CvtGray(IplImage *in, IplImage *out)
{
	unsigned char b, g, r, gray;

	for(int i = 0; i<out->height; i++)
	{
		for(int j = 0; j<out->width; j++)
		{
			b = (unsigned char)in->imageData[(i*in->widthStep) + j * 3 + 0];		//b = *(in->imageData + i * 3 + 0);
			g = (unsigned char)in->imageData[(i*in->widthStep) + j * 3 + 1];		//g = *(in->imageData + i * 3 + 1);
			r = (unsigned char)in->imageData[(i*in->widthStep) + j * 3 + 2];		//r = *(in->imageData + i * 3 + 2);

			gray = (unsigned char)((r+g+b)/3.0);			
			
			if(gray > 255)
			{
				gray = 255;
			}
			out->imageData[(i*out->widthStep) + j * 3 ] = gray;				//*(out->imageData + i) = gray;
			out->imageData[(i*out->widthStep) + j * 3 + 1] = gray;
			out->imageData[(i*out->widthStep) + j * 3 + 2] = gray;
			
		}
	}
}
IplImage *reSize(IplImage *in)
{
	IplImage *out = cvCreateImage(cvSize(W, H), IPL_DEPTH_8U, 3);
	if(in-> width == W && in->height == H)
		return in;
	//else
	//{
	//	IplImage *out = cvCreateImage(cvSize(W, H), IPL_DEPTH_8U, 3);
	//	cvResize(in, out, 1);
	//	return out;
	//}
	else if(in->width > W && in->height > H)
	{		
		IplImage *mid;
		if(in->width >= in->height)
		{
			mid = cvCreateImage(cvSize(W, W*in->height/in->width), IPL_DEPTH_8U, 3);	
		}
		else if(in->width <= in->height)
		{
			mid = cvCreateImage(cvSize(H*in->width/in->height, H), IPL_DEPTH_8U, 3);
		}
		cvResize(in, mid, CV_INTER_LINEAR);
		return mid;
		cvReleaseImage(&mid);
	}
	else if(in->width > W && in->height < H)
	{
		IplImage *mid;
		if(in->width >= in->height)
		{
			mid = cvCreateImage(cvSize(W, W*in->height/in->width), IPL_DEPTH_8U, 3);	
		}
		else if(in->width <= in->height)
		{
			mid = cvCreateImage(cvSize(H*in->width/in->height, H), IPL_DEPTH_8U, 3);
		}
		cvResize(in, mid, CV_INTER_LINEAR);
		return mid;
		cvReleaseImage(&mid);
	}
	else if(in->width < W && in->height > H)
	{
		IplImage *mid;
		if(in->width >= in->height)
		{
			mid = cvCreateImage(cvSize(W, W*in->height/in->width), IPL_DEPTH_8U, 3);	
		}
		else if(in->width <= in->height)
		{
			mid = cvCreateImage(cvSize(H*in->width/in->height, H), IPL_DEPTH_8U, 3);
		}
		cvResize(in, mid, CV_INTER_LINEAR);
		return mid;
		cvReleaseImage(&mid);
	}
	else if(in->width < W && in->height < H)
	{
		IplImage *mid;
		if(in->width >= in->height)
		{
			mid = cvCreateImage(cvSize(W, W*in->height/in->width), IPL_DEPTH_8U, 3);	
		}
		else if(in->width <= in->height)
		{
			mid = cvCreateImage(cvSize(H*in->width/in->height, H), IPL_DEPTH_8U, 3);
		}
		cvResize(in, mid, CV_INTER_LINEAR);
		return mid;
		cvReleaseImage(&mid);
	}

	//else if(in->width > W && in->height > H)
	//{
	//	IplImage *out = cvCreateImage(cvSize(W, H), IPL_DEPTH_8U, 3);
	//	cvResize(in, out, 1);
	//	return out;
	//	cvReleaseImage(&out);
	//}
	//else if(in->width > W && in->height < H)
	//{
	//	int temp = W / in->width;
	//	IplImage *mid = cvCreateImage(cvSize(temp, temp), IPL_DEPTH_8U, 3);
	//	IplImage *out = cvCreateImage(cvSize(W, H), IPL_DEPTH_8U, 3);
	//	cvResize(in, mid, 1);
	//	for(int i = 0; i < W; i++)
	//	{
	//		for(int j = 0; j < in->height), 
	//	}
	//	return out;
	//	cvReleaseImage(&out);
	//}
	//else if(in->width < W && in->height > H)
	//{
	//}
	//else //in->width < W && in->height < height
	//{
	//}
}
IplImage* preProcess(IplImage *in)
{
	IplImage *gray = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 3);
	CvtGray(in, gray);
	return reSize(gray);
}















/////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CVrgb2hsv(IplImage* in, IplImage* out)
//{
//	cvCvtColor(in, out, CV_BGR2HSV);
//}
//void rgb2hsv(IplImage* in, IplImage* out)
//{
//	unsigned char h, s, v;
//	unsigned char r, g, b;
//	unsigned char rgb_min, rgb_max;
//
//	for(int width = 0; width < in->widthStep; width+3)
//	{
//		for(int height = 0; height < in->height; ++height)
//		{
//			b = ((unsigned char)(in->imageData[width+height*in->widthStep]));
//			g = ((unsigned char)(in->imageData[width+height*in->widthStep + 1]));
//			r = ((unsigned char)(in->imageData[width+height*in->widthStep + 2]));
//			
//			rgb_min = MATH_MIN3(b, g, r);
//			rgb_max = MATH_MAX3(b, g, r);
//
//			v = rgb_max;
//			if(v == 0)
//			{
//				h = s = 0;
//				out->imageData[width+height*out->widthStep] = h;
//				out->imageData[width+height*out->widthStep + 1] = s;
//				out->imageData[width+height*out->widthStep + 2] = v;
//			}
//
//			s = 255*(rgb_max - rgb_min) / v;
//			if(s == 0){
//				h = 0;
//				out->imageData[width+height*out->widthStep] = h;
//				out->imageData[width+height*out->widthStep + 1] = s;
//				out->imageData[width+height*out->widthStep + 2] = v;
//			}
//
//			if(rgb_max == r)
//			{
//				h = 0 + 43*(g-b) / (rgb_max - rgb_min);
//			}
//			else if(rgb_max == g)
//			{
//				h = 85 + 43*(b-r) / (rgb_max - rgb_min);
//			}
//			else
//			{
//				h = 171 + 43*(r-g) / (rgb_max - rgb_min);
//			}
//
//			out->imageData[width+height*out->widthStep] = h;
//			out->imageData[width+height*out->widthStep + 1] = s;
//			out->imageData[width+height*out->widthStep + 2] = v;
//
//			//double tmp1=((r-g)+(r-b))/2;
//			//double tmp2=sqrt( pow((double)(r-g),2) + (r-b)*(g-b) );
//			//h = acos(tmp1/tmp2);
//			//s = 1-( 3*MATH_MIN3(b,g,r)/(b+g+r) );
//			//v = (b+g+r) / 3;
//
//			//out->imageData[width+height*out->widthStep] = h;
//			//out->imageData[width+height*out->widthStep + 1] = s;
//			//out->imageData[width+height*out->widthStep + 2] = v;
//		}
//	}
//}
//
//void histogram(IplImage* in)
//{
//	int bins = 256;
//	float ranges0 [] = {0, 255};
//	float *ranges[] = {ranges0};
//	float rmax_val, gmax_val, bmax_val;
//	
//	IplImage *R_plane = cvCreateImage (cvGetSize(in), 8, 1);
//	IplImage *G_plane = cvCreateImage (cvGetSize(in), 8, 1);
//	IplImage *B_plane = cvCreateImage (cvGetSize(in), 8, 1);
//	IplImage *R_hist = cvCreateImage (cvGetSize(in), 8, 1);
//	IplImage *G_hist = cvCreateImage (cvGetSize(in), 8, 1);
//	IplImage *B_hist = cvCreateImage (cvGetSize(in), 8, 1);
//	CvHistogram *rhist = cvCreateHist(1, &bins, CV_HIST_ARRAY, ranges, 1);
//	CvHistogram *ghist = cvCreateHist(1, &bins, CV_HIST_ARRAY, ranges, 1);
//	CvHistogram *bhist = cvCreateHist(1, &bins, CV_HIST_ARRAY, ranges, 1);
//
//	cvSplit(in, B_plane, G_plane, R_plane, 0);
//	cvCalcHist( &R_plane, rhist, 0, NULL);
//	cvCalcHist( &G_plane, ghist, 0, NULL);
//	cvCalcHist( &B_plane, bhist, 0, NULL);
//
//	cvGetMinMaxHistValue( rhist, 0, &rmax_val, 0, 0);
//	cvGetMinMaxHistValue( ghist, 0, &gmax_val, 0, 0);
//	cvGetMinMaxHistValue( bhist, 0, &bmax_val, 0, 0);
//
//	cvScale(rhist->bins, rhist->bins, ((double)R_hist->height)/rmax_val, 0);
//	cvScale(ghist->bins, ghist->bins, ((double)G_hist->height)/gmax_val, 0);
//	cvScale(bhist->bins, bhist->bins, ((double)B_hist->height)/bmax_val, 0);
//
//	cvSet( R_hist, cvScalarAll(255), 0);
//	cvSet( G_hist, cvScalarAll(255), 0);
//	cvSet( B_hist, cvScalarAll(255), 0);
//
//	int bin_w = cvRound((double)R_hist->width / bins);
//
//	for(int i = 0; i < bins; i++)
//	{
//		cvRectangle(R_hist, cvPoint(i*bin_w, R_hist->height),
//							cvPoint((i+1)*bin_w, R_hist->height - cvRound(cvGetReal1D(rhist->bins, i))), cvScalarAll(0), 1);
//		cvRectangle(G_hist, cvPoint(i*bin_w, G_hist->height),
//							cvPoint((i+1)*bin_w, G_hist->height - cvRound(cvGetReal1D(ghist->bins, i))), cvScalarAll(0), 1);
//		cvRectangle(B_hist, cvPoint(i*bin_w, B_hist->height),
//							cvPoint((i+1)*bin_w, B_hist->height - cvRound(cvGetReal1D(bhist->bins, i))), cvScalarAll(0), 1);
//	}
//
//	cvNamedWindow("R_histogram");
//	cvNamedWindow("G_histogram");
//	cvNamedWindow("B_histogram");
//	cvNamedWindow("R_channel", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("G_channel", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("B_channel", CV_WINDOW_AUTOSIZE);
//
//	cvShowImage("R_histogram", R_hist);
//	cvShowImage("G_histogram", G_hist);
//	cvShowImage("B_histogram", B_hist);
//	cvShowImage("R_channel", R_plane);
//	cvShowImage("G_channel", G_plane);
//	cvShowImage("B_channel", B_plane);
//
//	cvWaitKey(0);
//	cvDestroyAllWindows();
//
//	cvReleaseImage(&R_hist);
//	cvReleaseImage(&G_hist);
//	cvReleaseImage(&B_hist);
//	cvReleaseImage(&R_plane);
//	cvReleaseImage(&G_plane);
//	cvReleaseImage(&B_plane);
//}
//
//
//long getx, gety;
//int getRed, getGreen, getBlue;
//char getFlag = 0;
//void eventhandle(int event, int x, int y, int flag, void* param)
//{
//	switch(event)
//	{
//	case CV_EVENT_LBUTTONDOWN:
//		if(getFlag == 0)
//		{
//			getx = x;
//			gety = y;
//			getFlag = 1;
//		}else if(getFlag == 1)
//		{
//			getFlag = 2;
//		}
//		break;
//
//	case CV_EVENT_RBUTTONDOWN:
//		getFlag = 0;
//		break;
//	}
//}
//
//void color_extract(IplImage* in, IplImage* out)
//{
//	char buffer[200];
//	CvSize size;
//	CvFont font;
//	int H, S, V;
//	int lowH, lowS, lowV, highH, highS, highV;
//	int cx, cy, radius, ccnt;
//	IplImage *GrayImg = 0;
//	IplImage *SmoothImg = 0;
//	IplImage *HSVImg = 0;
//	IplImage *HImg = 0;
//	IplImage *SImg = 0;
//	IplImage *VImg = 0;
//	int key;
//
//
//	CvMat *mask;
//	
//	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.5,0.5);
//	cvSetMouseCallback("InputImage", eventhandle, (void*)in);
//
//	if(getFlag == 0)
//	{
//		sprintf(buffer, "Picking up color by left click");
//		cvPutText(in, buffer, cvPoint(200,20), &font, CV_RGB(255, 255, 255));
//	}
//	else if(getFlag == 1)
//	{
//		sprintf(buffer, "If below color is right you chosen, start detect by left click again");
//		cvPutText(in, buffer, cvPoint(20,20), &font, CV_RGB(255,255,255));
//		size =cvGetSize(in);
//		CvScalar v = cvGet2D(in, gety, getx);
//		getBlue = (int)v.val[0];
//		getGreen = (int)v.val[1];
//		getRed = (int)v.val[2];
//
//		SmoothImg = cvCreateImage(size, IPL_DEPTH_8U, 3);
//		cvSmooth(in, SmoothImg, CV_GAUSSIAN, 9, 9, 2, 2);
//		HSVImg = cvCreateImage(size, IPL_DEPTH_8U, 3);
//		cvCvtColor(SmoothImg, HSVImg, CV_BGR2HSV);
//		CvScalar s = cvGet2D(HSVImg, gety, getx);
//		H = (int)s.val[0];
//		S = (int)s.val[1];
//		V = (int)s.val[2];
//
//		sprintf(buffer,"X = %d, Y = %d, R = %d, G = %d, B = %d, H = %d, S = %d, V = %d",
//				getx, gety, getRed, getGreen, getBlue, H, S, V);
//		cvPutText(in, buffer, cvPoint(getx,gety), &font, CV_RGB(255,255,255));
//	}
//	else
//	{
//		sprintf(buffer, "You can picking up again by right click");
//		cvPutText(in, buffer, cvPoint(100,20), &font, CV_RGB(255,255,255));
//		cvSmooth(in, SmoothImg, CV_GAUSSIAN, 9, 9, 2, 2);
//		cvCvtColor(SmoothImg, HSVImg, CV_BGR2HSV);
//		
//		lowH = H*LOW_BOUND;
//		highH = H*HIGH_BOUND;
//		if(highH >= 180) highH = 179;
//
//		lowS = S*LOW_BOUND;
//		highS = S*HIGH_BOUND;
//		if(highS >= 256) highS = 255;
//
//		lowV = V*LOW_BOUND;
//		highV = V*HIGH_BOUND;
//		if(highV >= 256) highV = 255;
//
//		mask = cvCreateMat(size.height, size.width, CV_8UC1);
//		cvInRangeS(HSVImg, cvScalar(lowH, lowS, lowV), cvScalar(highH, highS, highV), mask);
//
//		cvErode(mask, mask, NULL);
//		cvDilate(mask, mask, NULL);
//
//		GrayImg = cvCreateImage(size, 8, 1);
//		cvCopy(mask, GrayImg, NULL);
//		cvSmooth(GrayImg, GrayImg, CV_GAUSSIAN, 15, 15, 2, 2);
//
//		CvMemStorage* storage =cvCreateMemStorage(0);
//		CvSeq* Circles = cvHoughCircles(GrayImg, storage, CV_HOUGH_GRADIENT, 2, size.height/10, 100, 40, 5, 60);
//
//		for(int k = 0; k<Circles->total; k++)
//		{
//			float* circle;
//			circle = (float*) cvGetSeqElem(Circles, k);
//
//			ccnt = Circles->total;
//
//			cx = cvRound(circle[0]);
//			cy = cvRound(circle[1]);
//			radius = cvRound(circle[2]);
//			cvCircle(in, cvPoint(cx,cy), radius, CV_RGB(0,255,0), 3, 8, 0);
//
//			sprintf(buffer, "X=%d, Y=%d, R=%d", cx, cy, radius);
//			cvPutText(in, buffer, cvPoint(cx-80, cy+radius+15), &font, CV_RGB(255,255,255));
//		}
//		cvReleaseMemStorage(&storage);
//
//		cvNamedWindow("HSVImage");
//		cvShowImage("HSVImage", HSVImg);
//		//cvMoveWindow("HSVImage", 850, 200);
//
//		cvNamedWindow("Mask");
//		cvShowImage("Mask", mask);
//		//cvMoveWindow("Mask", 850, 700);
//	}
//	cvNamedWindow("PreviewImage");
//	cvShowImage("PreiviewImge", in);
//	//cvMoveWindow("PreviewImage", 200, 200);
//	//key = cvWaitKey(1);
//	cvWaitKey(0);
//	cvDestroyAllWindows();
//	
//	cvReleaseImage(&SmoothImg);
//	cvReleaseImage(&GrayImg);
//	cvReleaseImage(&HSVImg);
//}
