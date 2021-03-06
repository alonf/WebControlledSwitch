#include "AzureIoTHubManager.h"
#include <Arduino.h>

using namespace std;

WiFiClientSecure AzureIoTHubManager::_sslWiFiClient;
AzureIoTHubClient AzureIoTHubManager::_iotHubClient;

AzureIoTHubManager::AzureIoTHubManager(WiFiManagerPtr_t wifiManager, LoggerPtr_t logger, const char* connectionString) :  _logger(logger), _azureIoTHubDeviceConnectionString(connectionString)
{
	wifiManager->RegisterClient([this](ConnectionStatus status) { UpdateStatus(status); });
}

void AzureIoTHubManager::HandleCommand(const String & commandName) const
{
	_logger->WriteMessage("Received command: ");
	_logger->WriteMessage(commandName);
	int commandId = 0;

	if (commandName == "Activate")
		commandId = 1;
	else if (commandName == "On")
		commandId = 1;
	else if (commandName == "Off")
		commandId = 2;

	if (commandId == 0)
	{
		_logger->WriteMessage("Invalid command, commands are case sensitive. [On, Off, Activate]");
		return;
	}

	_pubsub.NotifyAll(commandName, commandId);
}


bool AzureIoTHubManager::CheckTimeInitiated()
{
	if ( _isTimeInitiated)
		return true;
	
	if (_IsInitTime == false)
		return false;
	
	time_t epochTime;

	epochTime = time(nullptr);

	if (epochTime == 0)
	{
		_logger->WriteErrorMessage("Fetching NTP epoch time failed!", 5);
		delay(100);
		return false;
	}
	//else
	
	_logger->WriteMessage("Fetched NTP epoch time is: ");
	_logger->WriteMessage(epochTime);
	_isTimeInitiated = true;
	return true;
}

bool AzureIoTHubManager::CheckIoTHubClientInitiated()
{
	if (_isIotHubClientInitiated)
		return true;

	_iotHubClient.begin(_sslWiFiClient);

	if (!AzureIoTHubInit(_azureIoTHubDeviceConnectionString))
		return false;
	_isIotHubClientInitiated = true;
	return true;
}



void AzureIoTHubManager::Loop()
{
	if (CheckTimeInitiated() == false) //can't do anything before setting the time
		return;
	if (CheckIoTHubClientInitiated() == false)
		return;


	if ((millis() - _loopStartTime) < 500)
		return;
	_loopStartTime = millis();
	AzureIoTHubLoop();
}

void AzureIoTHubManager::UpdateRelayState( char *deviceId, int state) const
{
	if (_isIotHubClientInitiated)
		AzureIoTHubSendMessage(deviceId, state, 1);
}

void AzureIoTHubManager::UpdateStatus(ConnectionStatus status)
{
	if (status.IsJustConnected() && !_IsInitTime) //new connection, only once
	{
		configTime(0, 0, "pool.ntp.org", "time.nist.gov");
		_IsInitTime = true;
	}
}

