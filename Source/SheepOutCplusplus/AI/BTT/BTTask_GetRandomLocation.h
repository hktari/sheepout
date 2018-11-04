// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GetRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API UBTTask_GetRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	/** fixed distance added to threshold between AI and goal location in destination reach test */
	UPROPERTY(Category = Node, EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Radius = 100.0f;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
