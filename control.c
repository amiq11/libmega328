#include "library.h"
#include "api.h"

/* 1/4msごとにcontrol()が呼ばれる */


void control(void){
    led_control();              /* この関数によりledがダイナミック点灯する */
}

