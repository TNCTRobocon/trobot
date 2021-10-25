#pragma once
#ifndef __HEADER_GUARD_TROBOTLIB_UNITS_MD__
#define __HEADER_GUARD_TROBOTLIB_UNITS_MD__

#include <cassert>
#include <cmath>
#include <parts/pins.hpp>

namespace trb::units::motors {

/* NOTE:
 * 内包を当初unique_ptrで実装していたが、テストベンチする際にunique_ptrでは不都合が生じる。そして、
 * 最終的に実装されるのはマイコンであり、deleteをあまり考慮する必要はない。
 * オーバーヘッドを防ぐために古典的な生ポインタを用いて実装する。
 * なお、理想的な実装はC++20のconceptを用いたパターンはであるが、C++20は新しすぎる。また、templateを
 * 駆使した方法は可読性にかける点から選択していない。
 */

using PWM = parts::pins::PWM;
using Output = parts::pins::Output;

struct Motor {
    virtual ~Motor() = default;
    virtual void write(float);
    virtual void stop() { write(0); }
};

class PABMotor : public Motor {
    PWM *p;
    Output *a, *b;

public:
    PABMotor(PWM *_p, Output *_a, Output *_b) : p(_p), a(_a), b(_b) {
        assert(p), assert(a), assert(b);
    }
    PABMotor(const PABMotor &) = delete;
    virtual ~PABMotor() { delete p, delete a, delete b; }
    virtual void write(float x) {
        p->write(fabs(x));
        a->write(x > 0), b->write(x < 0);
    }

    virtual void stop() {
        p->write(0);
        a->write(false), b->write(false);
    }
};

class PQMotor : public Motor {
    PWM *p, *q;

public:
    PQMotor(PWM *_p, PWM *_q) : p(_p), q(_q) { assert(p), assert(q); }
    PQMotor(const PQMotor &) = delete;
    virtual ~PQMotor() { delete p, delete q; }
    virtual void write(float x) {
        if (x > 0) {
            p->write(fabs(x)), q->write(0);
        } else {
            p->write(0), q->write(fabs(x));
        }
    }
    virtual void stop();
};

class NegMotor : public Motor {
    Motor *motor;

public:
    NegMotor(Motor *_motor) : motor(_motor) { assert(motor); }
    NegMotor(const NegMotor &) = delete;
    virtual ~NegMotor() { delete motor; }
    virtual void write(float x) { motor->write(-x); }
    virtual void stop() { motor->stop(); }
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