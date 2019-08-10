// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_HealthBar.generated.h"

/**
 * 
 */
class UProgressBar;
class ACharacterBase;
UCLASS()
class ARPG_API UUI_HealthBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		UProgressBar* ManaBar;

	UFUNCTION()
		float HealthDelegate();

	UFUNCTION()
		float ManaDelegate();

public:
	virtual bool Initialize() override;

	ACharacterBase* OwnPawn;
};
