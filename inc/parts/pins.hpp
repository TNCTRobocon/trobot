#pragma once
#ifndef __HEADER_GUARD_TROBOTLIB_PARTS_PINS__
#define __HEADER_GUARD_TROBOTLIB_PARTS_PINS__

#include <cassert>
#include <cmath>
#include <cstdint>
#include <tuple>

namespace trb::parts::pins {

/* 本当は実行速度の観点からC++20のconceptで実装したいが、
 * stm32cubeはC++17までしかサポートしていないため、
 * 古典的な方法であるインターフェイスクラスによる実装を行う。
 */

struct Input {
    virtual ~Input() = default;
    virtual bool read() = 0;
};

struct Output {
    virtual ~Output() = default;
    virtual void write(bool) = 0;
    virtual void set() { write(true); }
    virtual void clear() { write(true); }
};

struct ADC {
    virtual ~ADC() = default;
    virtual float read() = 0;
};

struct DAC {
    virtual ~DAC() = default;
    virtual void write(float) = 0;
};

using PWM = DAC;

class InvertInput : Input {
    Input *input;

public:
    InvertInput(Input *_input) : input(_input) { assert(input); }
    InvertInput(const InvertInput *) = delete;
    virtual ~InvertInput() { delete input; }
    virtual bool read() { return !input->read(); }
};

class InvertOutput : Output {
    Output *output;

public:
    InvertOutput(Output *_output) : output(_output) { assert(output); }
    InvertOutput(const InvertOutput *) = delete;
    virtual ~InvertOutput() { delete output; }
    virtual void write(bool x) { return output->write(!x); }
    virtual void set() { return output->clear(); }
    virtual void clear() { return output->set(); }
};

#ifdef TRB_PSEUDO

/* パソコンで擬似的にGPIOを操作するときに用いるクラス
　　主に単体テストやシミュレーションに用いる
*/

namespace pseudo {

struct Digital : public pins::Input, pins::Output {
    bool value;
    Digital(bool _value = false) : value(_value) {}
    virtual ~Digital() = default;
    virtual void write(bool _value) { value = _value; }
    virtual bool read() { return value; }
};

struct ADC : public pins::ADC {
    float value;
    ADC(float _value = 0) : value(_value) {}
    virtual ~ADC() = default;
    virtual float read() { return value; }
};

struct DAC : public pins::DAC {
    float value;
    DAC(float _value = 0) : value(_value) {}
    virtual ~DAC() = default;
    virtual void write(float _value) { value = _value; }
};
} // namespace pseudo

#endif /* TRB_PSEUDO */

} // namespace trb::parts::pins

#endif /* __HEADER_GUARD_TROBOTLIB_PARTS_PINS__ */
