#include <stdio.h>
#include <math.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery_lis302dl.h"

#include "accConfig.h"
#include "movingFilter.h"
#include "gpioConfig.h"

#define SHOW_LED
#define DEGREE 180/3.1415
#define MILLI		0.001


