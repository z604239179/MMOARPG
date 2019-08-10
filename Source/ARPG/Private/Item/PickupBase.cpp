// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBase.h"
#include "Components/SphereComponent.h"
#include "ARPG.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APickupBase::APickupBase()
	//:m_GoodsType(EGoodsType::None)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickupRangeComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRangeComp"));
	RootComponent = PickupRangeComponent;
	PickupRangeComponent->SetCollisionObjectType(ECC_Item);
	PickupRangeComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupRangeComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	PickupRangeComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnEnterRange);
}

void APickupBase::OnEnterRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
	APlayerCharacter* PickPawn = Cast<APlayerCharacter>(OtherActor);
	if (PickPawn&&PickPawn->HasAuthority())
	{
		APlayerInfoData* TempData = Cast<APlayerInfoData>(PickPawn->GetPlayerInfoData());
		TempData->PickupItem(this);
		Destroy(true);
	}
}

//void APickupBase::InitPickup(UPrimaryGoods* _Info)
//{
//	ItemInfo = _Info;
//	OnRep_ItemInfoInit();
//}


void APickupBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickupBase, LootsList);
}