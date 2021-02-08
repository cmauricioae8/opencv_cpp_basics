/* @functions:  imshow, waitKey, destroyAllWindows, imread, flip, namedWindow, destroyWindow
 * @brief:      Basic functions of OpenCV are shown
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
  //--------- MATRIX DEFINITION
  cv::Mat mat0 = Mat::zeros(5,2,CV_8UC1); //ones, eye
  cout << "mat0 = " << endl << " " << mat0 << endl << endl; //Display in shell

  //Creating different types of images: Mat name(rows, cols, type, Scalar);
  Mat mat1(50,20,CV_8UC1,Scalar(0));  //Create a 50 x 20 single-channel array with 8 bit unsigned numbers
  //(pixels value = 0)
  Mat mat2(Size(80,40),CV_8UC1,Scalar(127)); //Note: Size(width/cols,height/rows)
  Mat mat3(Size(50,100),CV_8UC3, Scalar(0,0,255)); //Scalar = color (BGR). Scalar represents a 4-element vector

  Scalar my_color(255,0,0);
  Mat mat4(Size(50,100),CV_8UC3, my_color);

  imshow("Display mat1", mat1);
  imshow("Display mat2", mat2);
  imshow("Display mat3", mat3);
  imshow("Display mat4", mat4);
  waitKey(0); //Wait for any key press = pause

  destroyAllWindows(); //Close all windows


  //--------- READING IMAGES
  Mat image1, image2;
  std::string path = "robotica_posgrado.png";
  image1 = imread(path,1); //Reading from a path
  image2 = imread(path,0); //IMREAD_COLOR=1, IMREAD_GRAYSCALE=0, IMREAD_UNCHANGED=-1 (alpha channel)
  //img = imread( argv[1], 1 ); //Reading from shell

  if ( !image1.data || image2.empty() )
  {
    printf("No image data \n");
    return -1; //Exit
  }

  imshow("Display Image", image1); //Windows_autosize
  flip(image2,image2,1); //flip_mode = 0: flips around the x-axis, 1: y-axis, -1: both axes

  //--------- DISPLAYING IMAGES
  std::string my_window = "My window (flipped image)";
  namedWindow(my_window, WINDOW_NORMAL); //WINDOW_AUTOSIZE - User cannot resize the window
  //WINDOW_NORMAL- User can resize the window

  imshow(my_window,image2);
  cout << "Press any key to destroy the window '" << my_window << "'" << endl;
  waitKey(0);


  destroyWindow(my_window); //Destroy the created window
  printf("Press any key to exit\n");
  waitKey(0);

  return 0;
}

