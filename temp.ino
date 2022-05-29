#include <SPI.h>		// display lib
#include <Wire.h>		// wire  lib

// device driver libs
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define SERIAL_OPTS

#define OLED_RESET	4	// light for progress
#define ADDRESS		72	// idfk
#define BAUDRATE	9600	// communication to laptop

// set up display wires
Adafruit_SSD1306 display(128, 32, & Wire, OLED_RESET);


byte val = 0;

void setup()
{
	//start oled wires
	Wire.begin();

//#ifdef SERIAL_OPTS
	//setup serial output
	Serial.begin(BAUDRATE);
//#endif

	//setup pin for fan control
	pinMode(6, OUTPUT);

	//start display
	display.begin(SSD1306_SWITCHCAPVCC, 0x3c); 
	
	//flush displaybuffer
	display.clearDisplay();
}

void loop()
{
	//setup the lcd writing settings	// --				
	display.setTextColor (WHITE);		//   |				
	display.setTextSize (2);		//  /				
						//  -- should be in setup?	
	display.setCursor (0,0);		//  \
	//and finally start the damned thing	//   |				
	display.display();			// --				

	float temperature;

	Wire.beginTransmission(ADDRESS);
	//start the transmission
	Wire.write(val);
	Wire.requestFrom(address, 1);
	
	if (Wire.available()) {
		temperature = Wire.read();
		display.setCursor(0, 0);
		display.print("Temp:");
		display.print(temperature);
		display.print((char)011);
		display.print("C");
		display.display();
		if (temperature > 4) {
			digitalWrite(6, LOW);
			Serial.println(temperature);
		} else {
			digitalWrite(6, HIGH);
		}
  	}

	else {
		display.println("---");
		display.display();
	}
	delay(3000);
	display.clearDisplay();
}
