# DIY_SQM
Two Sky Qaulity Meter Implementations using TSL2591:  DIY SQM Handheld and DIY SQM USB

The files for reading the TSL2591 and returning SQM values were downloaded from gshau's SQM_TSL2591 repository
https://github.com/gshau/SQM_TSL2591/tree/master/SQM_TSL2591

The USB version has been implemented using an Arduino Leonardo, but any Arduino should work.

The handheld version also was implemented using a Leonardo and a 128x64 OLED.  This will not work with an Uno or other 2K RAM board (insufficient storage).  
Modifying the code for the handheld to use a 128x32 OLED should allow the use of any Arduino.
