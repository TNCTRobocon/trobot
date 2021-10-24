#pragma once
#ifndef __HEADER_GUARD_TROBOTLIB_UNITS_MD__
#define __HEADER_GUARD_TROBOTLIB_UNITS_MD__

#include <cassert>

#include <memory>
#include <parts/pins.hpp>

namespace trb::units::motors {
// alias
using parts::pins::Output;
using parts::pins::PWM;

struct Motor {
    virtual ~Motor() = default;
    virtual void write(float);
    virtual void stop() { write(0); }
};

class PABMotor : public Motor {
    std::unique_ptr<PWM> p;
    std::unique_ptr<Output> a, b;

public:
    PABMotor(std::unique_ptr<PWM> _p, std::unique_ptr<Output> _a,
             std::unique_ptr<Output> _b);
    PABMotor(const PABMotor &) = delete;
    PABMotor(PABMotor &&x) = delete;
    virtual ~PABMotor() = default;
    virtual void write(float x);
    virtual void stop();
};

class PABMotorBuilder {
    std::unique_ptr<PWM> p = nullptr;
    std::unique_ptr<Output> a = nullptr, b = nullptr;

public:
    PABMotorBuilder() = default;
    PABMotorBuilder &setP(std::unique_ptr<PWM> _p);
    PABMotorBuilder &setA(std::unique_ptr<Output> _a);
    PABMotorBuilder &setB(std::unique_ptr<Output> _b);
    std::unique_ptr<Motor> build();
};

class PQMotor : public Motor {
    std::unique_ptr<PWM> p, q;

public:
    PQMotor(std::unique_ptr<PWM> _p, std ::unique_ptr<PWM> _q)
        : p(std::move(_p)), q(std::move(_q)) {
        assert(p), assert(q);
    }
    PQMotor(const PQMotor &) = delete;
    PQMotor(PQMotor &&x) = delete;
    virtual ~PQMotor() = default;
    virtual void write(float x);
    virtual void stop();
};

class PQMotorBuilder {
    std::unique_ptr<PWM> p = nullptr, q = nullptr;

public:
    PQMotorBuilder() = default;
    PQMotorBuilder &setP(std::unique_ptr<PWM> &_p);
    PQMotorBuilder &setQ(std::unique_ptr<PWM> &_q);
    std::unique_ptr<Motor> build();
};

#ifdef TRB_PSEUDO
namespace pseudo {
struct Motor {
    float value;
    Motor(float _value) : value(_value) {}
    virtual ~Motor() = default;
    virtual void write(float _value) { value = _value; }
};
} // namespace pseudo
#endif /* TRB_PSEUDO*/

} // namespace trb::units::motors

#endif /*/__HEADER_GUARD_TROBOTLIB_UNITS_MD__*/