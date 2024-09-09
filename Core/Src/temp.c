#include "main.h"
#include "temp.h"
#include "HDC2021.h"


void startReadTempTask(void *argument) {
    HDC2021 hdc2021;
    uint8_t err;
    err = HDC2021_Init(&hdc2021, &hi2c1);
    
    float temp;
    for(;;) {
        HDC2021_Read_Temp(&hdc2021);
        temp = hdc2021.temp;
        osDelay(1000);
    }
}
