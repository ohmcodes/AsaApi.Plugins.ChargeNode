
void Reload()
{
	ReadConfig();

	// TODO: might cause crash after uncommented
	AddOrRemoveCommands(false);
	// TODO: might cause crash after uncommented
	AddOrRemoveCommands();
}

void ReloadConfig(APlayerController* pc, FString*, bool)
{
	auto* spc = static_cast<AShooterPlayerController*>(pc);

	try
	{
		Reload();
	}
	catch (const std::exception& error)
	{
		AsaApi::GetApiUtils().SendServerMessage(spc, FColorList::Red, "Failed to reload config. ERROR: {}", error.what());
	}

	AsaApi::GetApiUtils().SendServerMessage(spc, FColorList::Green, "Config Reloaded.");
}

void ReloadConfigRcon(RCONClientConnection* rcon_connection, RCONPacket* rcon_packet, UWorld*)
{
	FString reply;

	try
	{
		Reload();
	}
	catch (const std::exception& error)
	{
		reply = error.what();
		rcon_connection->SendMessageW(rcon_packet->Id, 0, &reply);
		return;
	}

	reply = "Config Reloaded.";
	rcon_connection->SendMessageW(rcon_packet->Id, 0, &reply);
}
 
void AddReloadCommands(bool addCmd = true)
{
	if (addCmd)
	{
		AsaApi::GetCommands().AddConsoleCommand("Chargenode.Reload", &ReloadConfig);
		AsaApi::GetCommands().AddRconCommand("Chargenode.Reload", &ReloadConfigRcon);
	}
	else
	{
		AsaApi::GetCommands().RemoveConsoleCommand("Chargenode.Reload");
		AsaApi::GetCommands().RemoveRconCommand("Chargenode.Reload");
	}
}