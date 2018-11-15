// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Scare.h"
/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AI/AISheepController.h"
#include "SheepCharacter.h"

EBTNodeResult::Type UBTTask_Scare::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto sheep = Cast<ASheepCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()));
	if (sheep)
	{
		if (auto aiController = Cast<AAISheepController>(sheep->GetController()))
		{
			aiController->Scare(*OwnerComp.GetOwner());
			return EBTNodeResult::Succeeded;
		}
	}
	UE_LOG(LogBehaviorTree, Warning, TEXT("Couldn't scare sheep."));
	return EBTNodeResult::Failed;
}
