/* @functions:  createTrackbar, setTrackbarPos, getTrackbarPos, setTrackbarMax, setTrackbarMin, addWeighted
 * @brief:      A weighted sum of 2 images is used to show how to create trackbars
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file

using namespace cv;
using namespace std;

//Global variables
Mat img1, img2;
int shape = 0, shape_max = 2;
int alpha_slider_max = 100; //The minimum limit is always zero

//Define the window name
string sum_window = "Weighted sum (using callback function)";

void trackbar_callback1(int alpha_slider, void*) //The function that is executed every change on the trackbar value
{
   double alpha = (double) alpha_slider/alpha_slider_max ;
   double beta = ( 1.0 - alpha );
   Mat sum;
   sum = img1*alpha + img2*beta; //addWeighted( img1, alpha, img2, beta, 0.0, sum);
   imshow( sum_window, sum );
}

int main(int argc, char** argv )
{
  //Reading source images
  img1 = imread("lena.jpg", IMREAD_COLOR);
  img2 = imread("robotica_posgrado.png", IMREAD_COLOR);

  if( !img1.data || img2.empty() )
  {
    printf("Cannot read one of the images\n");
    return -1; //Exit
  }

  //Note: Both images must be of the same size and type
  resize(img2,img2,img1.size());

  int alpha_slider = 20; //This variable can be global

  //---------- Option 1: Create a trackbar using a callback function
  namedWindow(sum_window, WINDOW_NORMAL); //Create the window of the option 1
  string trackbar1_name = "alpha";

  //If a trackbar using a callback function is created, then a while loop is not required
  createTrackbar( trackbar1_name, sum_window, &alpha_slider, alpha_slider_max, trackbar_callback1);
  trackbar_callback1(alpha_slider, 0); //Execute the callback function once


  //---------- Option 2: Create a trackbar using a global variable (not a callback function)
  string shape_window = "Drawing a figure (using a global variable)";
  namedWindow(shape_window, WINDOW_NORMAL);
  string trackbar2_name = "shape:\n 0: circle\n 1: square\n 2: rectangle\n"; //A menu format can be obtained

  //Create a trackbar using a global variable, thus a while loop is required
  createTrackbar( trackbar2_name, shape_window, &shape, shape_max, 0, 0); //Note: no user data


  cout << "Press ESC key to exit" << endl;

  while(1)
  {
    Mat temp;
    img1.copyTo(temp); //A copy is used to erase the previous draw

    if(shape == 0)
      circle(temp,Point(img1.cols/2,img1.rows/2),200,Scalar(255,255,255),3,8,0); //Draw a circle at the center of the image
    else if(shape == 1)
    {
      Rect my_square(50,50,200,200); //Define a Rect object
      rectangle(temp,my_square,Scalar(0,0,250),3,8,0); //Draw a square
    }else
    {
      Rect my_rectangle(250,180,200,300);
      rectangle(temp,my_rectangle,Scalar(255,0,255),3,8,0); //Draw a rectangle

      //Getting the value of a trackbar
      int trackbar1 = getTrackbarPos(trackbar1_name, sum_window);
      cout << "trackbar1_name : " << trackbar1 << endl;

      //Setting the value of a trackbar
      setTrackbarPos(trackbar1_name, sum_window, 75);
      setTrackbarMax(trackbar1_name, sum_window, 90);
      setTrackbarMin(trackbar1_name, sum_window, 10);
    }

    imshow(shape_window, temp); //Display the temporal image

    int key = waitKey(100); //Wait 100 ms for any key press
    if(key == 27) break; //ESC key = 27
  }
  return 0;
}

