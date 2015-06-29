========================================
Danboard
========================================

What's Danboard ?
========================================

.. image:: img/danboard.jpg
    :alt: Danboard

`image source <https://www.flickr.com/photos/meaganmakes/14189116565/>`_

license

.. image:: img/cc-by-nc.png
    :alt: CC BY-NC



What's this project doing ?
========================================

**make Danbo keep watching you :P**

we use Raspberry Pi 2 + Raspberry Pi Camera Module + ULN2003 + Stepper Motor

use camera to get image of current scene, then detect the faces, control stepper to turn Danbo's face



Algorithm - Viola–Jones object detection framework
==================================================

**Viola–Jones object detection framework** is a **real-time** object detection framework proposed in 2001 by Paul Viola and Michael Jones.

There are 4 primary steps :

* Haar Features Selection
* Creating Integral Image
* Adaboost Training algorithm
* Cascaded Classifiers

Haar Features Selection
------------------------------

**Haar features** consider adjacent rectangular regions at a specific location in a detection window,
sums up the pixel intensities in each region and calculates the difference between these sums.

The advantage of using Haar features is the **fast calculation speed**.


Creating Integral Image
------------------------------

In **integral image**,
each pixel is the sum of all pixels in the original image which are left and above.

like this : ::

    Original        Integral

    1, 2, 3         0,  0,  0,  0
    4, 5, 6         0,  1,  3,  6
    7, 8, 9         0,  5, 12, 21
                    0, 12, 27, 45

calculation : ::

    Original        Integral

    1, 2, 3         0,  0,  0,  0
    4, 5, 6         0,   ,   ,
    7, 8, 9         0,   ,   ,
                    0,   ,   ,



    Original        Integral

    ( 1 ), 2, 3         0, ( 0 ),  0,  0
        4, 5, 6     ( 0 ), [ 1 ],   ,
        7, 8, 9         0,      ,   ,
                        0,      ,   ,

            calculation : 0 + 0 + 1 = 1



    Original        Integral

    1, ( 2 ), 3     0,   0  , ( 0 ),  0
    4,     5, 6     0, ( 1 ), [ 3 ],
    7,     8, 9     0,      ,      ,
                    0,      ,      ,

            calculation : 0 + 1 + 2 = 3



    Original        Integral

    1, 2, ( 3 )     0, 0,     0, ( 0 )
    4, 5,     6     0, 1, ( 3 ), [ 6 ]
    7, 8,     9     0,  ,      ,
                    0,  ,      ,

            calculation : 0 + 3 + 3 = 6



    Original        Integral

        1, 2, 3         0,     0, 0, 0
    ( 4 ), 5, 6         0, ( 1 ), 3, 6
        7, 8, 9     ( 0 ), [ 5 ], ,
                        0,      , ,

            calculation : 1 + 0 + 4 = 5


    ...


    Original        Integral

    1, 2, 3         0,  0,  0,  0
    4, 5, 6         0,  1,  3,  6
    7, 8, 9         0,  5, 12, 21
                    0, 12, 27, 45


Adaboost Training algorithm
------------------------------

**AdaBoost** is a machine learning algorithm which can collaborate with many other types of learning algorithms to improve their performance.

The concept is to combine some **weak classifier** into a weighted sum to make a **strong classifier**.


Cascaded Classifiers
------------------------------



License
========================================

`GPL v3 <LICENSE>`_



Reference
========================================

* `Wikipedia - Viola–Jones object detection framework <https://en.wikipedia.org/wiki/Viola%E2%80%93Jones_object_detection_framework>`_
* `Wikipedia - Haar-like features <https://en.wikipedia.org/wiki/Haar-like_features>`_
* `Wikipedia - AdaBoost <https://en.wikipedia.org/wiki/AdaBoost>`_
