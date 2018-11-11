// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GuardCharacter.generated.h"

class UPawnSensingComponent;

/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API AGuardCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
	AGuardCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* SelectionSprite;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* m_pBehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UPawnSensingComponent* m_pPawnSensingComp;
	
protected:
	/* Triggered by pawn sensing component when a pawn is spotted */
	/* When using functions as delegates they need to be marked with UFUNCTION(). We assign this function to FSeePawnDelegate */
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

public:
	UBehaviorTree* GetBehaviorTree() { return m_pBehaviorTree; }
	UPawnSensingComponent* GetPawnSensingComp() { return m_pPawnSensingComp; }

};
