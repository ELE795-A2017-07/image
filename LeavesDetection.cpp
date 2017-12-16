#include <opencv2/opencv.hpp>

using namespace cv;

int main( int argc, char** argv )
{

 char* imageName = argv[1];
 Mat image;
 image = imread( imageName, IMREAD_COLOR );

 // If no image was found
 if( argc != 2 || !image.data )
 {
   printf( " No image was found \n " );
   return -1;
 }
 
 
 Mat gray_image;
 cvtColor( image, gray_image, COLOR_BGR2GRAY );
 imwrite( "Gray_Image.jpg", gray_image );
 
 return 0;
}