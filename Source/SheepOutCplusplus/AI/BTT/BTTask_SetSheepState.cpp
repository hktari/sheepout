// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SetSheepState.h"
/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBTTask_SetSheepState::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Enum>(BlackboardKey.GetSelectedKeyID(), static_cast<uint8>(State.GetValue()));
	return EBTNodeResult::Succeeded;
}
