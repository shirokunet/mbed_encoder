#ifndef HallEncoder_h
#define HallEncoder_h

#include "mbed.h"

class HallEncoder
{
    public:
        HallEncoder(PinName pin_A, PinName pin_B, unsigned int time_us = 100000)
                    : _encoder_A(pin_A), _encoder_B(pin_B)
        {
            set_sample_time(time_us);
            set_cnt();
            _encoder_A.rise(callback(this, &HallEncoder::ISR_A));
            _tkRPM.attach_us(callback(this, &HallEncoder::calcRPM), _SampleTime_us);
            _pulses = 0;
            _prev_cnt = 0;
            _cur_cnt = 0;
            _rpm = 0.0;
        }

        float getRPM(void);
        long getPosition(void);

    private:
        InterruptIn _encoder_A;
        InterruptIn _encoder_B;
        Ticker _tkRPM;

        unsigned int _EncoderCntsperRev;
        unsigned int _SampleTime_us;
        volatile float _rpm;
        volatile long _pulses;
        long _prev_cnt, _cur_cnt;

        void set_cnt(unsigned int cnt = 20);
        void set_sample_time(unsigned int time_us);
        void ISR_A(void);
        void calcRPM(void);
};

#endif /* HallEncoder_h */
