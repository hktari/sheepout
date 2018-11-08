// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AISheepController.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API AAISheepController : public AAIController
{
	GENERATED_BODY()

	AAISheepController(const class FObjectInitializer& ObjectInitializer);

	/* Called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

public:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetLocationKeyName;

	void MoveToLocation(FVector& location);

	UBehaviorTreeComponent* GetBehaviorComp() { return BehaviorComp; }
	UBlackboardComponent* GetBlackbardComp() { return BlackboardComp; }
};
