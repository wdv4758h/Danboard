#include <future>         // std::async, std::future
#include <wiringPi.h>


class stepper {

public:

    constexpr stepper () { setUp(); }

    constexpr stepper (unsigned char stepper1,
                       unsigned char stepper2,
                       unsigned char stepper3,
                       unsigned char stepper4)
                     : stepper1(stepper1),
                       stepper2(stepper2),
                       stepper3(stepper3),
                       stepper4(stepper4)
    {
        setUp();
    }

    void setStep(const bool w1,
                 const bool w2,
                 const bool w3,
                 const bool w4) const
    {
        // set step

        digitalWrite(stepper1, w1);
        digitalWrite(stepper2, w2);
        digitalWrite(stepper3, w3);
        digitalWrite(stepper4, w4);
    }

    void prawo(const unsigned int time, const unsigned int steps) const
    {
        // move right

        for (unsigned int i=0; i <= steps; i++)
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
    }

    void lewo(const unsigned int time, const unsigned int steps) const
    {
        // move left

        for (unsigned int i=0; i <= steps; i++)
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
    }

    template<typename... Args>
    std::future<void> async_prawo(Args... args) const
    {
        // explicitly use std::launch::async to force program use thread
        return std::async (std::launch::async, &stepper::prawo, this, std::forward<Args>(args)...);
    }

    template<typename... Args>
    std::future<void> async_lewo(Args... args) const
    {
        // explicitly use std::launch::async to force program use thread
        return std::async (std::launch::async, &stepper::lewo, this, std::forward<Args>(args)...);
    }

private:

    void setUp() const
    {
        pinMode(stepper1, OUTPUT);
        pinMode(stepper2, OUTPUT);
        pinMode(stepper3, OUTPUT);
        pinMode(stepper3, OUTPUT);
    }

    const unsigned char stepper1 = 15;
    const unsigned char stepper2 = 16;
    const unsigned char stepper3 = 1;
    const unsigned char stepper4 = 4;
};



int main()
{
    if (wiringPiSetup()==-1)
        return 1;

    const stepper step1;
    const stepper step2(5,6,10,11);

    while (1)
    {
        auto f1 = step1.async_lewo(10,60);
        auto f2 = step2.async_prawo(10,60);

        delay(500);

        f1.get();
        f2.get();

        f1 = step1.async_prawo(10,60);
        f2 = step2.async_lewo(10,60);

        delay(500);

        f1.get();
        f2.get();
    }

    return 0;
}
