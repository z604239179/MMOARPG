// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGGameModeBase.h"
#include "PickupBase.h"
#include "MyPlayerController.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"


void AARPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	MyGameInstance = GetGameInstance<UARPGGameInstance>();
}

AARPGGameModeBase::AARPGGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	DefaultPawnClass = nullptr;
	CurrentPlayerNums = 0;
}





APickupBase* AARPGGameModeBase::SpawnItem(FPrimaryAssetId PrimaryId, uint8 Nums, FTransform SpawnTransfrom, AActor* ItemOwner /*= nullptr*/)
{
	UPrimaryGoods* TempGoods = UMyAssetManager::FindObjectFromId<UPrimaryGoods>(PrimaryId);
	APickupBase* RetPickup = GetWorld()->SpawnActorDeferred<APickupBase>(APickupBase::StaticClass(), SpawnTransfrom, ItemOwner, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	RetPickup->LootsList.Add(FLoots(PrimaryId, Nums));
	RetPickup->SetReplicates(true);
	RetPickup->FinishSpawning(SpawnTransfrom);
	return RetPickup;
}









void AARPGGameModeBase::BroadcastMessage(const FString& msg, uint8 NetworkId)
{
	
	for (auto it : CurrentPlayerList)
	{
		it->ReceiveMessage(msg, CurrentPlayerList[NetworkId]->MyData->GetPlayerName());
	}
}

void AARPGGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AMyPlayerController* NewMyPlayer = Cast<AMyPlayerController>(NewPlayer);
	NewMyPlayer->NetworkIndex = CurrentPlayerNums;
	CurrentPlayerList.Add(NewMyPlayer);
	CurrentPlayerNums++;

	APlayerStart* DefaultStart = nullptr;

	if (GetWorld())
		for (TActorIterator<APlayerStart> it(GetWorld(), APlayerStart::StaticClass()); it; ++it)
		{
			DefaultStart = *it;
			break;
		}

	if (DefaultStart)
	{		
		if (TestCharacterClass)
		{
			FActorSpawnParameters SpawnParama;
			SpawnParama.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ACharacterBase* TempPawn = GetWorld()->SpawnActor<ACharacterBase>(TestCharacterClass, DefaultStart->GetActorLocation(), DefaultStart->GetActorRotation(), SpawnParama);
			NewPlayer->Possess(TempPawn);
			Cast<AMyPlayerController>(NewPlayer)->InitMyPawn(TempPawn);
		}

	}

}

