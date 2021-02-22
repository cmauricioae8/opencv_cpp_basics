/* @functions:  bitwise_{and,or,xor,not}, resize, rectangle, circle, fillConvexPoly, imwrite
 * @brief:      Logical bitwise operations and an application are shown
 * @author:     C. Mauricio Arteaga-Escamilla
 */
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp> //Include OpenCV header file

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
  //--------- EXAMPLES OF BINARY SINGLE CHANNEL ARRAYS  -----------------
  //In a binary image, the pixel value is either 0 -> black, or 255 -> white
  //Bitwise operations calculate the per-element bit-wise logical operations (and, or, xor, not)
  //of 2 arrays (or an array and a scalar). NOTE: Arrays must be equal in size and type

  Size my_size(500,200);

  Mat img1 = Mat::zeros(my_size,CV_8UC1);
  Mat img2 = Mat(my_size,CV_8UC1, Scalar(0));

  rectangle(img1, Rect(Point(100,50),Point(400,150)),Scalar(255),-1); //Draw a filled rectangle
  circle(img2, Point(250,100),70,Scalar(255),CV_FILLED,8); //Draw a filled circle

  //Display binary images
  imshow("Image 1", img1); imshow("Image 2", img2); //Windows_autosize

  //Bitwise operations using single channel arrays (binary)
  Mat AND, OR, XOR, NOT; //Results

  //Commutative, e.g. a × b = b × a, the order does not matter
  bitwise_and(img1, img2, AND); //Intersection operation is commutative
  bitwise_or( img1, img2, OR ); //Union operation is commutative
  bitwise_xor(img1, img2, XOR); //XOR operation is also commutative. a ^ a == 0 and a ^ 0 = a
  //a ^ b === (a && !b) || (!a && b)

  bitwise_not(XOR, NOT); //Invert the input array

  //Display the resulting images
  imshow("AND (Intersection)", AND);
  imshow("OR (Union)", OR);
  imshow("XOR", XOR);
  imshow("NOT (Complement)", NOT);

  printf("Using binary images, bitwise operations can be seen as Boolean operations\n");
  cout << "Press any key to continue" << endl;
  waitKey(0);
  destroyAllWindows();


  //Note: Bitwise operations can be applied to gray-scale and color images
  //--------- EXAMPLES USING BITWISE OPERATIONS WITH COLOR IMAGES
  Mat color1, color2;
  color1 = imread("lena.jpg", IMREAD_COLOR);
  color2 = imread("monkey.jpg", IMREAD_COLOR);

  if( !color1.data || color2.empty() )
  {
    printf("No image data\n");
    return -1; //Exit
  }

  //resize(color2,color2,color1.size()); //Note: both images must be of the same size and type

  //Display color images
  imshow("color image 1", color1); imshow("color image 2", color2);

  Mat AND_c, OR_c, XOR_c, NOT_c; //Results of the examples using color images

  bitwise_and(color1, color2, AND_c);
  bitwise_or(color1, color2, OR_c);
  bitwise_xor(color1, color2, XOR_c);
  bitwise_not(color2, NOT_c); //Invert the array

  //Display the resulting images
  imshow("AND", AND_c);   imshow("OR", OR_c);   imshow("XOR", XOR_c);   imshow("NOT", NOT_c);

  cout << "Press any key to continue" << endl;
  waitKey(0);
  destroyAllWindows();


  //--------- EXAMPLES USING THE MASK OPTION WITH COLOR IMAGES
  //The optional operation mask is an 8-bit single channel array that specifies elements of the
  //output array to be changed

  //Create the mask using a polygon
  Mat my_mask = Mat(color1.size(),CV_8UC1, Scalar(0)); //Note: 'my_mask' array is single channel

  vector<Point> points_list; //Define a polygon without knowing the total vertices (vector of Points)
  points_list.push_back(Point(150,150)); //Add the point to the list (in the last position)
  points_list.push_back(Point(260,380));
  points_list.push_back(Point(360,150));
  fillConvexPoly(my_mask,points_list,Scalar(255),8,0); //Draw a filled polygon

  //circle(my_mask,Point(250,250),150,Scalar(255),CV_FILLED,8);

  //Display the color image and my mask
  imshow("color image 1", color1); imshow("My mask", my_mask);

  Mat AND_m, OR_m, XOR_m, NOT_m;
  bitwise_and(color1, color2, AND_m, my_mask);
  bitwise_or(color1, color2, OR_m, my_mask);
  bitwise_xor(color1, color2, XOR_m, my_mask);
  bitwise_not(color1, NOT_m, my_mask); //Invert the array

  //Display the resulting images
  imshow("AND", AND_m);
  imshow("OR", OR_m);
  imshow("XOR", XOR_m);
  imshow("NOT", NOT_m);

  cout << "Press any key to continue" << endl;
  waitKey(0);
  destroyAllWindows();


  //------------- A POSSIBLE APPLICATION USING BITWISE OPERATIONS
  //Getting the upper section
  Mat upper_section;
  bitwise_and(color1, color1, upper_section, my_mask); //color1 && my_mask is not possible due to arrays
  //are not of the same type. color1 = C3, my_mask = C1
  imshow("Upper section", upper_section);

  //----- Creating the background
  Mat my_mask_inv;
  bitwise_not(my_mask, my_mask_inv); //Invert my mask to obtain the region of the background

  Mat temp, result;
  bitwise_and(color2, color2, temp, my_mask_inv); //Remember, 'my_mask_inv' is a single channel array
  imshow("Background", temp);

  bitwise_or( upper_section, temp, result); //Get the desired effect using bitwise operations
  //Note: 'or' and 'xor' operations work. 'and' operation does not work to get the desired effect

  //Display the resulting image
  imshow("Resulting image using bitwise operations", result);

  //Write images
  imwrite("bitwise_result.png", result);


  cout << "Press any key to exit" << endl;
  waitKey(0);
  return 0;
}
