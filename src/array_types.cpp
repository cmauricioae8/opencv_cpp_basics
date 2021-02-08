/* @functions:  resize, cvtColor
 * @brief:      How to get the pixel value (for gray-scale and color images) and array types
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
  //--------- READING IMAGES
  Mat color_img, gray_img;
  string path = "robotica_posgrado.png"; //Default image

  if(argc > 1) //User provided an image
  {
    color_img = imread(argv[1], IMREAD_COLOR); //Read an image in color
  }else{
    printf("The default image will be used\n");
    color_img = imread(path,1); //Default image
  }

  if(color_img.empty())
  {
    printf("Could not open or find the image!\n");
    return -1; //Exit
  }

  resize(color_img, color_img, Size(640, 480)); //Resize the image. Size(width,height)

  //-------- IMAGE CONVERSION
  //cvtColor(source_image, converted_image, type_of_conversion)
  //COLOR TO GRAY (CV_BGR2GRAY), COLOR TO HSV  ( CV_BGR2HSV)
  cvtColor(color_img,gray_img,COLOR_BGR2GRAY); //Y = (0.114)B + (0.587)G + (0.299)R


  //------ GRAY-SCALE IMAGE PROPERTIES
  printf("\nGray-scale image properties\n");
  cout << " Type (int): " << gray_img.type() << endl;

  int type1 = gray_img.type() & CV_MAT_DEPTH_MASK; //For gray-scale is not necessary the mask
  string r1;
  switch (type1) {
    case CV_8U:  r1 = "8U"; break;
    case CV_8S:  r1 = "8S"; break;
    case CV_16U: r1 = "16U"; break;
    case CV_16S: r1 = "16S"; break;
    case CV_32S: r1 = "32S"; break;
    case CV_32F: r1 = "32F"; break;
    case CV_64F: r1 = "64F"; break;
    default:     r1 = "User"; break;
  }

  cout << " Type (string): " << r1 << endl;
  cout << " Size (height, width): " << gray_img.size << endl;
  cout << " Channels: " << gray_img.channels() << endl;

  //Getting a pixel value (1 channel array)
  int x = gray_img.cols-1; //last x position
  int y = gray_img.rows-1; //last y position

  int p = gray_img.at<uchar>(Point(x,y)); //Check (y,x), int p = gray_img.at<uchar>(y,x);
  cout << " Pixel value (x,y) = (col,row) = (" << x << "," << y << "): " << p << endl;


  //------ COLOR IMAGE PROPERTIES
  printf("\nColor image properties\n");
  cout << " Type (int): " << color_img.type() << endl;

  int type = color_img.type() & CV_MAT_DEPTH_MASK;
  string r;
  switch (type) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }
  
  cout << " Type (string): " << r << endl;
  cout << " Size (height, width): " << color_img.size << endl;
  cout << " Channels: " << color_img.channels() << endl;

  //Getting a pixel value (3 channel array)
  int myRow = color_img.rows-1; //Switched position
  int myCol = color_img.cols-1;
  Vec3b pixel = color_img.at<Vec3b>(myRow, myCol); //(y,x) if Point is not used
  cout << " (B,G,R) Pixel value (x,y) = (col,row) = (" << x << "," << y << "): (";
  cout <<  (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;


  //--------- CREATING WINDOWS
  string gray_imgW = "Gray-scale image";
  namedWindow(gray_imgW, WINDOW_NORMAL); //WINDOW_AUTOSIZE, WINDOW_NORMAL
  string color_imgW = "Color image";
  namedWindow(color_imgW, WINDOW_NORMAL);

  imshow(gray_imgW, gray_img);
  imshow(color_imgW, color_img);

  printf("\nPress any key to exit\n");
  waitKey(0);

  return 0;
}

