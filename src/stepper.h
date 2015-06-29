#include <future>         // std::async, std::future
#include <iterator>       // std::rbegin, std::rend
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

    void turn(const unsigned int time, const unsigned int steps, const bool reverse = 0) const
    {
        static bool table[][4] = { { 1, 0, 0, 0 },
                                   { 1, 1, 0, 0 },
                                   { 0, 1, 0, 0 },
                                   { 0, 1, 1, 0 },
                                   { 0, 0, 1, 0 },
                                   { 0, 0, 1, 1 },
                                   { 0, 0, 0, 1 },
                                   { 1, 0, 0, 1 }, };

        if (!reverse)
        {
            for (unsigned int i = 0; i <= steps; i++)
            {
                for (auto& p : table)
                {
                    setStep(p[0], p[1], p[2], p[3]);
                    delay(time);
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i <= steps; i++)
            {
                for (auto it = std::rbegin(table); it != std::rend(table); it++)
                {
                    const auto& p = *it;
                    setStep(p[0], p[1], p[2], p[3]);
                    delay(time);
                }
            }
        }
    }

    template<typename... Args>
    void rturn(Args&&... args) const
    {
        turn(std::forward<Args>(args)..., 1);
    }

    template<typename... Args>
    std::future<void> async_turn(Args&&... args) const
    {
        // explicitly use std::launch::async to force program use thread
        return std::async (std::launch::async, &stepper::turn, this, std::forward<Args>(args)..., 0);
    }

    template<typename... Args>
    std::future<void> async_rturn(Args&&... args) const
    {
        // explicitly use std::launch::async to force program use thread
        return std::async (std::launch::async, &stepper::rturn<Args...>, this, std::forward<Args>(args)...);
    }

private:

    void setUp() const
    {
        pinMode(stepper1, OUTPUT);
        pinMode(stepper2, OUTPUT);
        pinMode(stepper3, OUTPUT);
        pinMode(stepper4, OUTPUT);
    }

    const unsigned char stepper1 = 15;
    const unsigned char stepper2 = 16;
    const unsigned char stepper3 = 1;
    const unsigned char stepper4 = 4;
};
