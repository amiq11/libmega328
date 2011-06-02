#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

typedef enum _ACCEL{
    Z=0,
    Y,
    X
} ACCEL_t;


void save_accel_horizontal(void);

#endif /* Not def: ACCELEROMETER_H */
