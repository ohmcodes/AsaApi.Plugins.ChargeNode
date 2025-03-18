

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

	const FString RepairItems = Chargenode::config["Commands"]["RepairItemCMD"].get<std::string>().c_str();
	if (!RepairItems.IsEmpty())
	{
		if (addCmd)
		{
			AsaApi::GetCommands().AddChatCommand(RepairItems, &RepairItemsCallback);
		}
		else
		{
			AsaApi::GetCommands().RemoveChatCommand(RepairItems);
		}
	}

	const FString DeletePlayer = Chargenode::config["Commands"]["DeletePlayerCMD"].get<std::string>().c_str();
	if (!DeletePlayer.IsEmpty())
	{
		if (addCmd)
		{
			AsaApi::GetCommands().AddChatCommand(DeletePlayer, &DeletePlayerCallback);
		}
		else
		{
			AsaApi::GetCommands().RemoveChatCommand(DeletePlayer);
		}
	}
}