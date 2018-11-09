// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateMoveTo.generated.h"

struct FBTServiceUpdateMoveToMemory
{
public:
	FBTServiceUpdateMoveToMemory() 
		: PreviousTargetLocation(FVector::ZeroVector) {}
	FVector PreviousTargetLocation;
};

/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API UBTService_UpdateMoveTo : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual uint16 GetInstanceMemorySize() const override;
};
