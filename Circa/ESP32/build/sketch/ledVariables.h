///*** "sun" settings ***///
int sun_bottomCenter = 50;
int sun_quarterStep = 10;

///*** sunrise ***///
float sunrise_animPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float sunrise_fullDuration = 0.5; // from 0 to 1, how long of the sunrise animation should be full-sun?
float sunrise_ledFadeInDuration = 0.45; // How long led's fades in based on percentage of entire animation. MUST BE LOWER THAN sunrise_fullDuration!
float sunrise_ledFadeInPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.

bool sunrise_active = false; // if any animation is playing rn
float sunrise_activeStep; // record of how many led's are lit up during sunrise
float sunrise_animProgress = 0.0; // record of general progress of sunrise animation

///*** to bed indication ***///
bool beforeBed_active = false; // if any animation is playing rn
float beforeBed_animPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float beforeBed_animProgress = 0.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.
float beforeBed_fadeInDuration = 30000.0; // millis
float beforeBed_fadeInPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.

///*** sunset ***///
float sunset_animPrecision = 1000.0; // doesn't do anything really. It's like hundred percent, but more or less as max percentage.

float sunset_activeStep; // record of how many led's are lit up during sunrise
float sunset_animProgress = 0.0; // record of general progress of sunrise animation