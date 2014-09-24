#include "clustering.h"

void clustering(Point p)
{
	CvScalar color_tab[MAX_CLUSTER];
	IplImage *img = cvCreateImage(cvSize(500, 500), 8, 3);
	

	color_tab[0] = CV_RGB(255, 0, 0);
	color_tab[1] = CV_RGB(0, 255, 0);
	color_tab[2] = CV_RGB(255, 0, 255);
	color_tab[3] = CV_RGB(100, 100, 255);
	color_tab[4] = CV_RGB(255, 0, 255);
	cvNamedWindow("clusters", 1);

	for(;;)
	{
		int k, i;
		int cluster_count = p.n % MAX_CLUSTER + 1;
		int sample_count = p.n%1000 + 1;
		CvMat* points = cvCreateMat(sample_count, 1, CV_32FC2);
		CvMat* clusters = cvCreateMat(sample_count, 1, CV_32SC1);

		for(k = 0; k < cluster_count; k++)
		{

		}
	}
	
}