

void ChargeCallback(AShooterPlayerController* pc, FString* param, int, int)
{

	ACharacter* character = pc->CharacterField().Get();
	if (!character) return;

	APrimalCharacter* primalCharacter = static_cast<APrimalCharacter*>(character);
	if (!primalCharacter) return;

	AActor* actor = primalCharacter->GetAimedActor(ECollisionChannel::ECC_GameTraceChannel2, 0i64, 0.0, 0.0, 0i64, 0i64, false, false, false, 0i64);

	if (!actor) return;

	if (!actor->IsA(APrimalStructureItemContainer::GetPrivateStaticClass()))return;

	APrimalStructureItemContainer* structure = static_cast<APrimalStructureItemContainer*>(actor);

	if (!structure) return;

	if (!structure->DescriptiveNameField().Equals("Charge Node")) return;

	FProperty* currentNodeState = structure->FindProperty(FName("currentNodeState", EFindName::FNAME_Add));

	currentNodeState->Set(structure, 2);
	structure->MulticastProperty(FName("currentNodeState", EFindName::FNAME_Add), false);

	structure->BeginPlay();
}