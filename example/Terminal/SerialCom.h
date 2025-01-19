#ifndef __SERIAL_COM__
#define __SERIAL_COM__

#include "VT100.h" 

class SerialCom_c:public VT100_c
{
	public:
	
		SerialCom_c(SerialClass & port,	uint16_t RxTimeout_ms=RX_TIMEOUT);

		void TerminalOpen(void);
		void TerminalProcess(void);
		void SerialOpen(void);
		void SerialProcess(void);

	private:
	
	SerialClass *SerialPort;
	
	static const uint16_t RX_TIMEOUT=100;
	
	static const uint8_t TEXT_LEN	=15;
	static const uint8_t EDIT_X		=15;
	static const uint8_t EDIT_Y		=20;
	
						// 123456789012345
	char Text[TEXT_LEN+1]="Hello World    ";
	colour_et colour=green;
	colour_et default_colour=white;
	
	void printText(void);
};

#endif // __SERIAL_COM__
