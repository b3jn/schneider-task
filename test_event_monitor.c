#include "unity.h"
#include "event_monitor.h"

extern uint32_t em_edge_counter;
extern gpio_mask_t em_last_state;
extern void event_monitor_gpio_callback(gpio_mask_t new_state);

/* * @brief Test if main function resets the edge counter correctly.
 */
void test_MainShouldResetCounter(void)
{
    em_edge_counter = 5;
    event_monitor_main();
    TEST_ASSERT( em_edge_counter = 0 );
}

// Test for GPIO callback that increments the edge counter
void test_GpioCallbackShouldIncrementCounter(void)
{
    em_edge_counter = 0;

    em_last_state = 0x00; // Initial state
    gpio_mask_t new_state = 0x01; // Simulate a GPIO state change on pin 0
    event_monitor_gpio_callback(new_state);
    TEST_ASSERT_EQUAL_UINT32(1, em_edge_counter);
}

// Test for GPIO callback with no change
void test_GpioCallbackShouldNotIncrementCounterOnNoChange(void)
{
    em_edge_counter = 0;

    em_last_state = 0x01; // Initial state
    gpio_mask_t new_state = 0x01; // Simulate no change in GPIO state
    event_monitor_gpio_callback(new_state);
    TEST_ASSERT_EQUAL_UINT32(0, em_edge_counter);
}

// Test for GPIO callback with multiple changes
void test_GpioCallbackShouldIncrementForMultipleChangesInSameCall(void)
{
    em_edge_counter = 0;

    em_last_state = 0x00; // Initial state
    gpio_mask_t new_state = 0x0f; // 4 bits changed change
    event_monitor_gpio_callback(new_state);
    TEST_ASSERT_EQUAL_UINT32(4, em_edge_counter); // 4 bits changed
}

//Test for GPIO callback with multiple rising edges and falling edges
void test_GpioCallbackShouldHandleMultipleRisingAndFallingEdges(void)
{
    em_edge_counter = 0;

    em_last_state = 0x0f; // Initial state
    gpio_mask_t new_state = 0x3e; // 2 rising edges and 1 falling edge
    event_monitor_gpio_callback(new_state);
    TEST_ASSERT_EQUAL_UINT32(2, em_edge_counter); // 2 rising edges detected
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_MainShouldResetCounter);
    RUN_TEST(test_GpioCallbackShouldIncrementCounter);
    RUN_TEST(test_GpioCallbackShouldNotIncrementCounterOnNoChange);
    RUN_TEST(test_GpioCallbackShouldIncrementForMultipleChangesInSameCall);
    RUN_TEST(test_GpioCallbackShouldHandleMultipleRisingAndFallingEdges);
    
    return UNITY_END();
}