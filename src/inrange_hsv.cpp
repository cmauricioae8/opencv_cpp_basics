/* @functions:   cvtColor, inRange, createTrackbar, bitwise_and
 * @brief:       A simple program to filter an object based on its color (using HSV color space)
 * @author:      C. Mauricio Arteaga-Escamilla
 */
#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp" //Include OpenCV header file
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
  VideoCapture cap(0); //Create a video capture object. '0' to read the video stream from the webcam

  if( !cap.isOpened() ){ //Check if video capture opened successfully, if not success, exit program
    cout << "Cannot open the video capture" << endl;
    return -1;
  }

  string control_win = "Control";
  namedWindow(control_win, CV_WINDOW_AUTOSIZE); //Create the control window

  //Creating the variables to define the range of the specific color (red)
  int lowH = 170; int highH = 179;
  int lowS = 150; int highS = 255;
  int lowV = 60;  int highV = 255;

  //Creating the trackbars
  createTrackbar("LowH", control_win, &lowH, 179); //Hue (0 - 179)
  createTrackbar("HighH", control_win, &highH, 179);

  createTrackbar("LowS", control_win, &lowS, 255); //Saturation (0 - 255)
  createTrackbar("HighS", control_win, &highS, 255);

  createTrackbar("LowV", control_win, &lowV, 255); //Value (0 - 255)
  createTrackbar("HighV", control_win, &highV, 255);


  cout << "Press ESC or 'q' key to exit" << endl;

  while(1){

    Mat src;

    bool bSuccess = cap.read(src); //Read a new frame
    if (!bSuccess){ //If not success, break loop
      cout << "Cannot read the frame from video stream" << endl;
      break;
    }

    Mat imgHSV;
    cvtColor(src, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV color space

    Mat imgThresholded;
    inRange(imgHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), imgThresholded);
    //Checks that each element of 'imgHSV' lies between 'lowerb' and 'upperb'

    imshow("Thresholded image", imgThresholded); //Show the thresholded image. Note: imgThresholded is the mask

    imshow(control_win, src); //Show the source image and the controls

    //Display the filtered region in color
    Mat color;
    bitwise_and(src,src,color,imgThresholded);
    imshow("Color region", color); //Show the filtered color

    //Note: To reduce the noise and improve results, it recommended to use morphological operations (erode, dilate)

    char key = waitKey(50);
    if(key == 27 || key == 'q') break;
  }
  return 0;
}
