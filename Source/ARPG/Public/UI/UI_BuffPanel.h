// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UI_BuffPanel.generated.h"

/**
 * 
 */
class UUI_BuffSlot;
class UPBuff;
UCLASS()
class ARPG_API UUI_BuffPanel : public UUIBase
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		TMap<UPBuff*, UUI_BuffSlot*> BuffList;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUI_BuffSlot> BuffSlotClass;

	UPROPERTY(meta = (BindWidget))
		class UWrapBox* BuffPanel;
public:
	void AddBuff(UPBuff* BuffInfo);
	void RemoveBuff(UPBuff* BuffInfo);
};
