#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

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

// all rgbs - see colorLineReference enum
// ro reach the values.
int colors[] = {   
  255,0,0,
  0,255,0,
  0,0,255,
  240,248,255,
  230,230,250,
  176,224,230,
  173,216,230,
  135,206,250,
  135,206,235,
  0,191,255,
  176,196,222,
  30,144,255,
  100,149,237,
  70,130,180,
  95,158,160,
  123,104,238,
  106,90,205,
  72,61,139,
  65,105,225,
  0,0,255,
  0,0,205,
  0,0,139,
  0,0,128,
  25,25,112,
  138,43,226,
  75,0,130,
  224,255,255,
  0,255,255,
  0,255,255,
  127,255,212,
  102,205,170,
  175,238,238,
  64,224,208,
  72,209,204,
  0,206,209,
  32,178,170,
  95,158,160,
  0,139,139,
  0,128,128,
  230,230,250,
  216,191,216,
  221,160,221,
  238,130,238,
  218,112,214,
  255,0,255,
  255,0,255,
  186,85,211,
  147,112,219,
  138,43,226,
  148,0,211,
  153,50,204,
  139,0,139,
  128,0,128,
  75,0,130,
  255,255,255,
  255,250,250,
  240,255,240,
  245,255,250,
  240,255,255,
  240,248,255,
  248,248,255,
  245,245,245,
  255,245,238,
  245,245,220,
  253,245,230,
  255,250,240,
  255,255,240,
  250,235,215,
  250,240,230,
  255,240,245,
  255,228,225,
  255,222,173
};
size_t lengthOfColors = sizeof(colors)/sizeof(colors[0]);

int colourLineOffset = 3;
enum colorLineReference {
  red,
  green,
  blue,
  aliceblue,
  lavender,
  powderblue,
  lightblue,
  lightskyblue,
  skyblue,
  deepskyblue,
  lightsteelblue,
  dodgerblue,
  cornflowerblue,
  steelblue,
  cadetblue,
  mediumslateblue,
  slateblue,
  darkslateblue,
  royalblue,
  blue2,
  mediumblue,
  darkblue,
  navy,
  midnightblue,
  blueviolet,
  indigo,
  lightcyan,
  cyan,
  aqua,
  aquamarine,
  mediumaquamarine,
  paleturquoise,
  turquoise,
  mediumturquoise,
  darkturquoise,
  lightseagreen,
  cadetblue2,
  darkcyan,
  teal,
  lavender2,
  thistle,
  plum,
  violet,
  orchid,
  fuchsia,
  magenta,
  mediumorchid,
  mediumpurple,
  blueviolet2,
  darkviolet,
  darkorchid,
  darkmagenta,
  purple,
  indigo2,
  white,
  snow,
  honeydew,
  mintcream,
  azure,
  aliceblue2,
  ghostwhite,
  whitesmoke,
  seashell,
  beige,
  oldlace,
  floralwhite,
  ivory,
  antiquewhite,
  linen,
  lavenderblush,
  mistyrose,
  navajowhite
};

// References to set colour and colour to transition to.
// apply defaults here.
colorLineReference primaryTargetColourIndex = red;
colorLineReference secondaryTargetColourIndex = plum;

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
    pixels.setPixelColor(i, colors[primaryTargetColourIndex*colourLineOffset], colors[primaryTargetColourIndex*colourLineOffset+1], colors[primaryTargetColourIndex*colourLineOffset+2]); 
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
    pixels.setPixelColor(i, colors[primaryTargetColourIndex*3], colors[primaryTargetColourIndex*3+1], colors[primaryTargetColourIndex*3+2]); 
    pixels.show();
  }

  for(int j = startPoint; j < NUMPIXELS; j++){
    pixels.setPixelColor(j, colors[secondaryTargetColourIndex*3], colors[secondaryTargetColourIndex*3+1], colors[secondaryTargetColourIndex*3+2]); 
    pixels.show();
  }
 
}

// Trigger to apply a two colours to the leds.
// e.g. red, blue, red, blue.
void twoColourAlternatePaint () {

  colorLineReference colourStateAlternate = primaryTargetColourIndex;

  for(int i = 0; i < NUMPIXELS; i++) {

    bool alternatePalette = (i % 2 );
      
    if(alternatePalette == 1) {

      colorLineReference colourStateAlternate = primaryTargetColourIndex;
      pixels.setPixelColor(i, colors[colourStateAlternate*colourLineOffset], colors[colourStateAlternate*colourLineOffset+1], colors[colourStateAlternate*colourLineOffset+2]); 
      pixels.show();
      
    } else {

      colorLineReference colourStateAlternate = secondaryTargetColourIndex;
      pixels.setPixelColor(i, colors[colourStateAlternate*colourLineOffset], colors[colourStateAlternate*colourLineOffset+1], colors[colourStateAlternate*colourLineOffset+2]); 
      pixels.show();
    }

  }
 
}

// Animate from one whole colour to another.
void moodLightRandomPaint () {
  if (round(colorValueR) != colors[primaryTargetColourIndex*3] ||
      round(colorValueG) != colors[primaryTargetColourIndex*3+1] || 
      round(colorValueB) != colors[primaryTargetColourIndex*3+2]
  ) {
    for(int i = 0; i < NUMPIXELS; i++) {
     colorValueR += round(colors[primaryTargetColourIndex*3] - colorValueR) * 0.001;
     colorValueG += round(colors[primaryTargetColourIndex*3+1] - colorValueG) * 0.001;
     colorValueB += round(colors[primaryTargetColourIndex*3+2] - colorValueB) * 0.001;
     pixels.setPixelColor(i, colorValueR, colorValueG, colorValueB);
     pixels.show();
    }
  } else {
    
    randNumber = random(lengthOfColors / 3); 
    primaryTargetColourIndex = randNumber;
  }
  pixels.show();
//  delay(1); // for debugging lower value.
}

void loop() {
  moodLightRandomPaint();
}

