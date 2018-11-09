// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_UpdateMoveTo.h"
/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

void UBTService_UpdateMoveTo::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	FBTServiceUpdateMoveToMemory* memory = reinterpret_cast<FBTServiceUpdateMoveToMemory*>(NodeMemory);
	FVector currentTargetLocation = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
	
	// Initialization
	if (memory->PreviousTargetLocation == FVector::ZeroVector)
	{
		memory->PreviousTargetLocation = currentTargetLocation;
	}
	else 
	{
		if (memory->PreviousTargetLocation != currentTargetLocation)
		{
			UE_LOG(LogTemp, Warning, TEXT("Restarting"));
			OwnerComp.RestartTree();
		}
	}
}

uint16 UBTService_UpdateMoveTo::GetInstanceMemorySize() const
{
	return sizeof(FBTServiceUpdateMoveToMemory);
}
