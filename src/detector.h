#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;


class detector {

public:

    detector ()
    {
        load_model();
        setup_camera();
    }

    detector (const char* model_file)
            : cascade_name(model_file)
    {
        load_model();
        setup_camera();
    }

    auto detect ()
    {
        read();

        std::vector<Rect> result;
        Mat image_gray;

        cvtColor(image, image_gray, COLOR_BGR2GRAY);
        equalizeHist(image_gray, image_gray);

        // detect
        cascade.detectMultiScale(image_gray, result, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

        return result;
    }

private:

    bool load_model ()
    {
        if (! cascade.load( cascade_name ))
        {
            return 1;
        };

        return 0;
    }

    bool setup_camera ()
    {
        capture.open(-1);

        if (! capture.isOpened() )
        {
            return 1;
        }

        return 0;
    }

    bool read()
    {
        capture.read(image);

        if ( image.empty() )
        {
            return 1;
        }

        return 0;
    }

    const char* cascade_name = "haarcascade_frontalface_alt.xml";
    CascadeClassifier cascade;
    VideoCapture capture;

public:

    Mat image;

};
