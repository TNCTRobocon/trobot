#include "parts/pins.hpp"
#include "gtest/gtest.h"

using namespace std;

namespace trb::parts::pins{

#ifdef TRB_PSEUDO

namespace pseudo{

TEST(PSUEDO_DIGITAL_PINS, WRITE) {
    Digital d(false);
    EXPECT_EQ(d.value,false);
    d.write(true);
    EXPECT_EQ(d.value,true);
}

TEST(PSUEDO_DIGITAL_PINS, READ) {
    Digital d(false);
    EXPECT_EQ(d.read(),false);
    d.value = true;
    EXPECT_EQ(d.read(),true);
}

TEST(PSUEDO_ADC_PINS, READ) {
    ADC a(0);
    EXPECT_EQ(a.read(),0);
    a.value=1;
    EXPECT_EQ(a.read(),1);
}
TEST(PSUEDO_DAC_PINS, READ) {
    DAC d(0);
    EXPECT_EQ(d.value,0);
    d.write(1);
    EXPECT_EQ(d.value, 1);
}
}
#endif

}