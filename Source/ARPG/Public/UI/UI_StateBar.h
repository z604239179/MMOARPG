// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UI_StateBar.generated.h"

/**
 * 
 */
class UProgressBar;
UCLASS()
class ARPG_API UUI_StateBar : public UUIBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthProgress;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ManaProgress;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* NameText;

	UFUNCTION()
		float GetHealthPer();

	UFUNCTION()
		float GetManaPer();

	class APlayerCharacter* MyPawn;
public:

	virtual bool Initialize() override;
};
