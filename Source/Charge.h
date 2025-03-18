

void ChargeCallback(AShooterPlayerController* pc, FString* param, int, int)
{
	Log::GetLog()->warn("Function: {}", __FUNCTION__);

	// permissions check
	FString perms = GetPriorPermByEOSID(pc->GetEOSId());
	nlohmann::json command = GetCommandString(perms.ToString(), "RepairItemCMD");

	if (command.is_null() || (!command.is_null() && command.value("Enabled", false) == false))
	{
		if (Chargenode::config["Debug"].value("Permissions", false) == true)
		{
			Log::GetLog()->info("{} No permissions. Command: {}", pc->GetCharacterName().ToString(), __FUNCTION__);
		}

		AsaApi::GetApiUtils().SendNotification(pc, FColorList::Red, 1.3f, 15.0f, nullptr, Chargenode::config["Messages"].value("RepairItemsPermErrorMSG", "You don't have permission to use this command.").c_str());

		return;
	}

	// points checking
	if (Points(pc->GetEOSId(), command.value("Cost", 0), true) == false)
	{
		if (Chargenode::config["Debug"].value("Points", false) == true)
		{
			Log::GetLog()->info("{} don't have points. Command: {}", pc->GetCharacterName().ToString(), __FUNCTION__);
		}

		AsaApi::GetApiUtils().SendNotification(pc, FColorList::Red, 1.3f, 15.0f, nullptr, Chargenode::config["Messages"].value("RepairItemsPointsErrorMSG", "Not enough points.").c_str());

		return;
	}

	ACharacter* character = pc->CharacterField().Get();
	if (!character) return;

	APrimalCharacter* primalCharacter = static_cast<APrimalCharacter*>(character);
	if (!primalCharacter) return;

	AActor* actor = primalCharacter->GetAimedActor(ECollisionChannel::ECC_GameTraceChannel2, 0i64, 0.0, 0.0, 0i64, 0i64, false, false, false, 0i64);

	if (!actor) return;

	if (!actor->IsA(APrimalStructureItemContainer::GetPrivateStaticClass()))return;

	APrimalStructureItemContainer* structure = static_cast<APrimalStructureItemContainer*>(actor);

	if (!structure) return;

	OverrideChargeNodeSettings(structure);

	// points deductions
	Points(pc->GetEOSId(), command.value("Cost", 0));
}