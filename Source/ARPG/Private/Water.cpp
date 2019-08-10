// Fill out your copyright notice in the Description page of Project Settings.

#include "Water.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/AudioComponent.h"
#include "CharacterBase.h"

// Sets default values
AWater::AWater()
{
 //	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaterPanel = CreateDefaultSubobject<UStaticMeshComponent>("WaterPanel");
	WaterVolumn = CreateDefaultSubobject<UBoxComponent>("WaterVolumn");
	PostProcessComp = CreateDefaultSubobject<UPostProcessComponent>("PostProcessComp");
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	
	RootComponent = WaterPanel;
	WaterVolumn->SetupAttachment(RootComponent);
	PostProcessComp->SetupAttachment(WaterVolumn);
	AudioComp->SetupAttachment(WaterVolumn);


	//PostProcessComp->Settings.DepthOfFieldMethod = DOFM_Gaussian;
	//PostProcessComp->Settings.DepthOfFieldFarTransitionRegion = 3200.f;
	//PostProcessComp->Settings.DepthOfFieldNearBlurSize = 0;
	//PostProcessComp->Settings.DepthOfFieldFarBlurSize = 15;

	//PostProcessComp->Settings.BloomIntensity = 2.f;

	//PostProcessComp->Settings.LensFlareTint = FLinearColor(0.4f, 1.f, 1.f);
	//PostProcessComp->Settings.LensFlareBokehSize = 8.f;
	//PostProcessComp->Settings.VignetteIntensity = 0.8f;

	//PostProcessComp->Settings.ColorSaturation = FVector4(1.2f, 1.0f, 1.0f);
	//PostProcessComp->Settings.SceneColorTint = FLinearColor(0, 0.4f, 1.f);
	//PostProcessComp->Settings.AmbientOcclusionIntensity = 1.f;

	//PostProcessComp->BlendRadius = 0;
	//PostProcessComp->bUnbound = false;


}

// Called when the game starts or when spawned
void AWater::BeginPlay()
{
	Super::BeginPlay();
	WaterVolumn->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWater::OnSomethingEnterWater);/*
	WaterPanel->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWater::OnSomethingLeaveWater);
	WaterPanel->OnComponentEndOverlap.AddUniqueDynamic(this, &AWater::OnSomethingEnterVolumn);*/
	/*AudioComp->AttenuationSettings->Attenuation.AttenuationShape = EAttenuationShape::Box;*/
}

void AWater::OnSomethingEnterWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->GetVelocity().Z >= 200.f)
	{
		if (HardSplash)
		{
			GetWorld()->GetAudioDevice()->PlaySoundAtLocation(HardSplash, GetWorld(), HardSplash->GetVolumeMultiplier(), HardSplash->GetPitchMultiplier(), 0, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), nullptr, nullptr, nullptr, OtherActor);
		}
	}
	else
	{
		float TempVolumn = FMath::Clamp(OtherActor->GetVelocity().Z / 200.f,0.5f,1.f);
		
		if (SoftSplash)
		{
			GetWorld()->GetAudioDevice()->PlaySoundAtLocation(SoftSplash, GetWorld(), TempVolumn, SoftSplash->GetPitchMultiplier(), 0, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), nullptr, nullptr, nullptr, OtherActor);
		}
	}
}

//void AWater::OnSomethingLeaveWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	ACharacterBase*  TempPawn = Cast<ACharacterBase>(OtherActor);
//	
//	if (TempPawn&&WaterVolumn->IsOverlappingActor(OtherActor))
//	{
//		TempPawn->GetCharacterMovement()->Velocity.Z = 0;
//		TempPawn->bCanMoveUp = false;
//		
//	}
//}
//
//void AWater::OnSomethingEnterVolumn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//
//	ACharacterBase*  TempPawn = Cast<ACharacterBase>(OtherActor);
//	if (TempPawn&&WaterVolumn->IsOverlappingActor(OtherActor))
//	{
//		TempPawn->bCanMoveUp = true;
//	}
//
//}

// Called every frame
void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

