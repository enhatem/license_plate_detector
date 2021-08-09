#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp> // Allows us to work with haarcascade files
#include <iostream>

using namespace std;
using namespace cv;


int main(){

    VideoCapture cap(0); // Since I only have 1 camera on the Laptop, the ID is 0
    Mat img;

    CascadeClassifier plateCascade;
    plateCascade.load("/home/elie/tutorials/c++/openCV/license_plate_detector/Resources/haarcascade_russian_plate_number.xml");

    if (plateCascade.empty()){cout << "XML file not loaded" << endl;}

    vector<Rect> plates;

    while(true){

        cap.read(img);

        plateCascade.detectMultiScale(img, plates,1.1,10); // the values can be tuned to improve the plates detection

        for (int i=0; i<plates.size(); i++)
        {   
            Mat imgCrop = img(plates[i]); // cropping the image using the dimensions (point, width and height) of the detected plates
            //imshow(to_string(i),imgCrop);
            imwrite("/home/elie/tutorials/c++/openCV/license_plate_detector/Resources/plates/"+ to_string(i) + ".png", imgCrop); // saving the detected (cropped) plate
            rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3); // Drawing the bounding box using the rectangle - boundRect[i].tl(): calls the top left point - boundRect[i].br(): calls the bottom right point
        }

        imshow("Image",img);
        waitKey(1);
    }
    return 0;
}