// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ARPGGameInstance.h"
#include "ARPGGameModeBase.generated.h"


/**
 * 
 */
class APickupBase;
UCLASS()
class ARPG_API AARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	class UARPGGameInstance* MyGameInstance;

	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Data")
		TSubclassOf<class ACharacterBase> TestCharacterClass;

	TArray<class AMyPlayerController*> CurrentPlayerList;

	uint8 CurrentPlayerNums;
public:
	AARPGGameModeBase();

	UFUNCTION(BlueprintCallable)
	APickupBase* SpawnItem(FPrimaryAssetId PrimaryId,uint8 Nums, FTransform SpawnTransfrom, AActor* ItemOwner = nullptr);

	UFUNCTION()
		void BroadcastMessage(const FString& msg,uint8 NetworkId);
		
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
