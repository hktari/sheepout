// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ICommandable.h"
#include "SheepCharacter.generated.h"

UCLASS(Blueprintable)
class SHEEPOUTCPLUSPLUS_API ASheepCharacter : public APaperCharacter, public IICommandable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASheepCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Command() override;
};
