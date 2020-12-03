#ifndef __CONTROLFUNCTION_H
#define __CONTROLFUNCTION_H
#ifdef __cplusplus
 extern "C" {
#endif


#include "gpio.h"

void TurnOnWave(void );
void TurnOnSun(void );
void TurnOff5VLoad(void );
void TurnOn5VLoad(void );
void TurnOff12VLoad(void );
void TurnOn12VLoad(void);


#ifdef __cplusplus
}
#endif
#endif /*__ ControlFunction_H */

