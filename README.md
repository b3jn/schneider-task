# EVENT MONITOR MODULE
Used for keeping track and count of rising edges on the GPIO's in 1s period and notifying the appropriate API.

# SETUP:
It is necessery to call event_monitor_init() function first, which would create a new RTOS task for main function execution and register GPIO status change callback. And reset state variables.

# OPERATION:
* Once event_monitor_main() is scheduled by RTOS kernel, it will:
    1) Reads current value of counted rising edges
    2) Resets rising edge counter to 0
    3) Notifies counter value to a predefined API
    4) Task waits for 1s

# INTEGRATION
To integrate the module in the system it is necessery to add event_monitor.c to cmake/make list of source files and add current directory to include paths.

# UNIT TESTS
Functionality is covered by unit tests done in Unity framework (https://www.throwtheswitch.org/unity).

To run unit tests, it is necessery to:
1) Clone Unity git repository - git clone https://github.com/ThrowTheSwitch/Unity.git
2) Build Unity files + tested module files - gcc test_event_monitor.c event_monitor.c "other-required-sources" unity/src/unity.c -o event_monitor.exe
3) Run - TestDumbExample.exe


