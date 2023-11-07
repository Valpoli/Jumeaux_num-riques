#pragma once

#if __cpp_exceptions

#include <mcpwm_cxx.hpp>

namespace idf {

class BdcMotor
{
public:
    BdcMotor(GPIONum pwmAGpio, GPIONum pwmBGpio, uint32_t pwmFreqHz, int groupId, uint32_t timerResolutionHz);
    ~BdcMotor();

    void enable();
    void disable();
    void setSpeed(uint32_t speed);
    void forward();
    void reverse();
    void coast();
    void brake();

private:
    BdcMotor(const BdcMotor &) = delete;
    BdcMotor & operator=(const BdcMotor &) = delete;

    idf::mcpwm::Timer _timer;
    idf::mcpwm::Operator _operat;
    idf::mcpwm::Comparators _cmpa;
    idf::mcpwm::Comparators _cmpb;
    idf::mcpwm::Generators _gena;
    idf::mcpwm::Generators _genb;
};

} // idf

#endif // __cpp_exceptions
