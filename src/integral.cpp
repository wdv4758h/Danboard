#include "opencv2/core/core.hpp"

using namespace cv;


Mat integral(Mat& image)
{
    /*

        Each pixel in the result is the sum of all pixels in the original image which are left and above.

        Original        Integral

        [ 1, 2, 3;      [ 0,  0,  0,  0;
          4, 5, 6;        0,  1,  3,  6;
          7, 8, 9 ]       0,  5, 12, 21;
                          0, 12, 27, 45 ]

    */

    const unsigned int rows = image.rows;
    const unsigned int cols = image.cols;

    Mat result(rows + 1, cols + 1, image.type(), Scalar(0));

    int sum = 0;

    for (unsigned int i = 0; i < rows; i++)
    {
        sum = 0;

        for (unsigned int j = 0; j < cols; j++)
        {
            sum += image.at<int>(i, j);
            result.at<int>(i+1, j+1) = result.at<int>(i, j+1) + sum;
        }
    }

    return result;
}
