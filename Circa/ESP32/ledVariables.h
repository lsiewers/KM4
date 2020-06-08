///*** "sun" settings ***///
int sun_bottomCenter = 50;
int sun_quarterStep = 10;

///*** overall animation setting ***///
unsigned long animation_startMillis;  // time record when animation starts
bool animation_active = false; // if any animation is playing rn

///*** sunrise ***///
float sunrise_animPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float sunrise_fullDuration = 0.5; // from 0 to 1, how long of the sunrise animation should be full-sun?
float sunrise_ledFadeInDuration = 0.45; // How long led's fades in based on percentage of entire animation. MUST BE LOWER THAN sunrise_fullDuration!
float sunrise_ledFadeInPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.

float sunrise_activeStep; // record of how many led's are lit up during sunrise
float sunrise_animProgress = 0.0; // record of general progress of sunrise animation

///*** to bed indication ***///
float beforeBed_animPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float beforeBed_animProgress = 0.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float fadeInDuration = 1.0; // seconds
float fadeInPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.

///*** sunset ***///
float sunset_animPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float sunset_fullDuration = 0.5; // from 0 to 1, how long of the sunrise animation should be full-sun?
float sunset_ledFadeOutDuration = 0.45; // How long led's fades in based on percentage of entire animation. MUST BE LOWER THAN sunrise_fullDuration!
float sunset_ledFadeOutPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.

float sunset_activeStep; // record of how many led's are lit up during sunrise
float sunset_animProgress = 0.0; // record of general progress of sunrise animation