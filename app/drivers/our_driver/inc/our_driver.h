#ifndef OUR_DRIVER_H
#define OUR_DRIVER_H

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

void our_driver_set_counter(const struct device *dev, int value);

#ifdef __cplusplus
}
#endif

#endif