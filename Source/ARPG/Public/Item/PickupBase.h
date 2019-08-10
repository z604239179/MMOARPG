// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "PickupBase.generated.h"

//#define NULLITEM 0
//UENUM()
//enum class EGoodsType : uint8
//{
//	None,
//	Equipment,
//	Consume,
//	Stuff,
//};

USTRUCT(BlueprintType)
struct FLoots
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		int32  Nums;
	UPROPERTY(EditDefaultsOnly)
		FPrimaryAssetId GoodsID;

	FLoots() : Nums(0)
	{

	}
	FLoots(FPrimaryAssetId ID, int32 InNum):GoodsID(ID),Nums(InNum)
	{
	}
};

UCLASS()
class ARPG_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

private:	/*
	UPROPERTY(ReplicatedUsing = OnRep_ItemInfoInit)
		class UPrimaryGoods* ItemInfo;*/

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class USphereComponent* PickupRangeComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class UStaticMeshComponent* StaticMeshComp;

	UFUNCTION()
		void OnEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

/*
	UFUNCTION()
		virtual void OnRep_ItemInfoInit() {};*/


public:	
	UPROPERTY(Replicated,EditDefaultsOnly)
		TArray<FLoots> LootsList;

	///*仅在服务器上执行*/
	//void InitPickup(UPrimaryGoods* _Info);

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//	EGoodsType m_GoodsType;
	///*物品当前数量*/
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	uint8 CurrentNum;
	//

	//FORCEINLINE UPrimaryGoods* GetBasicItemInfo() const { return ItemInfo; }

	//virtual bool UseItem() { return false; }

};
