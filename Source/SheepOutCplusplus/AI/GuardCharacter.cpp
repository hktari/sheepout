// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardCharacter.h"
#include "PaperSpriteComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/AIGuardController.h"
#include "SheepCharacter.h"
#include "Components/BoxComponent.h"

AGuardCharacter::AGuardCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pPawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	SelectionSprite = CreateDefaultSubobject<UPaperSpriteComponent>("SelectionSprite");
	SelectionSprite->AttachTo(RootComponent);
	SelectionSprite->SetVisibility(false);

	SheepShield = CreateDefaultSubobject<UBoxComponent>(TEXT("SheepShield"));
	SheepShield->SetupAttachment(RootComponent);
}

void AGuardCharacter::BeginPlay()
{
	Super::BeginPlay();
}


