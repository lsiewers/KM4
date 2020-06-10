const char *ROOT_CA_CERT =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDtzCCAp+gAwIBAgIQDOfg5RfYRv6P5WD8G/AwOTANBgkqhkiG9w0BAQUFADBl\n"
    "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
    "d3cuZGlnaWNlcnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJv\n"
    "b3QgQ0EwHhcNMDYxMTEwMDAwMDAwWhcNMzExMTEwMDAwMDAwWjBlMQswCQYDVQQG\n"
    "EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNl\n"
    "cnQuY29tMSQwIgYDVQQDExtEaWdpQ2VydCBBc3N1cmVkIElEIFJvb3QgQ0EwggEi\n"
    "MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCtDhXO5EOAXLGH87dg+XESpa7c\n"
    "JpSIqvTO9SA5KFhgDPiA2qkVlTJhPLWxKISKityfCgyDF3qPkKyK53lTXDGEKvYP\n"
    "mDI2dsze3Tyoou9q+yHyUmHfnyDXH+Kx2f4YZNISW1/5WBg1vEfNoTb5a3/UsDg+\n"
    "wRvDjDPZ2C8Y/igPs6eD1sNuRMBhNZYW/lmci3Zt1/GiSw0r/wty2p5g0I6QNcZ4\n"
    "VYcgoc/lbQrISXwxmDNsIumH0DJaoroTghHtORedmTpyoeb6pNnVFzF1roV9Iq4/\n"
    "AUaG9ih5yLHa5FcXxH4cDrC0kqZWs72yl+2qp/C3xag/lRbQ/6GW6whfGHdPAgMB\n"
    "AAGjYzBhMA4GA1UdDwEB/wQEAwIBhjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQW\n"
    "BBRF66Kv9JLLgjEtUYunpyGd823IDzAfBgNVHSMEGDAWgBRF66Kv9JLLgjEtUYun\n"
    "pyGd823IDzANBgkqhkiG9w0BAQUFAAOCAQEAog683+Lt8ONyc3pklL/3cmbYMuRC\n"
    "dWKuh+vy1dneVrOfzM4UKLkNl2BcEkxY5NM9g0lFWJc1aRqoR+pWxnmrEthngYTf\n"
    "fwk8lOa4JiwgvT2zKIn3X/8i4peEH+ll74fg38FnSbNd67IJKusm7Xi+fT8r87cm\n"
    "NW1fiQG2SVufAQWbqz0lwcy2f8Lxb4bG+mRo64EtlOtCt/qMHt1i8b5QZ7dsvfPx\n"
    "H2sMNgcWfzd8qVttevESRmCD1ycEvkvOl77DZypoEd+A5wwzZr8TDRRu838fYxAe\n"
    "+o0bJW1sj6W3YQGx0qMmoRBxna3iw/nDmVG3KwcIzi7mULKn+gpFL6Lw8g==\n"
    "-----END CERTIFICATE-----\n";

String protocol = "https";
String host = "studenthome.hku.nl/~luuk.siewers/circa";

String response;

void httpRequest(String request)
{
    response = "\0";
    String url = protocol + "://" + host + "/esp32/" + request;

    client.begin(url,ROOT_CA_CERT);

    Serial.println("Send request...");
    Serial.println(url);
    int httpResultCode = client.GET();
    if (httpResultCode = HTTP_CODE_OK)
    {
        response = client.getString();
    }
    else
    {
        Serial.print("Error in request: code=");
        Serial.println(httpResultCode);
        delay(3000);
    }
    client.end();
}

bool httpSendRecords() {
    // create json object
    DynamicJsonDocument doc(2048);
    // // mock data
    // bool setInBedRecord = doc["inBedTimeRecord"].set("2020-06-05 23:23:21");
    // bool setOutBedRecord = doc["outBedTimeRecord"].set("2020-06-06 10:21:34");
    // bool setInBedRecommended = doc["inBedTimeRecommended"].set("2020-06-05 22:40:00");
    // bool setOutBedRecommended = doc["outBedTimeRecommended"].set("2020-06-06 10:10:00");
    bool setInBedRecord = doc["inBedTimeRecord"].set(inBedTimeRecord);
    bool setOutBedRecord = doc["outBedTimeRecord"].set(outBedTimeRecord);
    bool setInBedRecommended = doc["inBedTimeRecommended"].set(inBedTimeRecommended);
    bool setOutBedRecommended = doc["outBedTimeRecommended"].set(outBedTimeRecommended);
    if(setInBedRecord && setOutBedRecord && setInBedRecommended && setOutBedRecommended) {
        String jsonStr;        
        serializeJson(doc, jsonStr);
        String request = String("set-records.php?deviceId=") + String(deviceId) + String("&data=") + urlencode(jsonStr);
        httpRequest(request);
        // send json data in request
        if(response == "true") { return true; } 
    } else {
        Serial.println("set json data went wrong...");
    }
}

void httpGetRecommended() {
    httpRequest("get-recommended.php?deviceId=" + String(deviceId));
    if(response != "\0") {
        DynamicJsonDocument doc(256);   
        DeserializationError err = deserializeJson(doc, response);
        
        if (!err) {
            const String inBedRecommended = doc["inBedTimeRecommended"];
            const String outBedRecommended = doc["outBedTimeRecommended"];
            Serial.print("In bed at: ");
            Serial.println(inBedRecommended);
            // Serial.println(getHours(inBedTimeRecommended));
            // Serial.println(getMinutes(inBedTimeRecommended));
            // Serial.println(getSeconds(inBedTimeRecommended));
            // Serial.println(getHours(inBedTimeRecommended) * 3600 + getMinutes(inBedTimeRecommended) * 60 + getSeconds(inBedTimeRecommended));
            inBedTimeRecommended = inBedRecommended;
            sunset_startTime = getHours(inBedTimeRecommended) * 3600 + getMinutes(inBedTimeRecommended) * 60 + getSeconds(inBedTimeRecommended);
            beforeBed_startTime = sunset_startTime - beforeBed_animDuration;
            Serial.print("Out bed at: ");
            Serial.println(outBedRecommended);
            // Serial.println(getHours(outBedTimeRecommended));
            // Serial.println(getMinutes(outBedTimeRecommended));
            // Serial.println(getSeconds(outBedTimeRecommended));
            outBedTimeRecommended = outBedRecommended;
            sunrise_startTime = getHours(outBedRecommended) * 3600 + getMinutes(outBedRecommended) * 60 + getSeconds(outBedRecommended) - sunrise_animDuration;
            Serial.print((currentTime - getHours(outBedRecommended) * 3600 + getMinutes(outBedRecommended) * 60 + getSeconds(outBedRecommended) - sunrise_animDuration)/60);
            Serial.println(" minutes ago you should have gone out of bed");
        } else {
            Serial.println(F("JSON incorrect?"));
            Serial.println(err.c_str());
        }
    }
}

int getHours(String time) { return time.substring(0,2).toInt(); }
int getMinutes(String time) { return time.substring(3,5).toInt(); }
int getSeconds(String time) { return time.substring(6,8).toInt(); }

String urlencode(String str)
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;
    
}