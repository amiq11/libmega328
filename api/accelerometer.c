/* 加速度センサを用いるためのAPI */

#include "library.h"
#include "api.h"
#include <avr/eeprom.h>

/* #define EEMEM __attribute__((section(".eeprom"))) */

/* 水平のときの値 */
/* static uint16_t horizontal_val_eemem_x EEMEM; /\* EEPROMに保存された値 *\/ */
/* static uint16_t horizontal_val_eemem_y EEMEM; */
/* static uint16_t horizontal_val_eemem_z EEMEM; */
/* static uint16_t EEMEM horizontal_val_eemem[3]; */
/* static uint8_t  EEMEM horizontal_flag_eemem  ; /\* EEPROMに保存されたフラグ *\/ */

#define HORIZONTAL_FLAG_EEMEM 0x00
#define HORIZONTAL_VAL_X_EEMEM 0x01
#define HORIZONTAL_VAL_Y_EEMEM 0x03
#define HORIZONTAL_VAL_Z_EEMEM 0x05

static uint16_t horizontal_val[3];     /* EEPROMから読み込んだ値 */




/* id:X Y Z */
/* ただ0-1024をadcして返す */
/* save_accel_horizontalした値は関係ない */
uint16_t get_accel_direct(ACCEL_t id){
    switch(id){
    case X:
        return read_adc(2);
    case Y:
        return read_adc(1);
    case Z:
        return read_adc(0);
    }
    return 0xFFFF;
}



/* 水平にしてからこの関数を実行する。 */
void save_accel_horizontal(void){
    uint16_t datalog[3] = {0};
    uint8_t i;

    for(i=0;i<16;i++){
        datalog[X] += get_accel_direct(X);
#ifdef DEBUG_PRINT
        printf("%04d ",datalog[X]);
#endif /* Def: DEBUG_PRINT */        
        datalog[Y] += get_accel_direct(Y);
        datalog[Z] += get_accel_direct(Z);
    }

#ifdef DEBUG_PRINT
    printf("\n");
#endif /* Def: DEBUG_PRINT */    
    

/*     /\* for(i=0;i<3;i++) *\/ */
/*     /\*     datalog[i]=get_accel_direct(i); *\/ */
    
    eeprom_busy_wait();
    eeprom_write_word((uint16_t *)HORIZONTAL_VAL_X_EEMEM,datalog[X]/16);
    eeprom_busy_wait();
    eeprom_write_word((uint16_t *)HORIZONTAL_VAL_Y_EEMEM,datalog[Y]/16);
    eeprom_busy_wait();
    eeprom_write_word((uint16_t *)HORIZONTAL_VAL_Z_EEMEM,datalog[Z]/16);
    eeprom_busy_wait();
    eeprom_write_byte((uint16_t *)HORIZONTAL_FLAG_EEMEM,0xAA);

/* #ifdef DEBUG_PRINT */
/*     eeprom_busy_wait(); */
/*     datalog[X]=eeprom_read_word((uint16_t *)HORIZONTAL_VAL_X_EEMEM); */
/*     /\* datalog[X]=eeprom_read_word(&horizontal_val_eemem[X]); *\/ */
/*     eeprom_busy_wait(); */
/*     datalog[Y]=eeprom_read_word((uint16_t *)HORIZONTAL_VAL_Y_EEMEM); */
/*     /\* datalog[Y]=eeprom_read_word(&horizontal_val_eemem[Y]); *\/ */
/*     eeprom_busy_wait(); */
/*     datalog[Z]=eeprom_read_word((uint16_t *)HORIZONTAL_VAL_Z_EEMEM); */
/*     /\* datalog[Z]=eeprom_read_word(&horizontal_val_eemem[Z]); *\/ */
/*     /\* for(i=0;i<3;i++) *\/ */
/*     /\*     datalog[i] /= 16; *\/ */
/*     printf("# horizontal values were saved\n" */
/*            "# X:%4d Y:%4d Z:%4d\n", */
/*            datalog[X],datalog[Y],datalog[Z]); */
/* #endif /\* Def: DEBUG_PRINT *\/ */
    
    load_accel_horizontal();
}

/* /\* 加速度センサの0点の位置を変数に代入 *\/ */
/* /\* 最初に１度は呼んであげてね *\/ */
void load_accel_horizontal(void){
    eeprom_busy_wait();
    if(eeprom_read_byte((uint16_t *)HORIZONTAL_FLAG_EEMEM)){
        eeprom_busy_wait();
        horizontal_val[X] = eeprom_read_word((uint16_t *)HORIZONTAL_VAL_X_EEMEM);
        eeprom_busy_wait();
        horizontal_val[Y] = eeprom_read_word((uint16_t *)HORIZONTAL_VAL_Y_EEMEM);
        eeprom_busy_wait();
        horizontal_val[Z] = eeprom_read_word((uint16_t *)HORIZONTAL_VAL_Z_EEMEM);
#ifdef DEBUG_PRINT
        printf("# horizontal values were read\n"
               "# X:%4d Y:%4d Z:%4d\n",
               horizontal_val[X],
               horizontal_val[Y],
               horizontal_val[Z]);
#endif /* Def: DEBUG_PRINT */
    }else{
        horizontal_val[X] = 0xFFFF;
#ifdef DEBUG_PRINT
    printf("# There isn't horizontal values in EEPROM\n"
           "# Please call the function (save_accel_horizontal)\n");
#endif /* Def: DEBUG_PRINT */
        
    }
}


/* 正負付きで、0点較正だけ行った値を返す */
/* もし0点較正が行われていない場合は、(uint16_t *)HORIZONTAL_VAL_X_EEMEMを0点とする */
int16_t get_accel(ACCEL_t id){
    if(horizontal_val[X] != 0xFFFF){
        /* return get_accel_direct(id) - horizontal_val[id]; */
        return horizontal_val[id] - get_accel_direct(id);
    }else{
        return get_accel_direct(id);
    }
}

/* 加速度の大きさを出してみる */
uint16_t get_accel_abs(void){
    return sqrt((uint32_t)get_accel_direct(X)*(uint32_t)get_accel_direct(X) +
                (uint32_t)get_accel_direct(Y)*(uint32_t)get_accel_direct(Y) +
                (uint32_t)get_accel_direct(Z)*(uint32_t)get_accel_direct(Z));
}
