// Fill out your copyright notice in the Description page of Project Settings.

#include "SheepCharacter.h"
#include "Paper2D/Classes/PaperSpriteComponent.h"

// Sets default values
ASheepCharacter::ASheepCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectionSprite = CreateDefaultSubobject<UPaperSpriteComponent>("SelectionSprite");
	SelectionSprite->AttachTo(RootComponent);
	SelectionSprite->SetVisibility(false);
}

// Called every frame
void ASheepCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASheepCharacter::Select()
{
	m_bIsSelected = true;
	SelectionSprite->SetVisibility(true);
}

void ASheepCharacter::Deselect()
{
	m_bIsSelected = false;
	SelectionSprite->SetVisibility(false);
}
