// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GamingHUD.generated.h"

/**
 * 
 */
class UUI_CheatPanel;
UCLASS()
class ARPG_API AGamingHUD : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UGamingMainUI> MainUIClass;

	UGamingMainUI* MainUIInstance;


	virtual void BeginPlay() override;

public:
	bool CallInventory();

	bool CallCharacterPanel();

	bool CallCheatPanel();

	void AddMessage(const FString& msg, const FString& InstigaterName);

	void AddBuff(class UPBuff* BuffInfo);
	void RemoveBuff(class UPBuff* BuffInfo);

	void CreateUI();

	UFUNCTION(BlueprintCallable)
		void AddChild(UWidget* InWidget);
	UFUNCTION(BlueprintCallable)
		void RemoveChild(UWidget* InWidget);
};
