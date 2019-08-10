// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSpawner.h"
#include "Components/SphereComponent.h"
#include "MyAssetManager.h"
#include "PrimaryMonster.h"
#include "Monster.h"
#include "Math/UnrealMathUtility.h"
#include "NavigationSystem.h"
#include "MyAIController.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnRange = CreateDefaultSubobject<USphereComponent>("SpawnRange");
	SpawnRange->SetupAttachment(RootComponent);
	TotalProbability = 0;
}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		//计算总概率
		for (auto& it : MonsterSpawnList)
		{
			TotalProbability+=it.Value;
		}
		SpawnRadius = SpawnRange->GetScaledSphereRadius();
		SpawnMonster();
	}
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSpawner::SpawnMonster()
{
	if (HasAuthority())
	{
		for (int32 it = FlushNums; it > 0; --it)
		{
			float TempProbility = FMath::RandRange(0.f, TotalProbability);
			for (auto& ListIt : MonsterSpawnList)
			{

				TempProbility -= ListIt.Value;
				//判断生成
				if (TempProbility <= 0)
				{
					UNavigationSystemV1* NavigationRef = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
					if (NavigationRef)
					{

						FVector SpawnLocation;
						NavigationRef->K2_GetRandomReachablePointInRadius(GetWorld(), SpawnRange->GetComponentLocation(), SpawnLocation, SpawnRadius);

						UPrimaryMonster* MonsterInfo = UMyAssetManager::Get().FindObjectFromId<UPrimaryMonster>(ListIt.Key);
						AAIBase* TempMonster = GetWorld()->SpawnActorDeferred<AMonster>(MonsterInfo->AIClass,FTransform(  FRotator::ZeroRotator, SpawnLocation), nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
						TempMonster->SetBasicAIInfo(MonsterInfo);
						TempMonster->bIsProtrol = true;
						TempMonster->FinishSpawning(FTransform(FRotator::ZeroRotator, SpawnLocation));
						
					}
					else
					{

						UE_LOG(LogTemp, Error, TEXT("NavigationRef Is Null"))
					}

				}
			}

		}
		//UMyAssetManager
	}
}

