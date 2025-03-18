
void TimerCallback()
{
	// sample broadcast every 20secs
	if (Chargenode::counter == 20)
	{
		Log::GetLog()->info("Server is up!");

		const FString msg = FString("Welcome to the server");
		AsaApi::GetApiUtils().GetCheatManager()->Broadcast(&msg);
	}

	// sample notif every 50secs
	if (Chargenode::counter == 50)
	{
		AsaApi::GetApiUtils().SendNotificationToAll(FColorList::Blue, 1.3f, 15.0f, nullptr, "Hooray Welcome to the server! enjoy!");
	}


	Chargenode::counter++;
}


void SetTimers(bool addTmr = true)
{
	if (addTmr)
	{
		AsaApi::GetCommands().AddOnTimerCallback("ChargenodeTimerTick", &TimerCallback);
	}
	else
	{
		AsaApi::GetCommands().RemoveOnTimerCallback("ChargenodeTimerTick");
	}
}