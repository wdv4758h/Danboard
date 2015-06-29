#include <wiringPi.h>
#include <stepper.h>


int main()
{
    if (wiringPiSetup()==-1)
        return 1;

    const stepper step1;
    const stepper step2(5,6,10,11);

    while (1)
    {
        auto f1 = step1.async_turn(10,60);
        auto f2 = step2.async_turn(10,30);
        f1.get();
        f2.get();

        f2 = step2.async_rturn(10,60);
        f2.get();

        f1 = step1.async_rturn(10,120);
        f2 = step2.async_turn(10,60);
        f1.get();
        f2.get();

        f2 = step2.async_rturn(10,60);
        f2.get();

        f1 = step1.async_turn(10,60);
        f2 = step2.async_turn(10,30);
        f1.get();
        f2.get();
    }

    return 0;
}
