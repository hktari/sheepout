// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardCharacter.h"
#include "PaperSpriteComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/AIGuardController.h"
#include "SheepCharacter.h"

AGuardCharacter::AGuardCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pPawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	SelectionSprite = CreateDefaultSubobject<UPaperSpriteComponent>("SelectionSprite");
	SelectionSprite->AttachTo(RootComponent);
	SelectionSprite->SetVisibility(false);
}

void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* This is the earliest moment we can bind our delegates to the component */
	if (m_pPawnSensingComp)
	{
		m_pPawnSensingComp->OnSeePawn.AddDynamic(this, &AGuardCharacter::OnSeePlayer);
		m_pPawnSensingComp->OnHearNoise.AddDynamic(this, &AGuardCharacter::OnHearNoise);
	}
}


void AGuardCharacter::OnSeePlayer(APawn* Pawn)
{
	/* Keep track of the time the player was last sensed in order to clear the target */
	/*LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;*/

	AAIGuardController* AIController = Cast<AAIGuardController>(GetController());
	ASheepCharacter* SensedPawn = Cast<ASheepCharacter>(Pawn);
	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("I see you "));
	}
}


void AGuardCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	/*if (!IsAlive())
	{
		return;
	}

	if (!bSensedTarget)
	{
		BroadcastUpdateAudioLoop(true);
	}

	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	ASZombieAIController* AIController = Cast<ASZombieAIController>(GetController());
	if (AIController)
	{
		AIController->SetTargetEnemy(PawnInstigator);
	}*/
}

