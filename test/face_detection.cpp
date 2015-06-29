#include <detector.h>

int main ()
{

    detector face ("haarcascade_frontalface_alt.xml");

    while (1)
    {
        const auto faces = face.detect();

        Mat& frame = face.image;

        for ( size_t i = 0; i < faces.size(); i++ )
        {
            const Point center( faces[i].x + faces[i].width/2,
                                faces[i].y + faces[i].height/2 );

            ellipse( frame,     // image
                     center,
                     Size( faces[i].width/2, faces[i].height/2 ),   // axes
                     0,                         // angle
                     0, 360,                    // startAngle, endAngle
                     Scalar( 255, 0, 255 ),     // color
                     4, 8, 0 );                 // thickness, lineType, shift
        }

        // show the result
        imshow("Test", frame);

        char c = waitKey(10);

        // ESC
        if (c == 27)
            break;
    }

    return 0;
}
