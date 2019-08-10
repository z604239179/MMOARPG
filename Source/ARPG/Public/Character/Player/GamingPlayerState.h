// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GamingPlayerState.generated.h"


/**
 * 
 */




UCLASS()
class ARPG_API AGamingPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AGamingPlayerState();

protected:

	virtual void BeginPlay() override;

};
