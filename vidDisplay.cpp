#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <math.h>
#include "filters.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
        Mat Image;
        Mat gray_scale;
        Mat sobelx;
        Mat sobely;
        Mat local, temp;
    // live video

        VideoCapture *capdev;

       

        capdev = new VideoCapture(0);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }
        

        Size refS(  (int) capdev->get(CAP_PROP_FRAME_WIDTH ),
                    (int) capdev->get(CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);
        
        
        namedWindow("Video", 1); 
        int c,flag=0,num=0;

        while(true){
            *capdev >> Image; 
            if( Image.empty() ) {
                printf("frame is empty\n");
                break;
            }
            if(flag==11){
                Image.copyTo(local);
                cartoon(Image,local);
                imshow("cartoon",local);
            }
            
            else if(flag==10){
                    cvtColor(Image,gray_scale,COLOR_BGR2GRAY);
                    imshow("gray_image",gray_scale);
            }

            if(flag==9){
                Mat local(Image.rows, Image.cols, CV_8UC1, Scalar(0));
                greyscale(Image,local);
                imshow("new_greyimage",local);
            }
            else if(flag==8){
                Image.copyTo(temp);
                blur5x5(Image,temp);
                temp.copyTo(local);
                blur5x5(temp,local);
                imshow("blur",local);
            }
               
            else if(flag==7){
                Mat local(Image.rows, Image.cols, CV_16SC3);
                sobelX3x3(Image,local);
                imshow("sobelx",local);
            }
            else if(flag==6){
                Mat local(Image.rows, Image.cols, CV_16SC3);
                sobelY3x3(Image,local);
                imshow("sobely",local);
            }
            else if(flag==5){
                Mat sx(Image.rows, Image.cols, CV_16SC3);
                Mat sy(Image.rows, Image.cols, CV_16SC3);
                Image.copyTo(local);
                sobelX3x3(Image, sx);
                sobelY3x3(Image, sy);
                magnitude(sx,sy,local);
                imshow("Gradient_Magn",local);
            }

            else if(flag==4){
                Image.copyTo(local);
                blurQuantize(Image,local,10);
                imshow("BlurQuantize",local);
            }
            else if(flag==3){
                Image.copyTo(local);
                Neg(Image,local);
                imshow("Negative",local);
            }
           
            else{
                
                imshow("Video",Image);
                
            }

            char key = waitKey(10); 

            if (key=='c'){
                destroyAllWindows();
                num++;
                flag =11*(num%2);
                 
            } 

            if (key=='g'){
                destroyAllWindows();
                num++;
                flag =10*(num%2);
            }
            if (key=='w'){
                destroyAllWindows();
                num++;
                flag =9*(num%2);
              
            }
            if (key=='b'){
                destroyAllWindows();
                num++;
                flag =8*(num%2);
               
            }
            if (key=='x'){
                destroyAllWindows();
                num++;
                flag =7*(num%2);
               
            }
            if (key=='y'){
                destroyAllWindows();
                num++;
                flag =6*(num%2);
               
            }
            if (key=='m'){
                destroyAllWindows();
                num++;
                flag =5*(num%2);
            }
             if (key=='n'){
                 destroyAllWindows();
                num++;
                flag =3*(num%2);   
            }
            if (key == 'u'){
                destroyAllWindows();
                num++;
                flag =4*(num%2);
            }
        
            if(key=='q'){
                destroyAllWindows();
                break;
            }
            if(key='s'){
                imwrite("saveimage.jpg",Image);
            } 
        
        }
    destroyAllWindows;
    delete capdev;
    return(0);
}




