// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AISheepController.h"
#include "SheepCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PaperSpriteComponent.h"

AAISheepController::AAISheepController(const FObjectInitializer & objectInitializer) 
	: Super(objectInitializer)
{
	BehaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	TargetLocationKeyName = "TargetLocation";
	SheepStateKeyName = "State";
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
	BlackboardComp->SetValueAsVector(TargetLocationKeyName, location);
	BlackboardComp->SetValueAsEnum(SheepStateKeyName, static_cast<uint8>(ESheepStates::MoveTo));
}


void AAISheepController::Select()
{
	auto sheep = Cast<ASheepCharacter>(GetPawn());
	if (sheep)
	{
		m_bIsSelected = true;
		sheep->SelectionSprite->SetVisibility(true);
		BlackboardComp->SetValueAsEnum(SheepStateKeyName, 1);
	}
}

void AAISheepController::Deselect()
{
	auto sheep = Cast<ASheepCharacter>(GetPawn());
	if (sheep)
	{
		m_bIsSelected = false;
		sheep->SelectionSprite->SetVisibility(false);
		BlackboardComp->SetValueAsEnum(SheepStateKeyName, 0);
	}
}
