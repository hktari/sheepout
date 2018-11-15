// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AI/AISheepController.h"
#include "BTTask_SetSheepState.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API UBTTask_SetSheepState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Node, EditAnywhere)
	TEnumAsByte<ESheepStates> State;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
