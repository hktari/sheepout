// Fill out your copyright notice in the Description page of Project Settings.

#include "SheepCharacter.h"


// Sets default values
ASheepCharacter::ASheepCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ASheepCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASheepCharacter::Command()
{
	UE_LOG(LogTemp, Display, TEXT("Commanded"));
}

