/**
   esp32 firmware OTA
   
   Purpose: Perform an OTA update from a bin located on a webserver (HTTP Only)

   Setup:
   Step 1 : Set your WiFi (ssid & password)
   Step 2 : set esp32fota()
   
   Upload:
   Step 1 : Menu > Sketch > Export Compiled Library. The bin file will be saved in the sketch folder (Menu > Sketch > Show Sketch folder)
   Step 2 : Upload it to your webserver
   Step 3 : Update your firmware JSON file ( see firwmareupdate )

*/

#include <FS.h>
#include <SPIFFS.h>
#include <esp32fota.h>
#include <WiFi.h>

// Change to your WiFi credentials
const char *ssid = "TP-Link_6937";
const char *password = "60676092";
String version = "1.0.0";

// esp32fota esp32fota("<Type of Firme for this device>", <this version>);
esp32FOTA esp32FOTA("esp32-fota-https", version, false, true);

void setup()
{
  // Provide spiffs with root_ca.pem to validate server certificate
//  SPIFFS.begin(true);
//  esp32FOTA.checkURL = "http://192.168.0.111:8082/fota.json";
  esp32FOTA.checkURL = "https://github.com/lukbieli/FOTA_HTTPS/blob/master/release/fota.json";
  Serial.begin(115200);
  Serial.println(version);
  setup_wifi();
}

void setup_wifi()
{
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println(WiFi.localIP());
}

void loop()
{
  Serial.println("Start check");
  bool updatedNeeded = esp32FOTA.execHTTPcheck();
  if (updatedNeeded)
  {
    esp32FOTA.execOTA();
  }
  else
  {
    Serial.println("Update not needed");
  }

  delay(10000);
}
