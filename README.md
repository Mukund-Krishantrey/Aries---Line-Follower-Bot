# Line follower bot using 8051 Microcontroller

<p align="center">
  <img width="650" height="500" src="https://user-images.githubusercontent.com/32802845/54489921-628bac00-48d7-11e9-8de6-ece69e4cb6e1.png">
</p>

 As the name indicates, line follower bot follows a specific line, as it is designed to,
but we have used a 8051 microcontroller as the control system.
In our case, it has been designed to follow white line on black background. The whole setup can be divided as:

#### IR Sensors (RKI-1032):

IR sensors have been used to detect white line on black background. The deployment is done keeping in mind that black surface absorbs visible light falling on it, while white reflects. Thus, when an IR sensor is on white line, it detects the reflected light.
The IR sensors used by us gave 3.3V-3.6V output on white surface and 0V-0.2V on black surface. Out of seven IRs, four were used by us in alternate manner as per our requirement.
The GND and 5V were supplied from motor driver L298n.

#### Comparators:

The output from IRs is analog, and since we need only digital values to know whether the surface is white or black, we compared the IR outputs with 2.5V through comparators to generate 5V(High) or 0V(Low) as outputs corresponding to the IR inputs.
Op-amp IC LM324N was used for the purpose.
Here also, the GND and 5V were supplied from motor driver L298n to the pins 11 and 4 respectively.
At the inverting terminal pins 2,6,9,13, 2.5V were applied through potential dividing. 
The outputs from IRs to non-inverting terminal pins 10,12,5,3 10,5,3,12 respectively from left to right.
And outputs taken in same order from pins 8,7,1,14, and applied to microcontroller pins.

#### Microcontroller 8051 (IC AT89S52):

The connections were as follows:

 <p align="center">
  <img width="650" height="500" src="https://user-images.githubusercontent.com/32802845/54489932-6dded780-48d7-11e9-91a4-f2548cda10ec.png">
</p>

The code was uploaded to the microcontroller through USB-AVR programmer and it was placed in the circuit.
The GND and 5V supply to the microcontroller was given from motor driver L298n used in the setup.
An 11.0592MHz  crystal was connected to pins 19 and 18 as shown in schematic.
A power-on Reset circuit using 10uF capacitor, 1kΩ resistor and a push button parallel to capacitor is used as in the schematic to reset the microcontroller on Power On.
The outputs from IR sensors, now converted to logics, were input to the microcontroller through pins 39, 38, 37, 36 starting from left IR to right.
The code outputs were connected to Input3, Input4, EnableB,  Input1, Input2, EnableA of motor driver from pins 21 to 26 respectively.

#### Motor Driver:

Input1, Input2 and EnableA have been used for controlling right wheel direction and speed, while the rest are for left.
Output1 and Output2 go to right motor, while Output3 and Output4 to left motor.
The GND and VCC(12V preferably) were supplied to the motor driver from a battery, and the GND and 5V output were supplied to breadboard circuit as mentioned before.
 
<p align="center">
  <img width="750" height="500" src="https://user-images.githubusercontent.com/32802845/54490116-13df1180-48d9-11e9-9920-ac58a92a6650.jpg">
</p>
