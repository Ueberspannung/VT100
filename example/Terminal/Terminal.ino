#include "SerialCom.h"
#include "SerialClass.h"

#ifdef HAS_USB_SERIAL
SerialClass SerialPort{SerialUSB};
#else
SerialClass SerialPort{Serial};
#endif

SerialCom_c SerialCom{SerialPort};



void toggle(int n)
{
	digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
	delay(n);
}

void pulse(int n)
{
	digitalWrite(LED_BUILTIN,HIGH);
	delay(n);
	digitalWrite(LED_BUILTIN,LOW);
	delay(n);
}

void blink(int pulse, int dauer)
{
	do
	{
		toggle(pulse);
		dauer-=pulse;
	} 
	while (dauer>0);
}


void setup()
{
	pinMode(LED_BUILTIN,OUTPUT);
	digitalWrite(LED_BUILTIN,LOW);
	SerialPort.begin(115200);
}

void loop()
{
	SerialCom.process();
	if (SerialCom.GetTerminalMode()==SerialCom_c::offline)	
		pulse(50);
}

