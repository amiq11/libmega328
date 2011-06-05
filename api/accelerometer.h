#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <math.h>


typedef enum _ACCEL{
    Z=0,
    Y=1,
    X=2
} ACCEL_t;


/* uint16_t get_accel_direct(ACCEL_t id); */
void save_accel_horizontal(void);
void load_accel_horizontal(void);
int16_t get_accel(ACCEL_t id);
uint16_t get_accel_abs(void);

#endif /* Not def: ACCELEROMETER_H */
