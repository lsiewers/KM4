#include "ledVariables.h"

void ledStripUpdate() {
  strand_t * strands[1] = {&STRANDS[0]};
  digitalLeds_resetPixels(strands, STRANDCNT);
  int m1 = getMaxMalloc(1*1024, 16*1024*1024);
}

// void sunrise(strand_t ** strands) {
//   // led sunrise animation
//   if (currentTime >= sunrise_startTime && currentTime - sunrise_startTime <= sunrise_animDuration) {
//     float startTime;
//     if(!animation_active) {
//         startTime = millis();
//         Serial.println("sunset started");
//         animation_active = true;
//     }
//     strand_t * pStrand = strands[0]; // select only strip
//     sunrise_animProgress = map(millis() - startTime, 0, sunrise_animDuration * 1000, 0, sunrise_animPrecision);

//     if (sunrise_animProgress < sunrise_animPrecision - sunrise_animPrecision * sunrise_fullDuration) {
//       sunrise_activeStep = map(sunrise_animProgress, 0, sunrise_animPrecision - sunrise_animPrecision * sunrise_fullDuration, 0, sun_quarterStep * 2); 
//     } else sunrise_activeStep = sun_quarterStep * 2;
//     // sun led's
//     for(int i = 0; i <= round(sunrise_activeStep); i++) {
//       int sumIndex = sun_bottomCenter + i;
//       if(i > sun_quarterStep) {
//         sumIndex = sun_bottomCenter - sun_quarterStep * 3 + i - sun_quarterStep;
//       }
//       // i = 0 to sun_quarterStep
//       pStrand->pixels[sun_bottomCenter - i] = pixelFromRGBW(sunriseFadeColor("r", i), sunriseFadeColor("g", i), 0, sunriseFadeColor("w", i));
//       pStrand->pixels[sumIndex] = pixelFromRGBW(sunriseFadeColor("r", i), sunriseFadeColor("g", i), 0, sunriseFadeColor("w", i));
//     }
//     // top led's
//     for(int i = 0; i < sun_bottomCenter - 3 * sun_quarterStep; i++) {
//       pStrand->pixels[i] = pixelFromRGBW(sunriseFadeColor("r", i), sunriseFadeColor("g", i), 0, 0);
//     }
//     digitalLeds_drawPixels(strands, 1);
//   } else if (animation_active) animation_active = false;
// }

// // color fade in function
// uint8_t sunriseFadeColor(String rgbwColor, int i) {
//   float treshold = sunrise_animPrecision * sunrise_ledFadeInDuration;
//   // i (0 - quarterstep * 2), progress (0 - precision)
//   // precision / (quarterstep * 2) * i = i progress in precision
//   float thisProgressStart = (sunrise_animPrecision - sunrise_animPrecision * sunrise_fullDuration) / (sun_quarterStep * 2.0) * float(i);
//   float thisProgressEnd = thisProgressStart + treshold;
//   float fadeProgress;
//   uint8_t color;

//   // led not reached yet
//   if (sunrise_animProgress < thisProgressStart) fadeProgress = 0.0;
//   // led fading in
//   else if (sunrise_animProgress < thisProgressEnd) fadeProgress = map(sunrise_animProgress, thisProgressStart, thisProgressEnd, 0, sunrise_ledFadeInPrecision);
//   // led fade ended
//   else fadeProgress = sunrise_ledFadeInPrecision;

//   if(fadeProgress <= 0.0) {
//    if (rgbwColor == "r") color = uint8_t(0.0);
//    if (rgbwColor == "g") color = uint8_t(0.0);
//    if (rgbwColor == "w") color = uint8_t(0.0);
//   }
//   else if(fadeProgress < sunrise_ledFadeInPrecision/2) {
//    if (rgbwColor == "r") color = uint8_t(255.0/sunrise_ledFadeInPrecision/2*fadeProgress);
//    if (rgbwColor == "g") color = uint8_t(0.0);
//    if (rgbwColor == "w") color = uint8_t(0.0);
//   } else if(fadeProgress < sunrise_ledFadeInPrecision) {
//    if (rgbwColor == "r") color = uint8_t(255.0 - (155.0/(sunrise_ledFadeInPrecision/2)*(fadeProgress-sunrise_ledFadeInPrecision/2)));
//    if (rgbwColor == "g") color = uint8_t(30.0/(sunrise_ledFadeInPrecision/2)*(fadeProgress-sunrise_ledFadeInPrecision/2));
//    if (rgbwColor == "w") color = uint8_t(25.0/(sunrise_ledFadeInPrecision/2)*(fadeProgress-sunrise_ledFadeInPrecision/2));
//   }
//   else {
//    if (rgbwColor == "r") color = uint8_t(100.0);
//    if (rgbwColor == "g") color = uint8_t(30.0);
//    if (rgbwColor == "w") color = uint8_t(25.0);
//   }
  
//   return color;
// }
// ///*** end sunrise ***///

// ///*** before going to bed (time to adjust environment) ***///
// bool beforeBed(strand_t ** strands) {
//   if (currentTime >= beforeBed_startTime && currentTime - beforeBed_startTime <= beforeBed_animDuration) {
//     float startTime;
//     if(!animation_active) {
//         startTime = millis();
//         Serial.println("before bed indication started");
//         animation_active = true;
//     }
//     strand_t * pStrand = strands[0]; // select only strip
//     beforeBed_animProgress = map(millis() - startTime, 0, beforeBed_animDuration * 1000, 0, beforeBed_animPrecision);
//     Serial.println(beforeBed_animProgress);
//     for(int i = 0; i <= sun_quarterStep * 2; i++) {
//       int sumIndex = sun_bottomCenter + i;
//       if(i > sun_quarterStep) {
//         sumIndex = sun_bottomCenter - sun_quarterStep * 3 + i - sun_quarterStep;
//       }
//       // i = 0 to sun_quarterStep
//       pStrand->pixels[sun_bottomCenter - i] = pixelFromRGBW(fadeInColor("r", 100.0), fadeInColor("g", 30.0), 0, 0);
//       pStrand->pixels[sumIndex] = pixelFromRGBW(fadeInColor("r", 100.0), fadeInColor("g", 30.0), 0, 0);
//     }
//     digitalLeds_drawPixels(strands, 1);
//   } else if (animation_active) animation_active = false;
// }

// uint8_t fadeInColor(String rgbwColor, uint8_t value) {
//   uint8_t color;
//   if(currentTime - beforeBed_startTime <= fadeInDuration) {
//     float fadeProgress = map(currentTime - beforeBed_startTime, 0, fadeInDuration, 0, fadeInPrecision); // progress in percentage
//     Serial.println("Fade In Progress: " + String(fadeProgress));

//     if(fadeProgress < fadeInPrecision) {
//      if (rgbwColor == "r") color = uint8_t(map(fadeProgress, 0, fadeInPrecision, 0, value));
//      if (rgbwColor == "g") color = uint8_t(map(fadeProgress, 0, fadeInPrecision, 0, value));
//     }
//   } else {
//    if (rgbwColor == "r") color = uint8_t(value);
//    if (rgbwColor == "g") color = uint8_t(value);
//   }

//   return color;
// }

// ///*** sunset, directly after before bed indication ***///
// void sunset(strand_t ** strands) { // led sunrise animation
//   if (currentTime >= sunset_startTime && currentTime - sunset_startTime <= sunset_animDuration) {
//     float startTime;
//     if(!animation_active) {
//         startTime = millis();
//         Serial.println("sunset started"); 
//         animation_active = true;
//     }
//     strand_t * pStrand = strands[0]; // select only strip
//     sunset_animProgress = map(millis() - startTime, 0, sunset_animDuration * 1000, 0, sunset_animPrecision);

//     if (sunset_animProgress < sunset_animPrecision - sunset_animPrecision * sunset_fullDuration) {
//       sunset_activeStep = map(sunset_animProgress, 0, sunset_animPrecision - sunset_animPrecision * sunset_fullDuration, 0, sun_quarterStep * 2); 
//     } else sunset_activeStep = sun_quarterStep * 2;

//     int startingPoint = sun_bottomCenter - sun_quarterStep * 2;
//     for(int i = 0; i <= round(sunrise_activeStep); i++) {
//       int sumIndex = startingPoint - i;
//       if(i < startingPoint + sun_quarterStep) {
//         sumIndex = startingPoint + sun_quarterStep - i;
//       }
//       // i = 0 to sun_quarterStep
//       pStrand->pixels[startingPoint + i] = pixelFromRGBW(sunsetFadeColor("r", i), sunsetFadeColor("g", i), 0, 0);
//       pStrand->pixels[sumIndex] = pixelFromRGBW(sunsetFadeColor("r", i), sunsetFadeColor("g", i), 0, 0);
//     }
//     digitalLeds_drawPixels(strands, 1);
//   } else if (animation_active) animation_active = false;
// }

// // color fade out function
// uint8_t sunsetFadeColor(String rgbwColor, int i) {
//   float treshold = sunset_animPrecision * sunset_ledFadeOutDuration;
//   // i (0 - quarterstep * 2), progress (0 - precision)
//   // precision / (quarterstep * 2) * i = i progress in precision
//   float thisProgressStart = (sunset_animPrecision - sunset_animPrecision * sunset_fullDuration) / (sun_quarterStep * 2.0) * float(i);
//   float thisProgressEnd = thisProgressStart - treshold;
//   float fadeProgress;
//   uint8_t color;

//   // led not reached yet
//   if (sunset_animProgress < thisProgressStart) fadeProgress = 0.0;
//   // led fading in
//   else if (sunset_animProgress < thisProgressEnd) fadeProgress = map(sunset_animProgress, thisProgressStart, thisProgressEnd, 0, sunset_ledFadeOutPrecision);
//   // led fade ended
//   else fadeProgress = sunset_ledFadeOutPrecision;

//   if(fadeProgress <= 0.0) {
//    if (rgbwColor == "r") color = uint8_t(100.0);
//    if (rgbwColor == "g") color = uint8_t(30.0);
//   }
//   else if(fadeProgress < sunset_ledFadeOutPrecision) {
//    if (rgbwColor == "r") color = uint8_t(100.0 - (100.0/(sunset_ledFadeOutPrecision/2)*(fadeProgress-sunset_ledFadeOutPrecision/2)));
//    if (rgbwColor == "g") color = uint8_t(30.0 - 30.0/(sunset_ledFadeOutPrecision/2)*(fadeProgress-sunset_ledFadeOutPrecision/2));
//   }
//   else {
//    if (rgbwColor == "r") color = uint8_t(0.0);
//    if (rgbwColor == "g") color = uint8_t(0.0);
//   }
  
//   return color;
// }
