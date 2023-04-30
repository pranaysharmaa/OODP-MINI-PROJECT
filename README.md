# OODP-MINI-PROJECT
Code Implementation for the mini project for OODP 


Traffic Light Control System
This is a C++ implementation of a traffic light control system that uses vehicle density information to dynamically adjust the green duration for each lane. The system can also detect the presence of an emergency vehicle using an RFID reader and immediately switch to a dedicated emergency response phase, bypassing the normal vehicle density-based control.

Installation
To use this program, you will need to have a C++ compiler installed on your system, such as gcc or clang. You can then compile the main.cpp file using the following command:
g++ main.cpp -o traffic_light
This will generate an executable file called traffic_light in the same directory as the source code.

Usage
To run the program, simply execute the traffic_light executable. The program will simulate the traffic light control system by generating random vehicle density values for each lane and periodically updating the green duration for each lane based on these values.

Additionally, the program simulates the detection of an emergency vehicle using an RFID reader. If an emergency vehicle is detected, the program will immediately switch to a dedicated emergency response phase, in which all lanes are given a minimum green duration of 10 seconds.

Configuration
The behavior of the traffic light control system can be configured by modifying the constants defined at the top of the main.cpp file. These constants include:

MAX_NUM_LANES: The maximum number of lanes that can be controlled by the system.
MIN_VEHICLE_DENSITY and MAX_VEHICLE_DENSITY: The minimum and maximum values for the randomly generated vehicle density values.
MIN_GREEN_DURATION and MAX_GREEN_DURATION: The minimum and maximum green durations for each lane.
MAX_PHASE_DURATION: The maximum duration for each traffic light phase.
