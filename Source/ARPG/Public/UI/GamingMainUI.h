// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "GamingMainUI.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UGamingMainUI : public UUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* ChildPanel;

	UPROPERTY(meta = (BindWidget))
		class UUI_CheatPanel* UMG_CheatPanel;

	UPROPERTY(meta = (BindWidget))
		class UUI_StateBar* UMG_StateBar;

	UPROPERTY(meta = (BindWidget))
		class UUI_BuffPanel* UMG_BuffPanel;

	class UUI_Inventory* InventoryPanel;

	class UUI_Character* CharacterPanel;


	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUI_Inventory> InventoryClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUI_Character> CharacterPanelClass;

public:
	virtual bool Initialize() override;

	void AddMessage(const FString& msg, const FString& InstigaterName);

	bool CallInventory();

	bool CallCharacterPanel();

	bool CallCheatPanel();

	void AddChild(UWidget* InWidget);
	void RemoveChild(UWidget* InWidget);

	void AddBuff(class UPBuff* BuffInfo);
	void RemoveBuff(UPBuff* BuffInfo);
};
