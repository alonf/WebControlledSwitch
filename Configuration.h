// Configuration.h

#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h

//Wifi Configuration
static const char *SSID = "AlonIoT"; //The default configuration access point ssid
static const char *password = "12345678"; //The default configuration access point password - at least 8 chars
static const char *webSiteHeader = "Welcome to the web light switch server";
static const char *appKey = "appkey"; //your secret app key - should be long enough
//static const char* azureIoTHubDeviceConnectionString = "HostName=[IoTHub].azure-devices.net;DeviceId=[MyLightSwitch];SharedAccessKey=k6UElnivbQgrFGD86LSTPNRmV36cpKMe1OOH5LMc/42k=";
static char* deviceId = "MyLightSwitch";

static const char* azureIoTHubDeviceConnectionString = "HostName=BlinkyHub.azure-devices.net;DeviceId=MyLightSwitch;SharedAccessKey=B333wsfq0fh3/w2gA98LPMTLPvVxwmyikM3/1ah1JTo=";
static const char *stopMenuEntry = "Stop";
static const char *closeMenuEntry = "Close Gate";
static const char *openMenuEntry = "Open Gate";

const unsigned int defaultButtonLongTimePeriod = 5000; //5 seconds -> reset
const unsigned int defaultButtonVeryLongTimePeriod = 20000; //20 seconds -> factory reset

//NodeMCU Board configuration
//const int pushButton = 5; //D1
//const int redLed = 4; //D2
//const int greenLed = 15; //D8
//const int relay = 2; //D4
//const int ButtonPressed = HIGH;
//const int ButtonReleased = ButtonPressed == HIGH ? LOW : HIGH;

//WeMos D1 Board gate controll with stepper motor & limit switches configuration
const int pushButton = 2; //D4 Pulldup 10K
const int redLed = 16; //D0
const int greenLed = 5; //D1
const int stepper1 = 4; //D2 
const int stepper2 = 14; //D5 
const int stepper3 = 12;  //D6
const int stepper4 = 13; //D7
const int limitSwitches = A0; //A0 pull down with 10K resistor
const int flashingLED = 0; //D3 
const int flashingLedPeriod = 500; //0.5 second
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
const int stepperSpeed = 1; // 0 > speed < 1024

const int ButtonPressed = LOW;
const int ButtonReleased = ButtonPressed == HIGH ? LOW : HIGH;


//Wifi Witty ESP-12F Board - https://blog.the-jedi.co.uk/2016/01/02/wifi-witty-esp12f-board/
//const int LDR = A0;
//const int pushButton = 4;
//const int redLed = 15;
//const int greenLed = 12;
//const int relay = 13; //BLUE led
//const int ButtonPressed = LOW;
//const int ButtonReleased = ButtonPressed == HIGH ? LOW : HIGH;

#endif

