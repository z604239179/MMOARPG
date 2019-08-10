// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageBoxBase.h"
#include "ARPG.h"
#include "Monster.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Weapon.h"
#include "Camera/CameraShake.h"
#include "Damage/BlockDamageType.h"
// Sets default values
ADamageBoxBase::ADamageBoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	DamageBox->SetCollisionObjectType(ECC_DamageBox);
	DamageBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DamageBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = DamageBox;


}

void ADamageBoxBase::InitDamageBox(TSubclassOf<UDamageType> DamageType, FVector BoxSize)
{
	MyDamageType = DamageType;
	DamageBox->SetWorldScale3D(BoxSize);
}

void ADamageBoxBase::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		DamageSource = Cast<ACharacterBase>(GetInstigator());
		SourceWeapon = Cast<AWeapon>(GetOwner());
		DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ADamageBoxBase::OnDamageActor);
	}
}



void ADamageBoxBase::OnDamageActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacterBase* DamageCharacter = Cast<ACharacterBase>(OtherActor);
	if (!DamagedPawn.Contains(DamageCharacter))
	{
		if (DamageCharacter->CharacterType != DamageSource->CharacterType&&DamageCharacter->bCanBeDamaged)
		{


			float DamageValue = DamageSource->GetCurrentInfoData()->GetAttributefromName(EPropertyName::ATK);
			SourceWeapon->ApplyDamageToPawn(DamageCharacter, DamageValue, DamageSource->GetController(), DamageSource, MyDamageType);
			//GetWorldTimerManager().ClearTimer(timerhandle);
			//	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.02f);
			//	GetWorldTimerManager().SetTimer(timerhandle, this, &ADamageBoxBase::ResetTimeDilation, 0.0015f, false);
			
			SourceWeapon->PlayEffect(DamageCharacter);
			DamagedPawn.AddUnique(DamageCharacter);
		}
	}

}

