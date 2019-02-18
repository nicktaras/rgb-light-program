#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "cmap.h"
#include <math.h>
long randNumber;

#define PIN            6
#define NUMPIXELS      2 // 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

// initial values.
float colorValueR = 0;
float colorValueG = 0;
float colorValueB = 0;
int colourLineOffset = 3;

// References to set colour and colour to transition to.
// apply defaults here.
ColorLineReference primaryTargetColourIndex = red;
ColorLineReference secondaryTargetColourIndex = plum;

// Application State
enum state {
  inTranistion,
  colourShown
};

// On load
state currentState = inTranistion;

// Trigger to apply a single colour to the leds.
void singleColourPaint () {
 for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, Colors[primaryTargetColourIndex*colourLineOffset], Colors[primaryTargetColourIndex*colourLineOffset+1], Colors[primaryTargetColourIndex*colourLineOffset+2]); 
    pixels.show();
  }
  currentState = colourShown;
}

// Trigger to apply two colours to the leds 50/50
// e.g. red, red, blue, blue
void twoColourDividePaint () {

  int startPoint = NUMPIXELS / 2;
  int endPoint = NUMPIXELS / 2;
  
  for(int i = 0; i < endPoint; i++) {
    pixels.setPixelColor(i, Colors[primaryTargetColourIndex*3], Colors[primaryTargetColourIndex*3+1], Colors[primaryTargetColourIndex*3+2]); 
    pixels.show();
  }

  for(int j = startPoint; j < NUMPIXELS; j++){
    pixels.setPixelColor(j, Colors[secondaryTargetColourIndex*3], Colors[secondaryTargetColourIndex*3+1], Colors[secondaryTargetColourIndex*3+2]); 
    pixels.show();
  }
 
}

// Trigger to apply a two colours to the leds.
// e.g. red, blue, red, blue.
void twoColourAlternatePaint () {

  ColorLineReference colourStateAlternate = primaryTargetColourIndex;

  for(int i = 0; i < NUMPIXELS; i++) {

    bool alternatePalette = (i % 2 );
      
    if(alternatePalette == 1) {

      ColorLineReference colourStateAlternate = primaryTargetColourIndex;
      pixels.setPixelColor(i, Colors[colourStateAlternate*colourLineOffset], Colors[colourStateAlternate*colourLineOffset+1], Colors[colourStateAlternate*colourLineOffset+2]); 
      pixels.show();
      
    } else {

      ColorLineReference colourStateAlternate = secondaryTargetColourIndex;
      pixels.setPixelColor(i, Colors[colourStateAlternate*colourLineOffset], Colors[colourStateAlternate*colourLineOffset+1], Colors[colourStateAlternate*colourLineOffset+2]); 
      pixels.show();
    }

  }
 
}

// Animate from one whole colour to another.
void moodLightRandomPaint () {
  if (round(colorValueR) != Colors[primaryTargetColourIndex*3] ||
      round(colorValueG) != Colors[primaryTargetColourIndex*3+1] || 
      round(colorValueB) != Colors[primaryTargetColourIndex*3+2]
  ) {
    for(int i = 0; i < NUMPIXELS; i++) {
     colorValueR += round(Colors[primaryTargetColourIndex*3] - colorValueR) * 0.001;
     colorValueG += round(Colors[primaryTargetColourIndex*3+1] - colorValueG) * 0.001;
     colorValueB += round(Colors[primaryTargetColourIndex*3+2] - colorValueB) * 0.001;
     pixels.setPixelColor(i, colorValueR, colorValueG, colorValueB);
     pixels.show();
    }
  } else {
    
    randNumber = random(LengthOfcolors / 3); 
    primaryTargetColourIndex = randNumber;
  }
  pixels.show();
  delay(10); // for debugging lower value.
}

void loop() {
  moodLightRandomPaint();
}




