#include <wiringPi.h>
#include <stepper.h>
#include <detector.h>

int main()
{
    if (wiringPiSetup()==-1)
        return 1;

    const stepper step1(15, 16, 1, 4);
    const stepper step2(5, 6, 10, 11);

    detector face_detector ("haarcascade_frontalface_alt.xml");

    while (1)
    {
        const auto faces = face_detector.detect();
        const auto middle_x = face_detector.image.cols/2;
        const auto middle_y = face_detector.image.rows/2;

        if (middle_x > faces[0].x)
        {
            step1.turn(10, 6);
        }
        else if (middle_x < faces[0].x)
        {
            step1.rturn(10, 6);
        }

        if (middle_y > faces[0].y)
        {
            step2.turn(10, 6);
        }
        else if (middle_y < faces[0].y)
        {
            step2.rturn(10, 6);
        }
    }

    return 0;
}
