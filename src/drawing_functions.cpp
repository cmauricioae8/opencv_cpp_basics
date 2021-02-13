/* @functions:  int2string, string2int, moveWindow, rectangle, circle, line, arrowedLine,
 *              drawMarker, polylines, fillConvexPoly, putText
 * @brief:      How to draw different figures and write a text in the image
 * @author:     C. Mauricio Arteaga-Escamilla
 */
//Sources info: https://docs.opencv.org/3.4/d6/d6e/group__imgproc__draw.html
#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp> //Include OpenCV header file
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

string int2string(int number){ //Function to convert an integer number to a string
  std::stringstream ss;
  ss << number;
  return ss.str();
}

int string2int(string chain){ //Function to convert a string to an integer number
    int number;
    std::stringstream s;
    s << chain;
    s >> number;
    return number;
}

int main(int argc, char** argv ) //char *argv[]
{
  //-------- DEFINING POINTS (2D, 3D)
  Point p1; p1.x = 15; p1.y = 20; //Define a 2D point, specified by its image coordinates (x,y)
  Point p2 = Point(500, 600); //Point: integers
  Point p_bl(60,900);

  Point2d P3(0.5,1.6); //Point2d: double, Point2f: float
  Point3f P4(1.5,2.9,3.14); //P4.x, P4.y, P4.z

  cout << "p1: " << p1 << endl;
  cout << "p2: " << p2 << endl;
  cout << "p_bl: " << p_bl << endl;
  cout << "P3: " << P3 << endl;
  cout << "P4: " << P4 << endl;


  //--------- CREATING WINDOWS
  string my_draw_win = "Drawing window";
  namedWindow(my_draw_win, WINDOW_NORMAL); //WINDOW_AUTOSIZE, WINDOW_NORMAL

  Mat base(1000,2000,CV_8UC3,Scalar::all(0)); //Define a color image as the background
  int my_width = 200;
  int my_height = 300;
  int my_thickness = 6; //thickness = -1 means FILLED
  //int my_lineType = LINE_4: 4-connected line, LINE_8: 8-connected line, LINE_AA: antialiased line
  double my_tipLength = 0.2; //The length of the arrow tip in relation to the arrow length


  //-------- DRAWING FUNCTIONS
  Rect my_rectangle(p1.x,p1.y,my_width,my_height); //Define a Rect object
  rectangle(base,my_rectangle,Scalar(0,0,250),my_thickness,1); //Draw a rectangle (using Rect)
  rectangle(base,p1,p2,Scalar(0,0,200),my_thickness,1); //Draw a rectangle (using two points)

  circle(base,p2,50,Scalar(240,0,0),CV_FILLED,LINE_AA); //Draw a filled circle

  line(base,p1,Point(p1.x+my_width,p1.y+my_height),Scalar(0,250,0),my_thickness,4); //Draw a line

  arrowedLine(base,p2,Point(550,400),Scalar(50,50,0),my_thickness,8,0,my_tipLength);
  //Draw an arrow segment pointing from the first point to the second one

  //Drawing markers
  drawMarker(base,Point(600,500),Scalar(250,250,250),MARKER_CROSS,30,my_thickness,8);
  drawMarker(base,Point(700,500),Scalar(250,250,250),MARKER_DIAMOND,30,my_thickness,8);
  drawMarker(base,Point(800,500),Scalar(250,250,250),MARKER_SQUARE,30,my_thickness,8);
  drawMarker(base,Point(900,500),Scalar(250,250,250),MARKER_STAR,30,my_thickness,8);
  drawMarker(base,Point(1000,500),Scalar(250,250,250),MARKER_TRIANGLE_DOWN,30,my_thickness,8);

  imshow(my_draw_win, base);
  moveWindow(my_draw_win, 100, 50); //Move the window at (x,y) position

  printf("\nPress any key to clear and continue...\n");
  waitKey(0);
  base.setTo(Scalar::all(0)); //Clear the image "base"


  //Drawing polygons
  vector<Point> my_points(4); //Define a polygon knowing the total vertices (vector of Points)
  my_points.at(0) = Point(1050,50); //Assign each point
  my_points.at(1) = Point(1250,250);
  my_points[2] = Point(950,650);
  my_points[3] = Point(1500,800);
  polylines(base,my_points,true,Scalar(255,255,35),my_thickness,8,0);//Polylines only, not filled

  vector<Point> points_list; //Define a polygon without knowing the total vertices (vector of Points)
  points_list.push_back(p1); //Add the point to the list (in the last position)
  points_list.push_back(p2);
  points_list.push_back(Point(600,300));
  fillConvexPoly(base,points_list,Scalar(120,120,120),8,0); //Draw and fill a polygon


  int radius = 20;
  RNG rng(12345); //Random Number Generator

  printf("\nPress any key to continue...\n");
  while(1)
  {
    Scalar random_color(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)); //inside the loop
    for( int i = 0; i < points_list.size(); i++ )
      circle(base, points_list[i], radius, random_color, -1, 8, 0);

    for( int i = 0; i < my_points.size(); i++ )
      circle(base, my_points[i], radius, Scalar(rng.uniform(0,255), rng.uniform(0,255),
                                                 rng.uniform(0,255)), -1, 8, 0 );

    imshow(my_draw_win, base);

    int key = 0; //initialize the variable
    key = waitKey(50); //Wait 50 ms for any key pressed
    if(key > 0) //Some key of the keyboard was pressed
    {
      cout << "key (int): " << key << ", key (char): " << (char)key << endl;
      break;  //Break the while loop
    }
  }


  printf("\nPress any key to clear and continue...\n"); //Another pause
  waitKey(0);
  base.setTo(Scalar::all(0)); //Clear the image "base"


  //--------- READING USER PARAMETERS
  string user_text, user_int;

  if(argc == 3) //User provided data
  {
    user_text = argv[1];
    user_int = argv[2];
  }else{
    printf("\nNot enought parameters. Default parameters are used.\n");
    user_text = "my text";
    user_int = "750";
  }

  int my_fontScale = 3;
  Scalar my_color(0,255,255); //Define a custom color

  Point bl(30,200); //bottom-left point, used by the text
  drawMarker(base,bl,Scalar(250,250,250),MARKER_TRIANGLE_UP,30,my_thickness,8);


  //-------- DRAWING TEXT: consersion from integer to string and vice-versa
  putText(base,"simple text (simplex)",bl,FONT_HERSHEY_SIMPLEX,my_fontScale,my_color,my_thickness,0,false);
  putText(base,"simple text (plain)",bl,FONT_HERSHEY_PLAIN,my_fontScale,my_color,my_thickness,0,true);

  putText(base,user_text+" (duplex)",Point(30,500),FONT_HERSHEY_DUPLEX,my_fontScale,my_color,my_thickness,0);

  putText(base,"conversion i2s: "+int2string(bl.y)+" (complex)",Point(30,650),FONT_HERSHEY_COMPLEX,my_fontScale,my_color,my_thickness,0);

  putText(base,"user_int: "+user_int+" (triplex)",Point(30,750),FONT_HERSHEY_TRIPLEX,my_fontScale,my_color,my_thickness,0);
  putText(base,user_int+" (script_simplex)",Point(string2int(user_int),950),FONT_HERSHEY_SCRIPT_SIMPLEX,my_fontScale,my_color,my_thickness,0);


  imshow(my_draw_win, base);
  moveWindow(my_draw_win, 200, 100); //Move the window at (x,y) position


  printf("\nPress any key to exit\n");
  waitKey(0);

  return 0;
}
