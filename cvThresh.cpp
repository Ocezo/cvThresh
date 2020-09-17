// Have a look to: https://docs.opencv.org/3.4/d4/d7d/tutorial_harris_detector.html

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/// Global variables
int threshold_value = 80;
int const max_value = 255;

int threshold_canny_value_1 = 50;
int threshold_canny_value_2 = 100;
int const max_canny_value = 100;

Mat camFrame, grayFrame, binFrame, cannyFrame;

const char* threshed_window = "Binary";
const char* canny_window    = "Canny";

/// Function headers
void Threshold_Demo( int, void* );
void Canny_Demo( int, void* );

int main() {
    VideoCapture stream1(0);   // 0 is the id of video device.0 if you have only one camera.
    if (!stream1.isOpened()) { // check if video device has been initialized
        cout << "cannot open camera";
    }

    while (true) {
        stream1.read(camFrame);
        imshow("Camera", camFrame);

        cvtColor( camFrame, grayFrame, COLOR_BGR2GRAY );
        //imshow("Grayscale", grayFrame);

        createTrackbar( "Threshold: ", threshed_window, &threshold_value, max_value, Threshold_Demo);
        Threshold_Demo( 0, 0 );

        createTrackbar( "Threshold 1: ", canny_window, &threshold_canny_value_1, max_canny_value, Canny_Demo);
        createTrackbar( "Threshold 2: ", canny_window, &threshold_canny_value_2, max_canny_value, Canny_Demo);
        Canny_Demo( 0, 0 );

        if (waitKey(30) >= 0 )
            break;
    }

    return 0;
}

void Threshold_Demo( int, void* )
{
    threshold( grayFrame, binFrame, threshold_value, max_value, THRESH_BINARY );
    imshow( threshed_window, binFrame );
}

void Canny_Demo( int, void* )
{
	Canny( grayFrame, cannyFrame, threshold_canny_value_1, threshold_canny_value_2, 3, true );
	imshow("Canny", cannyFrame);
}
