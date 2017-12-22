#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

int main( int argc, char** argv )
{
	
	Mat image;	// Source image array
	Mat hsv;
	Mat mask;
	
	std::vector<int> params;
	params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	params.push_back(9);   // that's compression level, 9 == full , 0 == none
	
	char* imageName = argv[1];

	image = imread( imageName, CV_LOAD_IMAGE_COLOR );
	
	// If no image was found
	if( argc != 2 || !image.data )
	{
		printf( " No image was found \n " );
		return -1;
	}

	// We resize the image to 300x300
	Size size(300,300);	
	resize(image,image,size);//resize image

	// Gaussian low-pass filter of size 7x7
	//GaussianBlur( image1, image1, Size( 7, 7 ), 0, 0 );
	
	// We change image space from RGB to HSV
    cvtColor(image,hsv,COLOR_BGR2HSV);
	
	// H(0-255) S(0-50) V(0-255)
	inRange(hsv,Scalar(0,0,0),Scalar(255,50,255),mask);
	
	imwrite("mask_temp.png",mask,params);
	
	bitwise_not (mask,mask);
	
	image.setTo(Scalar(0,0,0),mask);
	
	imwrite("img_temp.png",image, params);
	
    return 0;

}
