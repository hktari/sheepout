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
	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* SelectionSprite;
	// Sets default values for this pawn's properties
	ASheepCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Command(int command) override;
	virtual void ShowUI() override;
	virtual void Select() override;
	virtual void Deselect() override;
};
