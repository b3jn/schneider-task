#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#include <stdint.h>

#include "gpio_hal.h"
#include "rtos_api.h"


/**
 * @brief Initializes the event monitor system.
 */
void event_monitor_init(void);

/**
 * @brief Starts the event monitor task.
 */
void event_monitor_main(void);




#endif // GPIO_HAL_H