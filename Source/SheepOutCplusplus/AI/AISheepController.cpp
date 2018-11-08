// Fill out your copyright notice in the Description page of Project Settings.

#include "AISheepController.h"
#include "SheepCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AAISheepController::AAISheepController(const FObjectInitializer & objectInitializer) 
	: Super(objectInitializer)
{
	BehaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	TargetLocationKeyName = "TargetLocation";
}

void AAISheepController::Possess(class APawn* inPawn)
{
	Super::Possess(inPawn);

	ASheepCharacter* sheep = Cast<ASheepCharacter>(inPawn);
	if (sheep && sheep->BehaviorTree)
	{
		if (sheep->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*sheep->BehaviorTree->BlackboardAsset);
		}
		BehaviorComp->StartTree(*sheep->BehaviorTree);
	}
}

void AAISheepController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
	
}

void AAISheepController::MoveToLocation(FVector & location)
{
}
