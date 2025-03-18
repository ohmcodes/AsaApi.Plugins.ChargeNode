


DECLARE_HOOK(AShooterCharacter_Die, bool, AShooterCharacter*, float, FDamageEvent*, AController*, AActor*);

bool Hook_AShooterCharacter_Die(AShooterCharacter* shooter_character, float KillingDamage, FDamageEvent* DamageEvent, AController* Killer, AActor* DamageCauser)
{
	FString playername = shooter_character->PlayerNameField();

	Log::GetLog()->info("Player: {}, Dies!", playername.ToString());

	return AShooterCharacter_Die_original(shooter_character, KillingDamage, DamageEvent, Killer, DamageCauser);
}


DECLARE_HOOK(APrimalStructureItemContainer_ServerOpenRemoteInventory, void, APrimalStructureItemContainer*, AShooterPlayerController*);

void Hook_APrimalStructureItemContainer_ServerOpenRemoteInventory(APrimalStructureItemContainer* structure, AShooterPlayerController* pc)
{
	if (structure->DescriptiveNameField().Equals("Charge Node"))
	{
		OverrideChargeNodeSettings(structure);
	}

	APrimalStructureItemContainer_ServerOpenRemoteInventory_original(structure, pc);
}

//void BPCraftingFinishedNotification(UPrimalItem* itemToBeCrafted)  { NativeCall<void, UPrimalItem*>(this, "UPrimalInventoryComponent.BPCraftingFinishedNotification(UPrimalItem*)", itemToBeCrafted) ; }

DECLARE_HOOK(UPrimalInventoryComponent_BPCraftingFinishedNotification, void, UPrimalInventoryComponent* , UPrimalItem*);
void Hook_UPrimalInventoryComponent_BPCraftingFinishedNotification(UPrimalInventoryComponent* invComp,UPrimalItem* itemToBeCrafted)
{
	UPrimalInventoryComponent_BPCraftingFinishedNotification_original(invComp, itemToBeCrafted);

	APrimalStructureItemContainer* structure = static_cast<APrimalStructureItemContainer*>(invComp->OwnerPrivateField());

	if(structure)
		OverrideChargeNodeSettings(structure);
}


void SetHooks(bool addHooks = true)
{
	if (addHooks)
	{
		AsaApi::GetHooks().SetHook("AShooterCharacter.Die(float,FDamageEvent&,AController*,AActor*)", &Hook_AShooterCharacter_Die, &AShooterCharacter_Die_original);

		AsaApi::GetHooks().SetHook("APrimalStructureItemContainer.ServerOpenRemoteInventory(AShooterPlayerController*)", &Hook_APrimalStructureItemContainer_ServerOpenRemoteInventory, &APrimalStructureItemContainer_ServerOpenRemoteInventory_original);

		AsaApi::GetHooks().SetHook("UPrimalInventoryComponent.BPCraftingFinishedNotification(UPrimalItem*)", &Hook_UPrimalInventoryComponent_BPCraftingFinishedNotification, &UPrimalInventoryComponent_BPCraftingFinishedNotification_original);
	}
	else
	{
		AsaApi::GetHooks().DisableHook("AShooterCharacter.Die(float,FDamageEvent&,AController*,AActor*)", &Hook_AShooterCharacter_Die);

		AsaApi::GetHooks().DisableHook("APrimalStructureItemContainer.ServerOpenRemoteInventory(AShooterPlayerController*)", &Hook_APrimalStructureItemContainer_ServerOpenRemoteInventory);

		AsaApi::GetHooks().DisableHook("UPrimalInventoryComponent.BPCraftingFinishedNotification(UPrimalItem*)", &Hook_UPrimalInventoryComponent_BPCraftingFinishedNotification);
	}
}