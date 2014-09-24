//#include "main.h"
//#define MAX_CLUSTER 4
//
//void main()
//{
//	CvScalar color_tab[MAX_CLUSTER];
//	IplImage *img = cvCreateImage(cvSize(500, 500), 8, 3);
//	CvRNG rng = cvRNG(0xffffffff);
//
//	color_tab[0] = CV_RGB(255, 0, 0);
//	color_tab[1] = CV_RGB(0, 255, 0);
//	color_tab[2] = CV_RGB(255, 255, 255);
//	//color_tab[3] = CV_RGB(100, 100, 255);
//	//color_tab[4] = CV_RGB(255, 0, 255);
//	//color_tab[5] = CV_RGB(0, 0, 255);
//	cvNamedWindow("clusters", 1);
//
//	for(;;)
//	{
//		int k, i;
//		int cluster_count = cvRandInt(&rng) % MAX_CLUSTER + 1;
//		int sample_count = cvRandInt(&rng)%1000 + 1;
//		CvMat* points = cvCreateMat(sample_count, 1, CV_32FC2);
//		CvMat* clusters = cvCreateMat(sample_count, 1, CV_32SC1);
//
//		for(k = 0; k < cluster_count; k++)
//		{
//			CvPoint center;
//			CvMat point_chunk;
//
//			center.x = cvRandInt(&rng) % img->width;
//			center.y = cvRandInt(&rng) % img->height;
//
//			cvGetRows(points, &point_chunk, k*sample_count / cluster_count,
//						k==cluster_count -1 ? sample_count : (k+1)*sample_count / cluster_count);
//
//			cvRandArr(&rng, &point_chunk, CV_RAND_NORMAL,
//				cvScalar(center.x, center.y, 0, 0),
//				cvScalar(img->width/6, img->height/6, 0,0) );
//		}
//
//		for(i = 0; i<sample_count/2; i++)
//		{
//			CvPoint2D32f * pt1 = (CvPoint2D32f*)points->data.fl + cvRandInt(&rng)%sample_count;
//			CvPoint2D32f * pt2 = (CvPoint2D32f*)points->data.fl + cvRandInt(&rng)%sample_count;
//			CvPoint2D32f temp;
//			CV_SWAP(*pt1, *pt2, temp);
//		}
//		cvKMeans2(points, cluster_count, clusters, cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 1.0) );
//		cvZero( img );
//		for(i = 0; i < sample_count; i++)
//		{
//			CvPoint2D32f pt = ((CvPoint2D32f * )points -> data.fl)[i];
//			int cluster_idx = clusters->data.i[i];
//			cvCircle( img, cvPointFrom32f(pt), 2, color_tab[cluster_idx], CV_FILLED ) ;
//		}
//		cvReleaseMat(&points);
//		cvReleaseMat(&clusters);
//		cvShowImage("clusters", img);
//		if(cvWaitKey(0) ==27)
//			break;
//	}
//	cvReleaseImage(&img);
//	cvDestroyWindow("clusters");
//}


#include "shape.h"
#include "Image.h"
//#include "clustering.h"

int main(void)
{
	IplImage *input_image	 = cvLoadImage("2.jpg");
	IplImage *resize_image	 = cvCreateImage(cvGetSize(input_image), IPL_DEPTH_8U, 3);
	IplImage *edge_image	 = cvCreateImage(cvGetSize(input_image), IPL_DEPTH_8U, 3);
	IplImage *result_image	 = cvCreateImage(cvGetSize(input_image), IPL_DEPTH_8U, 3);
	Point p;

	//GaussianFilter(input_image, result_image, 2.0f);
	//out = cvCreateImage(cvGetSize(reSize(input_image)), IPL_DEPTH_8U, 3);

	
	resize_image = preProcess(input_image);
	detect_edge(resize_image, edge_image, p);
	



	cvNamedWindow("input");
	cvNamedWindow("resize");
	cvNamedWindow("shape");
	cvShowImage("input", input_image);
	cvShowImage("resize", resize_image);
	cvShowImage("shape", edge_image);

	cvWaitKey(0);
	cvDestroyAllWindows();
	
	return 0;
}
//
//
////int main(void)
////{
////	IplImage *input = cvLoadImage("11.jpg");
////	IplImage *output  = cvCreateImage(cvGetSize(input), IPL_DEPTH_8U, 1);
////	IplImage *result  = cvCreateImage(cvGetSize(input), IPL_DEPTH_8U, 3);
////	cvCvtColor(input, output, CV_BGR2GRAY);
////
////	cvMerge(output, output, output, NULL, result);
////	cvNamedWindow("input");
////	cvNamedWindow("output");
////	cvShowImage("input", input);
////	cvShowImage("output", result);
////
////	cvWaitKey(0);
////	cvDestroyAllWindows();
////	
////	return 0;
////
////	return 0;
////}
//
//
//
////int main(void)
////{
////	
////	IplImage *input_image	=cvLoadImage("2.jpg");
////	IplImage *hsv_image	=cvCreateImage(cvGetSize(input_image), IPL_DEPTH_8U, 3);
////
////	//CVrgb2hsv(input_image, hsv_image);
////	//rgb2hsv(input_image, hsv_image);
////
////	//histogram(input_image);
////	color_extract(input_image, hsv_image);
////	//////////////////////////////////////////////////////////////////////////////////////////
////	//cvNamedWindow("OUTPUT");
////	//cvShowImage("OUTPUT", input_image);
////	//cvWaitKey(0);
////	//cvDestroyAllWindows();
////
////	//cvReleaseImage(&hsv_image);
////
////	return 0;	
////}