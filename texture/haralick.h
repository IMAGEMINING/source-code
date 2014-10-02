
void inline UpdatePixel ( int x1 , int y1 , int x2 , int y2);
int normal;
int img_height;
int img_width;
double m_COM[256][256];
double m_fEnergy, m_fContrast, m_fHomogeneity, m_fEntropy, ux, uy, px[256],pdxy[512], pxy[512];
double stdDevix,stdDeviy, m_fVariance, hx, DiffAver, m_fSumAver, m_fSumEntr, m_fDiffEntr, 
	m_fCorrelation, hxy1, hxy2, m_fSumVri, m_DiffVari, m_flnMeaCor1, m_flnMeaCor2;
void haralick(IplImage image);
IplImage * image;
IplImage * img_gray;