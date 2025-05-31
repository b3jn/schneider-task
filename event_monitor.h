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
 * @brief Deinitializes the event monitor system.
 * This function should be called to clean up resources used by the event monitor.
 */
void event_monitor_deinit(void);

/**
 * @brief Starts the event monitor task.
 */
void event_monitor_main(void);




#endif // GPIO_HAL_H