#include <wiringPi.h>

int i;

int prawo(int time, int steps)          //move right
{

    digitalWrite(3,1);              //LED1 ON

    for(i=0;i<=steps;i++)
    {

        setStep(1,0,0,0);
        delay(time);
        setStep(1,1,0,0);
        delay(time);
        setStep(0,1,0,0);
        delay(time);
        setStep(0,1,1,0);
        delay(time);
        setStep(0,0,1,0);
        delay(time);
        setStep(0,0,1,1);
        delay(time);
        setStep(0,0,0,1);
        delay(time);
        setStep(1,0,0,1);
        delay(time);
    }

    digitalWrite(3,0);              //LED1 OFF
};

int lewo(int time, int steps)                       //move left
{

    digitalWrite(2,1);              //LED2 ON

    for(i=0;i<=steps;i++)
    {
        setStep(0,0,0,1);
        delay(time);
        setStep(0,0,1,1);
        delay(time);
        setStep(0,0,1,0);
        delay(time);
        setStep(0,1,1,0);
        delay(time);
        setStep(0,1,0,0);
        delay(time);
        setStep(1,1,0,0);
        delay(time);
        setStep(1,0,0,0);
        delay(time);
        setStep(1,0,0,1);
        delay(time);
    }

    digitalWrite(2,0);              //LED2 OFF
};

int setStep(int w1, int w2, int w3, int w4)                            //set step
{

    digitalWrite(6,w1);
    digitalWrite(5,w2);
    digitalWrite(0,w3);
    digitalWrite(4,w4);
};

int main(void)
{

    if(wiringPiSetup()==-1) exit(1);

    pinMode(0,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);

    while(1)
    {
        prawo(10,6);
        delay(500);
        prawo(10,6);
        delay(500);
        lewo(10,6);
        delay(500);
        lewo(10,6);
        delay(500);
    }

    return 0;
}
