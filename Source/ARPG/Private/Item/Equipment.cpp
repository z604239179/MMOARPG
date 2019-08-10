// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment.h"
#include "Net/UnrealNetwork.h"
#include "CharacterBase.h"
// Sets default values
AEquipment::AEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	MeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		EquipmentOwner = Cast<ACharacterBase>(GetOwner());
	}
}





void AEquipment::InitEquipment_Implementation(FPrimaryAssetId EquipInfoId)
{

}

void AEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEquipment, EquipmentOwner);
}