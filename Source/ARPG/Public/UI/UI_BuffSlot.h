// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_BuffSlot.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_BuffSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UPBuff* LocalBuffInfo;

	UPROPERTY(meta = (BindWidget))
		class UImage* BuffIcon;

public:
	void InitBuffSlot(UPBuff* InBuffInfo);
};
