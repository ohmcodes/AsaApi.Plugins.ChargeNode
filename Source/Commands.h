

void AddOrRemoveCommands(bool addCmd = true)
{
	const FString ChargeNode = Chargenode::config["Commands"]["ChargeCMD"].get<std::string>().c_str();
	if (!ChargeNode.IsEmpty())
	{
		if (addCmd)
		{
			AsaApi::GetCommands().AddChatCommand(ChargeNode, &ChargeCallback);
		}
		else
		{
			AsaApi::GetCommands().RemoveChatCommand(ChargeNode);
		}
	}
}