# DIY_SQM
Two Sky Qaulity Meter Implementations using TSL2591:  DIY SQM Handheld (SQM_TSL2591_OLED-SSD1306-128x64.ino)
and DIY SQM USB (SQM_USB.ino)

The files for reading the TSL2591 and returning SQM values were downloaded from gshau's SQM_TSL2591 repository
https://github.com/gshau/SQM_TSL2591/tree/master/SQM_TSL2591.  If the .ino files are used as-is, SQM_TSL2591.cpp and SQM_TSL2591.h must be in the same directory/folder as the .ino file.

The USB version has been implemented using an Arduino Leonardo, but any Arduino should work.
The SQM LU protocol has been used but only responds to information requests (ix) and read requests (rx or RX).
This has been tested using INDI.

The handheld version also was implemented using a Leonardo and a 128x64 OLED.  
This will not work with an Uno or other 2K RAM board (insufficient storage).  
Modifying the code for the handheld to use a 128x32 OLED should allow the use of any Arduino.
