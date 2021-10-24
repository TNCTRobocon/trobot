#include "units/motors.hpp"
#include <cmath>
using std::move;
using std::unique_ptr;

namespace trb::units::motors {

// PABMotor
PABMotor::PABMotor(unique_ptr<PWM> _p, unique_ptr<Output> _a,
                   unique_ptr<Output> _b)
    : p(move(_p)), a(move(_a)), b(move(_b)) {
    assert(p), assert(a), assert(b);
}

void PABMotor::write(float x) {
    p->write(fabs(x));
    a->write(x > 0), b->write(x < 0);
}

void PABMotor::stop() {
    p->write(0);
    a->write(false), b->write(false);
}

// PABMotorBuilder

PABMotorBuilder &PABMotorBuilder::setP(std::unique_ptr<PWM> _p) {
    p = std::move(_p);
    return *this;
}

PABMotorBuilder &PABMotorBuilder::setA(std::unique_ptr<Output> _a) {
    a = std::move(_a);
    return *this;
}

PABMotorBuilder &PABMotorBuilder::setB(std::unique_ptr<Output> _b) {
    b = std::move(_b);
    return *this;
}

std::unique_ptr<Motor> PABMotorBuilder::build() {
    assert(p), assert(a), assert(b);
    return std::unique_ptr<Motor>(
        new PABMotor(std::move(p), std::move(a), std::move(b)));
}

// PQMotor

PQMotor::PQMotor(std::unique_ptr<PWM> _p, std ::unique_ptr<PWM> _q)
    : p(std::move(_p)), q(std::move(_q)) {
    assert(p), assert(q);
}

void PQMotor::write(float x) {
    if (x > 0) {
        p->write(fabs(x)), q->write(0);
    } else {
        p->write(0), q->write(fabs(x));
    }
}

void PQMotor::stop() { p->write(0), q->write(0); }

// PQMotorBuilder

PQMotorBuilder &PQMotorBuilder::setP(std::unique_ptr<PWM> &_p) {
    p = std::move(_p);
    return *this;
}

PQMotorBuilder &PQMotorBuilder::setQ(std::unique_ptr<PWM> &_q) {
    q = std::move(_q);
    return *this;
}

std::unique_ptr<Motor> PQMotorBuilder::build() {
    return std::unique_ptr<Motor>(new PQMotor(std::move(p), std::move(p)));
}

} // namespace trb::units::motors