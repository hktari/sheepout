// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Interact.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Interactables/Interactable.h"
#include "ICommandable.h"
#include "AI/AISheepController.h"
//class AAISheepController;

EBTNodeResult::Type UBTTask_Interact::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAISheepController* commandable = Cast<AAISheepController>(OwnerComp.GetAIOwner());
	/*IInteractable* t;
	t->StartInteraction(commandable);*/
	IInteractable* interactable = Cast<IInteractable>(
		OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()));
	if (commandable && interactable)
	{
		interactable->StartInteraction(*commandable);
		return EBTNodeResult::Succeeded;
	}
	UE_LOG(LogBehaviorTree, Warning, TEXT("Failed to execute interact"));
	return EBTNodeResult::Failed;
}
