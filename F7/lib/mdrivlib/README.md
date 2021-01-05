### mdrivlib ###
## Embedded driver library, providing high-level functionality using modern C++ ##

This is highly a work in progress, the API is in flux. Contributions, feedback, and issues are welcome.

Currently only some STM32 devices are supported. As much as possible, the vendor-provided LL (low-level) libraries are used.

Goals:

  * Easy to use, difficult to misuse.
  * Provide modern C++17/20 classes for setting up and accessing internal peripherals and common external chips.
  * Provide high-level functionality for common use cases (debouncing switches, wear-leveling, RGB color blending).
  * Allow use of C++ callable objects as interrupt request handlers and callbacks (not limited to static or C-style functions).
  * Priortize peripheral access efficiency over one-time cost of peripheral setup.
  * Unit tests
  * Example code (ideally on a low-cost vendor-provided development board, such as Discovery Boards)


