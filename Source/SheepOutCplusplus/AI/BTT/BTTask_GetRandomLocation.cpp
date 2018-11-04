// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_GetRandomLocation.h"
#include "AISystem.h"
#include "AIController.h"
#include "NavigationSystem.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get actor location
	APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (pawn)
	{
		FVector curLocation = pawn->GetActorLocation();
		
		FNavLocation resultLocation;
		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerComp.GetAIOwner());
		if (NavSystem && NavSystem->GetRandomPointInNavigableRadius(curLocation, Radius, resultLocation))
		{
			/* The selected key should be "PatrolLocation" in the BehaviorTree setup */
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), resultLocation.Location);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
