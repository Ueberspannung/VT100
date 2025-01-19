# VT100
Terminal Control Functions

## description
The VT100 class provides funtions to control VT100 Terminal (emulators) such as [PuTTY](https://www.putty.org/).
Due to the many different varaints some adjustments to Putty's terminal settings might be
necessary. E.g:  
	- blinking text ist disabled by default
	- BS is mapped to DEL by default
	- Auto CR with LF / Auto LF with CR is enabled by default
	- ...
  
The Class works with my SerialClass in order to unify HW Serial and USB Serial usage.  

The usage is nonblocking, the process funtion needs to be coled regulary.

Tests have been performed on an Arduino Uno and Zero with Putty.

## usage
The VT100 class needs to be initialized with the appropriate serial port. 
When calling **process** it checks wether the serial ort is availabe. Once
the serial port ist available, it checks if a terminal is connected.  
The result can be obtained by calling **GetTerminalMode**. The result is either
offline, serial or temrinal.  
for automated processing the class provides six virtual functions:  
	- TerminalOpen, TerminalProcess, TerminalClose  
	- SerialOpen, SerialProcess, SerialClose  
**xxxOpen** is called when either VT100 or not is detected on an active serial port  
**xxxProcess** is called on every call to the process member function  
**xxxClose** is called when the serial port is disabled (USB only)

**EditStart** opens an edit field at the specified position and width  
**Edit** processes the edit field. Return value is eihter **editing** or the key which
terminated the editing (CR or ESC by default).  

