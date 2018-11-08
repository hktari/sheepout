// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ICommandable.h"
#include "SheepCharacter.generated.h"

UCLASS(Blueprintable)
class SHEEPOUTCPLUSPLUS_API ASheepCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* SelectionSprite;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		class UBehaviorTree* BehaviorTree;

	// Sets default values for this pawn's properties
	ASheepCharacter();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Select();
	void Deselect();

	bool GetIsSelected() { return m_bIsSelected; }
private :
	bool m_bIsSelected;
};
