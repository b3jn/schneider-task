#include "event_monitor.h"

/*DEFINES*/
#define MAIN_TASK_CYCLE 1000 //1000ms

/*GLOBAL VARIABLES*/
static rtos_task_t em_task_handle;
static uint32_t em_edge_counter = 0;
static gpio_mask_t em_last_state = 0;

/*LOCAL FUNCTION DECLARATIONS*/
static void report_event_count(uint32_t count);
static void event_monitor_gpio_callback(gpio_mask_t new_state);

/*FUNCTION DEFINITIONS*/


/**
 * @brief Initializes the event monitor system.
 */
void event_monitor_init(void)
{
    //initialize edge counter
    em_last_state = 0;
    em_edge_counter = 0;

    //create new rtos task for main function
    rtos_task_create(&em_task_handle, event_monitor_main, NULL);
    
    //register gpio callback
    gpio_register_callback(event_monitor_gpio_callback);
}

/**
 * @brief Deinitializes the event monitor system.
 * 
 * This function should be called to clean up resources used by the event monitor.
 */
void event_monitor_deinit(void)
{
    //deinitialize resources if needed
    //currently no resources to deinitialize
    //if there were, we would unregister the gpio callback and delete the task
    //gpio_unregister_callback(event_monitor_gpio_callback);
    //rtos_task_delete(&em_task_handle);
}

/**
 * @brief Starts the event monitor task.
 */
void event_monitor_main(void)
{
    uint32_t rising_edges_detected = 0;

    while(1)
    {
        //using rtos_mutex_lost can cause kernel issues
        //since if interrupt occurs during this time, it wont be able to access mutex protected 
        //variable and block
        //we need to disable interrupts here, not use mutex
        
        //rtos_mutex_lock();  ---> disable_irq();
        /*read and reset counter */
        rising_edges_detected = em_edge_counter;
        em_edge_counter = 0;
        //rtos_mutex_unlock();  ---> enable_irq()

        //report event count
        report_event_count(rising_edges_detected);

        //delay task
        //to create precise cycle, delay function is called with period 
        //of (MAIN_TASK_CYCLE - execution time of current cycle), but we dont have time
        //APIs available to track execution times in this assignment
        rtos_task_delay_ms(MAIN_TASK_CYCLE);
    }
}

/**
 * @brief Callback function to handle GPIO state changes.
 * 
 * This function is called whenever there is a change in the GPIO state.
 * It detects rising edges and increments the edge counter accordingly.
 * 
 * @param new_state The new GPIO state as a bitmask.
 */
void event_monitor_gpio_callback(gpio_mask_t new_state)
{
    uint32_t mask;

    /*
    Rising edge detection method: for each bit in a 32-bit status var
    is done with a bit mask corresponding to each bit, new_state var is checked 
    for active bits "1" and also last_state is checked for "0" state on same position, signaling that 
    that specific bit position had transition from "0"->"1" in this callback call
    
    Afterwards bit mask is shifted by 1 (<<1) and next bit is checked
    */
   
    /*calling mutex_lock here to reduce overhead with locking on every edge increment
        In case we disable interrupts in main task, there is no need to protect shared resource
    */  
    //rtos_mutex_lock();
    for (uint8_t bit = 0; bit < 32; bit++)
    {
        mask = 0x1 << bit;
        if ((new_state & mask) != 0 &&
            (em_last_state & mask) == 0)
            {
                //bit in last state is 0, in new state its 1
                //rising edge detected
                em_edge_counter++;
            }
    }

    //rtos_mutex_unlock();
    em_last_state = new_state;
}

/// @brief Reports the event count to an external system or log.
void report_event_count(uint32_t count)
{
    //stub
}