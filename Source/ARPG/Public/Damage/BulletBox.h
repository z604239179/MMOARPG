// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageBoxBase.h"
#include "BulletBox.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API ABulletBox : public ADamageBoxBase
{
	GENERATED_BODY()
public:
	ABulletBox();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Components")
		class UProjectileMovementComponent* ProjectileComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UParticleSystemComponent* BulletParticle;


	virtual void BeginPlay()override;
};
