#ifndef __OM_DEVICE_H
#define __OM_DEVICE_H


/*******************************************************************************
 * INCLUDES
 */
#if (CONFIG_OM6236)
#include "../om6236/om6236.h"
#elif (CONFIG_OM6229)
#include "../om6229/om6229.h"
#elif (CONFIG_OM6239)
#include "../om6239/om6239.h"
#else
#error "device not specified!\n"
#endif


#endif  /* __OM_DEVICE_H */
