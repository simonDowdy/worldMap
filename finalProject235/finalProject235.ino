#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>

int numLeds = 200;
int pin = 11;

int state = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, pin, NEO_GRB + NEO_KHZ800);

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4, 6);
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4, 8);
CapacitiveSensor   cs_4_10 = CapacitiveSensor(4, 10);
CapacitiveSensor   cs_4_12 = CapacitiveSensor(4, 12);
CapacitiveSensor   cs_4_13 = CapacitiveSensor(4, 13);

// usa colors
uint32_t white = strip.Color(255, 255, 255);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t yellow = strip.Color(255, 255, 0);


void setup() {
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor
  cs_4_6.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor
  cs_4_8.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor
  cs_4_10.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor
  cs_4_12.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor
  cs_4_13.set_CS_AutocaL_Millis(0xFFFFFFFF);  //Calibrate the sensor

  Serial.begin(9600);

  strip.begin();
  strip.clear();
  strip.show();
}

void loop() {
  switch (state) {
    case 0:
      finiteState();
      strip.clear();
      break;
    case 1:
      finiteState();
      strip.clear();
      usaFlag(red, white, blue);
      break;
    case 2:
      finiteState();
      strip.clear();
      brazilFlag(green, yellow, blue, 100); // Green, Yellow, Blue colors
      break;
    case 3:
      finiteState();
      strip.clear();
      swedenFlag(10); // Adjust speed for the gradient effect
      break;
    case 4:
      finiteState();
      strip.clear();
      southAfricaFlag();
      break;
    case 5:
      finiteState();
      strip.clear();
      chinaFlag(red, yellow, 50);
      break;
    case 6:
      finiteState();
      strip.clear();
      australiaFlag();
      break;
  }

  Serial.println(state);
}

///////////////////////////   Finite State Machine    ///////////////////////////////////////

void finiteState() {
  long total1 =  cs_4_2.capacitiveSensor(30);
  long total2 =  cs_4_6.capacitiveSensor(30);
  long total3 =  cs_4_8.capacitiveSensor(30);
  long total4 =  cs_4_10.capacitiveSensor(30);
  long total5 =  cs_4_12.capacitiveSensor(30);
  long total6 =  cs_4_13.capacitiveSensor(30);

  if (total1 > 1000) {
    state = 1;
  }
  if (total2 > 1000) {
    state = 2;
  }

  if (total3 > 1000) {
    state = 3;
  }

  if (total4 > 1000) {
    state = 4;
  }

  if (total5 > 1000) {
    state = 5;
  }

  if (total6 > 1000) {
    state = 6;
  }
}


///////////////////////////   USA CODE    ///////////////////////////////////////
void usaFlag(uint32_t color1, uint32_t color2, uint32_t color3) {
  static unsigned long usaTimer = millis();
  int usaInterval = 500;
  static int i = 0;

  if ((millis() - usaTimer) >= usaInterval) {
    i++;
    usaTimer = millis();
  }
  if (i >= 3) {
    i = 0;
  }
  if (i == 0) {
    strip.clear();
    switchColors(color1, color2, color3);
  } else if (i == 1) {
    strip.clear();
    switchColors(color3, color1, color2);
  } else {
    strip.clear();
    switchColors(color2, color3, color1);
  }
}

void switchColors (uint32_t color1, uint32_t color2, uint32_t color3) {
  for (int i = 0; i < strip.numPixels(); i = i + 3) {
    strip.setPixelColor(i, color1);
  }
  for (int i = 1; i < strip.numPixels(); i = i + 3) {
    strip.setPixelColor(i, color2);
  }
  for (int i = 2; i < strip.numPixels(); i = i + 3) {
    strip.setPixelColor(i, color3);
  }
  strip.show();
}



///////////////////////////   BRAZIL CODE    ///////////////////////////////////////

void brazilFlag(uint32_t color1, uint32_t color2, uint32_t color3, int brazilInterval) {
  static unsigned long brazilTimer = millis();
  static int i = 0;
  if ((millis() - brazilTimer) >= brazilInterval) {
    i++;
    brazilTimer = millis();
  }
  if (i >= 3) {
    i = 0;
  }
  if (i == 0) {
    strip.clear();
    switchColors(color1, color2, color3);
  } else if (i == 1) {
    strip.clear();
    switchColors(color3, color1, color2);
  } else {
    strip.clear();
    switchColors(color2, color3, color1);
  }
}

///////////////////////////   SWEDEN CODE    ///////////////////////////////////////

void swedenFlag(int swedenInterval) {
  static unsigned long swedenTimer = millis();
  int steps = 255; // Number of steps for the gradient

  if ((millis() - swedenTimer) >= swedenInterval) {
    for (int i = 0; i < steps; i++) {
      int red = map(i, 0, steps - 1, 0, 254);          // Gradually increase red from 0 to 254
      int green = map(i, 0, steps - 1, 106, 204);      // Gradually change green from 106 to 204
      int blue = map(i, 0, steps - 1, 107, 2);         // Gradually decrease blue from 107 to 2

      uint32_t color = strip.Color(red, green, blue); // Create color from components

      for (int j = 0; j < strip.numPixels(); j++) {
        strip.setPixelColor(j, color); // Set color to all pixels
      }

      strip.show(); // Display the gradient
      swedenTimer = millis();
    }
  }
}


///////////////////////////   SOUTH AFRICA CODE    ///////////////////////////////////////

void southAfricaFlag() {
  int numSteps = 255; // Number of fading steps
  static unsigned long southAfricanTimer = millis();
  int southAfricaInterval = 1000;

  // Define the colors
  uint32_t colors[] = {
    strip.Color(255, 0, 0),    // Red
    strip.Color(255, 255, 0),  // Yellow
    strip.Color(0, 255, 0),    // Green
    strip.Color(0, 0, 255),    // Blue
    strip.Color(255, 255, 255) // White
  };

  int numColors = sizeof(colors) / sizeof(colors[0]);

  if ((millis() - southAfricanTimer) >= southAfricaInterval) {
    for (int color = 0; color < numColors; color++) {
      fadeColor(colors[color], colors[(color + 1) % numColors], numSteps, numSteps);

      if (color == 0 || color == 2 || color == 4) {
        southAfricanTimer = millis();
      }
    }
  }
}

// from Chat gpt
void fadeColor(uint32_t fromColor, uint32_t toColor, int step, int numSteps) {
  for (int step = 0; step <= numSteps; step++) {
    uint8_t r = map(step, 0, numSteps, (fromColor >> 16) & 0xFF, (toColor >> 16) & 0xFF);
    uint8_t g = map(step, 0, numSteps, (fromColor >> 8) & 0xFF, (toColor >> 8) & 0xFF);
    uint8_t b = map(step, 0, numSteps, fromColor & 0xFF, toColor & 0xFF);

    for (int i = 0; i < numLeds; i++) {
      strip.setPixelColor(i, strip.Color(r, g, b));
    }
    strip.show();
  }
}

///////////////////////////   CHINA CODE    ///////////////////////////////////////
void chinaFlag(uint32_t redColor, uint32_t yellowColor, int chinaInterval) {
  static unsigned long chinaTimer = millis();

  static int index = 0;

  if ((millis() - chinaTimer) >= chinaInterval) {
    for (int i = 0; i < strip.numPixels(); i++) {
      if (i != index) {
        strip.setPixelColor(i, redColor); // Set all pixels to red except the traveling light
      }
    }
    strip.setPixelColor(index, yellowColor); // Set the traveling light to yellow
    strip.show();

    index++;

    // reset timer
    chinaTimer = millis();

    // Reset moving light when reaching the end
    if (index >= strip.numPixels()) {
      index = 0;
      strip.clear();
      strip.show();
    }
  }
}

///////////////////////////   AUSTRALIA CODE    ///////////////////////////////////////

void turnBlue() {
  static unsigned long transitionTimer = millis();
  int transitionInterval = 1000;

  if ((millis() - transitionTimer) >= transitionInterval) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, blue);
      transitionTimer = millis();
    }
    strip.show();
  }
}

void australiaFlag() {
  static unsigned long australiaTimer = millis();
  int austaliaInterval = 500;

  strip.clear();
  strip.show();

  if ((millis() - australiaTimer) >= austaliaInterval) {
    strip.fill(red, 0, strip.numPixels());
    strip.show();
    australiaTimer = millis();
  } 
  else {
    
    strip.fill(white, 0, strip.numPixels());
    strip.show();
  }

  // Transition back to blue
  //turnBlue();
}
