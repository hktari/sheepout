// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIGuardController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UENUM(BlueprintType)
enum class EGuardStates : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Herding UMETA(DisplayName = "Herding")
};
/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API AAIGuardController : public AAIController
{
	GENERATED_BODY()

	AAIGuardController(const class FObjectInitializer& ObjectInitializer);

	/* Called whenever the controller possesses a character bot */
	virtual void Possess(APawn* InPawn) override;

	virtual void UnPossess() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName StateKeyName;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKeyName;

private:
	UBehaviorTreeComponent* m_pBehaviorComp;
	UBlackboardComponent* m_pBlackboardComp;

	/* Triggered by pawn sensing component when a pawn is spotted */
	/* When using functions as delegates they need to be marked with UFUNCTION(). We assign this function to FSeePawnDelegate */
	UFUNCTION()
		void OnSeePawn(APawn* InPawn);

	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

public:
	UFUNCTION(BlueprintCallable)
	EGuardStates GetState();

	UBehaviorTreeComponent* GetBehaviorComp() { return m_pBehaviorComp; }
	UBlackboardComponent* GetBlackbardComp() { return m_pBlackboardComp; }
};
