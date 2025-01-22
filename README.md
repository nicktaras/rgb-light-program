# rgb-light-program
A project to create an elegant light display for the home.

![alt text](https://github.com/nicktaras/rgbIot/blob/master/project%20images/1.JPG?raw=true)

### Current Methods:

## moodLightRandomPaint() 
Paint the lights different colours, slow fades from one colour to the next.

## twoColourAlternatePaint() 
Apply two colours to the led strip. e.g. red, blue, red, blue.

## twoColourDividePaint()
apply two colours to the leds 50/50 e.g. red, red, blue, blue

## singleColourPaint()
apply a single colour to the led strip

### Set default colours on load:
ColorLineReference primaryTargetColourIndex = red;
ColorLineReference secondaryTargetColourIndex = plum;

// This is a beaufiful algorithm <3 to animate from one colour to the next.

const lerp = (v0, v1, perc) => {
  return v0 * (1 - perc) + v1 * perc;
}
