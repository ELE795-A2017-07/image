/** 
 *  @file    LeavesDetection.cpp
 *  @author  Samuel Asselin
 *  @date    19/12/2017 
 *  @version 1.0 
 *  
 *  @brief Detect mildiou, black rot or holes on leaves
 *
 *  @section DESCRIPTION
 *  
 *  This is a little program that receives an image as input
 *  and uses thresholding to determine if the leaves contain
 *	either mildiou or black rot.
 *	
 *  TODO: 
 *		- Do something if there is a problem on the leaves.
 *		- Detect holes with border detection.
 *
 */
 
#include <opencv2/opencv.hpp>
#include <vector>

#define IMG_WIDTH	300
#define	IMG_HEIGHT	300
#define	IMG_FILE	"img_temp.png"
#define	MSK_FILE	"mask_temp.png"
#define COMPRESSION_LEVEL	9 // that's compression level, 0 == none, 9 == full

using namespace cv;

int main( int argc, char** argv )
{
	
	Mat image;	// Source image array
	Mat hsv;
	Mat mask;
	
	std::vector<int> params;
	params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	params.push_back(COMPRESSION_LEVEL);   
	
	char* imageName = argv[1];

	image = imread( imageName, CV_LOAD_IMAGE_COLOR );
	
	// If no image was found
	if( argc != 2 || !image.data )
	{
		printf( " No image was found \n " );
		return -1;
	}

	// We resize the image to 300x300
	Size size(IMG_WIDTH,IMG_HEIGHT);	
	resize(image,image,size);//resize image

	// Gaussian low-pass filter of size 7x7
	//GaussianBlur( image1, image1, Size( 7, 7 ), 0, 0 );
	
	// We change image space from RGB to HSV
	cvtColor(image,hsv,COLOR_BGR2HSV);
	
	// H(0-255) S(0-50) V(0-255)
	inRange(hsv,Scalar(0,0,0),Scalar(255,50,255),mask);
	
	imwrite(MSK_FILE,mask,params);
	
	bitwise_not (mask,mask);
	
	image.setTo(Scalar(0,0,0),mask);
	
	imwrite(IMG_FILE,image, params);
	
	return 0;

}
