// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletBox.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


ABulletBox::ABulletBox()
{
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	BulletParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	BulletParticle->SetupAttachment(RootComponent);
	ProjectileComp->InitialSpeed = 1800.f;
	ProjectileComp->ProjectileGravityScale = 0.1f;
	ProjectileComp->bRotationFollowsVelocity = true;
	UParticleSystem* LoadParticle = LoadObject<UParticleSystem>(NULL, TEXT("ParticleSystem'/Game/Effects/Particle_Systems/Bow/P_Arrow.P_Arrow'"));

	BulletParticle->SetTemplate(LoadParticle);
}





void ABulletBox::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);

}
