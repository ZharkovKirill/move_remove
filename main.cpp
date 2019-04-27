#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>
using  namespace cv;
using std::endl; using std::cout;
struct accumulator{
    Mat accum;
    float q;
    void push(Mat obj)
    {
        accum = accum*q + obj*(1-q);
    }
};
int main()
{

    bool run = true;
    Mat frame,diff,res;
    int num_frame,freq_A,freq_B,freq_diff,tres = 1;
    int q_A,q_B = 0;
    VideoCapture cam(0);
    if(!cam.isOpened())
        return -1;

    cout<<"Start"<<endl;
    cout << "FPS: " << cam.get(CAP_PROP_FPS) << endl;
    cout<<"//////"<<endl;
    accumulator A,B;
    A.q = 0.4;
    B.q = 0.7;

    cam>>frame;
    cvtColor(frame,frame, COLOR_RGB2GRAY);

    frame.copyTo(A.accum);
    frame.copyTo(B.accum);

    namedWindow("Setting", WINDOW_AUTOSIZE);
    createTrackbar("Freq_A","Setting",&freq_A,60);
    createTrackbar("Freq_B","Setting",&freq_B,60);
    createTrackbar("Freq_diff","Setting",&freq_diff,60);
    createTrackbar("q_A","Setting",&q_A,100);
    createTrackbar("q_B","Setting",&q_B,100);
    createTrackbar("q_B","Setting",&tres,255);

    absdiff(A.accum, B.accum, diff);
    while(run)
    {
        num_frame++;
        cam>>frame;
        cvtColor(frame,frame, COLOR_RGB2GRAY);
        A.q = float(q_A/100);
        B.q = float(q_B/100);

        if( num_frame % (freq_A + 1)  == 0) {
            A.push(frame);

        }
        if( num_frame%(freq_B+1) == 0) {
            B.push(frame);
        }
        if( num_frame%(freq_diff+1) == 0) {
            absdiff( A.accum ,  B.accum , diff);
        }
        threshold(diff,diff,tres,255,THRESH_BINARY );
        bitwise_and(frame,diff,res);
        imshow("A", A.accum);
        imshow("B", B.accum);
        imshow("Diff", res);

        int key = waitKey(1);
        if (key == 27/*ESC*/)
            run = false;
    }

    return 0;
}