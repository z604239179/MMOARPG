// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class AMonster;
UCLASS()
class ARPG_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditInstanceOnly)
		TMap<FPrimaryAssetId, float> MonsterSpawnList;

	UPROPERTY(EditInstanceOnly)
		float FlushInterval;

	UPROPERTY(EditInstanceOnly,meta=(ClampMin = 0,ClampMax=255))
		int32 FlushNums;

	UPROPERTY(VisibleInstanceOnly)
		class USphereComponent* SpawnRange;

	float TotalProbability;

	float SpawnRadius;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnMonster();
};
