#include "encoder.h"


void HallEncoder::set_cnt(unsigned int cnt) {
    _EncoderCntsperRev = cnt;
}

void HallEncoder::set_sample_time(unsigned int time_us) {
    _SampleTime_us = time_us;
}

void HallEncoder::ISR_A(void)
{
    if(_encoder_A.read() ^ _encoder_B.read()) {
        _pulses -= 1 ;
    }
    else {
        _pulses += 1 ;
    }
}

void HallEncoder::calcRPM(void)
{
    _cur_cnt = _pulses;
    _rpm = float(_cur_cnt-_prev_cnt)/float(_EncoderCntsperRev)/(float(_SampleTime_us)*1.e-6)*60.0;
    _prev_cnt = _cur_cnt;
}

float HallEncoder::getRPM() {
    return _rpm;
}

long HallEncoder::getPosition() {
    return _cur_cnt;
}
