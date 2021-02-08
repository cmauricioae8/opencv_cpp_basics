/* @functions:  split, merge, imwrite
 * @brief:      How to separate a color image into 3 planes is shown. Each plane is a color image.
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
  Mat src_img;
  string path = "robotica_posgrado.png";

  if(argc > 1) //User provided an image
  {
    src_img = imread(argv[1], IMREAD_COLOR); //Get the color image
  }else{
    printf("Using default image\n");
    src_img = imread(path,1); //Default image
  }

  if(src_img.empty())
  {
    printf("Could not open or find the image!\n");
    return -1; //Exit
  }

  //-------- SPLIT CHANNELS INTO 3 PLANES
  vector<Mat> bgr_planes; //Define a vector of matrices
  split(src_img, bgr_planes); //Split the source image. Note: Every plane is 1 channel array

  imshow("Blue channel (C1)", bgr_planes[0]);
  imshow("Green channel (C1)", bgr_planes[1]);
  imshow("Red channel (C1)", bgr_planes[2]);

  printf("Press any key to destroy all windows\n");
  waitKey(0); //Wait for any key press

  destroyAllWindows();

  //Showing each channel in color
  Mat zero(src_img.size(),CV_8UC1,Scalar(0)); //Define an auxiliar 1 channel array with the same size

  //Define each channel
  vector<Mat> Blue = { bgr_planes[0], zero, zero };
  vector<Mat> Green = { zero, bgr_planes[1], zero };
  vector<Mat> Red = { zero, zero, bgr_planes[2] };

  Mat colorB, colorG, colorR;

  //Merge the channels into a color one
  merge(Blue, colorB);   merge(Green, colorG);   merge(Red, colorR);

  imshow("Blue channel (C3)", colorB);
  imshow("Green channel (C3)", colorG);
  imshow("Red channel (C3)", colorR);

  imwrite("b_channel.png",colorB); //path, name and extension (jpg, png)
  imwrite("g_channel.png",colorG);
  imwrite("r_channel.png",colorR);

  printf("\nPress any key to exit\n");
  waitKey(0);

  return 0;
}
