# mh-z19b

## Adding the library to your project
Add this respository to your CMake project with add_subdirectory(). Now, you should be able to link the mh-z19b library with target_link_libraries(\<target\> mh-z19b). This should allow you to #include "mh-z19b.h" and start using the library functions.

## Usage
First, you have to register your platform specific uart tx, rx and discard buffer functions with mh_z19b_init().
You have to use the following settings for uart.

| Setting | Value |
| ------------- | ------------- |
| Baud Rate  | 9600  |
| Data Bits  | 8  |
| Stop Bits | 1  |
| Parity(check bits)  | 0(No)  |

After that, you can use all other library functions.

## Examples
https://github.com/kahlering/mh-z19b_examples



## Sources
https://revspace.nl/MH-Z19B#Protocol_.28operation_mode_0.29

https://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf
