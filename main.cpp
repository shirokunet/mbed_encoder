#include "mbed.h"
#include "encoder.h"

HallEncoder encoder(p5, p6);
Serial pc(USBTX, USBRX, 115200);

int main() 
{
    while(1)
    {
        pc.printf("%d, %f\r\n", encoder.getPosition(), encoder.getRPM());
        wait_ms(100);
    }
}
