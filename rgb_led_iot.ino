#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
#endif
  pixels.begin();
}

int colorValueR = 0;
int colorValueG = 0;
int colorValueB = 0;

int colors[] = {   
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

int colourLineOffset = 3;
enum colorLineReference {
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
  blue,
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

// Beautiful colour combinations:
// mistyrose + magenta.

colorLineReference colourStateIndex = mistyrose;
colorLineReference colourStateIndex2 = magenta;
colorLineReference colourStateAlternate = colourStateIndex;

void singleColourPaint () {
 for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, colors[colourStateIndex*3], colors[colourStateIndex*3+1], colors[colourStateIndex*3+2]); 
    pixels.show();
  }
}

void twoColourPaint () {

 // Alternate 
 for(int i = 0; i < NUMPIXELS; i++) {

  bool alternatePalette = (i % 2 ); //(i + 1) % dirArr.length;
    
  if(alternatePalette == 1) {

    colorLineReference colourStateAlternate = colourStateIndex;
    pixels.setPixelColor(i, colors[colourStateAlternate*3], colors[colourStateAlternate*3+1], colors[colourStateAlternate*3+2]); 
    pixels.show();
    
  } else {

    colorLineReference colourStateAlternate = colourStateIndex2;
    pixels.setPixelColor(i, colors[colourStateAlternate*3], colors[colourStateAlternate*3+1], colors[colourStateAlternate*3+2]); 
    pixels.show();  
  }
  
 }

 // 50 / 50 on strip

// int startPoint = NUMPIXELS / 2;
// int endPoint = NUMPIXELS / 2;
//  
// for(int i = 0; i < endPoint; i++) {
//    pixels.setPixelColor(i, colors[colourStateIndex*3], colors[colourStateIndex*3+1], colors[colourStateIndex*3+2]); 
//    pixels.show();
//  }
//
//  for(int j = startPoint; j < NUMPIXELS; j++){
//    pixels.setPixelColor(j, colors[colourStateIndex2*3], colors[colourStateIndex2*3+1], colors[colourStateIndex2*3+2]); 
//    pixels.show();
//  }
//  
}

void loop() {
  
 twoColourPaint();
 
}



