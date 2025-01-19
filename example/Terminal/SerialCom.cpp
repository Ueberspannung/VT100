#include "SerialCom.h"

SerialCom_c::SerialCom_c(SerialClass & port,	uint16_t RxTimeout_ms) : VT100_c(port,RxTimeout_ms)
{
	SerialPort=&port;
}


void SerialCom_c::SerialOpen(void)
{
	SerialPort->print("\n\n\nPlain Serial Detected\n\n"); 
}

void SerialCom_c::SerialProcess(void)
{
	// process serial protocol
}

void SerialCom_c::printText(void)
{
	PrintAt(1,24,"last line");
	SaveRestoreCursorAttributes(true);
	SetColours(colour,VT100_c::black);
	SetCursor(1,22);
	SetCharSize(VT100_c::double_hight_upper_line);
	PrintAt(4,22,Text);
	SetCursor(1,23);
	SetCharSize(VT100_c::double_hight_lower_line);
	PrintAt(4,23,Text);
	SaveRestoreCursorAttributes(false);

}

void SerialCom_c::TerminalOpen(void)
{
	ResetTerminal();
	SetCursorOn(false);
	SetColours(default_colour,	VT100_c::black);
	ClearScreen();
	PrintAt(1,1,"normal text");
	SetAttributes((uint8_t)VT100_c::bright);
	PrintAt(1,2,"bright text");
	SetAttributes((uint8_t)VT100_c::dim);
	PrintAt(1,3,"dim text");
	SetAttributes((uint8_t)VT100_c::underscore);
	PrintAt(1,4,"underscore");
	SetAttributes((uint8_t)VT100_c::blink);
	PrintAt(1,5,"blinking");
	SetAttributes((uint8_t)VT100_c::reverse);
	PrintAt(1,6,"reverse text");
	SetAttributes((uint8_t)VT100_c::hidden);
	PrintAt(1,7,"hidden text");
	SetAttributes((uint8_t)VT100_c::bright | (uint8_t)VT100_c::blink | (uint8_t)VT100_c::reverse );
	PrintAt(1,7,"bright blink reverse");
	SetAttributes();
	PrintAt(1,1,"normal text");
	
	SetColours(VT100_c::red,	VT100_c::black); PrintAt(30,1,"(r)ed");
	SetColours(VT100_c::green,	VT100_c::black); PrintAt(30,2,"(g)green");
	SetColours(VT100_c::yellow,	VT100_c::black); PrintAt(30,3,"(y)ellow");
	SetColours(VT100_c::blue,	VT100_c::black); PrintAt(30,4,"(b)lue");
	SetColours(VT100_c::magenta,VT100_c::black); PrintAt(30,5,"(m)agenta");
	SetColours(VT100_c::cyan,	VT100_c::black); PrintAt(30,6,"(c)yan");
	SetColours(VT100_c::white,	VT100_c::black); PrintAt(30,7,"(w)hite");


	SetCursor(1,11);	SetCharSize(VT100_c::normal);					Print("normal size Line");
	SetCursor(1,12);	SetCharSize(VT100_c::double_width);				Print("double width Line");
	SetCursor(1,13);	SetCharSize(VT100_c::double_hight_upper_line);	Print("double hight double width Line (upper)");
	SetCursor(1,14);	SetCharSize(VT100_c::double_hight_lower_line);	Print("double hight double width Line (lower)");
	SetCursor(1,15);	SetCharSize(VT100_c::normal);					Print("normal size Line");

	PrintAt(5,20,F("(E)dit : "));

	PrintAt(EDIT_X,EDIT_Y,Text);

	printText();
}


void SerialCom_c::TerminalProcess(void)
{
	char cMenu;
	bool update=false;
	if (EditGetState()!=editing)
	{	// process Menu
		if (ScanKeyMask(&cMenu,F("rRgGyYbBmMcCwWeE")))
		{	// key pressed
			cMenu=toupper(cMenu);
			update=true;
			switch (cMenu)
			{	// menu item
				case 'R':
					colour=red;
					break;
				case 'G':
					colour=green;
					break;
				case 'Y':
					colour=yellow;
					break;
				case 'B':
					colour=blue;
					break;
				case 'M':
					colour=magenta;
					break;
				case 'C':
					colour=cyan;
					break;
				case 'W':
					colour=white;
					break;
				case 'E':
					EditStart(EDIT_X,EDIT_Y,Text,TEXT_LEN);
					update=false;
					break;
				default:
					break;
			}	// menu item
		}	// key pressed
	}	// process Menu
	else
	{	// process edit
		update= Edit()!=editing;
	}	// process edit
	if (update) printText();
}
