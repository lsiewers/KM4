// pragma once prevents the file to be included twice
#pragma once
// #include ...
// all other includes stays here in the .h file

// vars need to be extern

extern String NETWORK_NAME;
extern String NETWORK_PASSWORD;

// prototypes don't need named attributes in the .h file
void connectWiFi();