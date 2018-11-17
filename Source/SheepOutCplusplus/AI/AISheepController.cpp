// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/AISheepController.h"
#include "SheepCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "PaperSpriteComponent.h"
#include "Interactables/Interactable.h"
#include "ICommandable.h"
#include "SheepOutCplusplus.h"

AAISheepController::AAISheepController(const FObjectInitializer & objectInitializer) 
	: Super(objectInitializer)
{
	BehaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	TargetLocationKeyName = "TargetLocation";
	SheepStateKeyName = "State";
	TargetInteractableKeyName = "TargetInteractable";
	CooldownKeyName = "Cooldown";
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
			BlackboardComp->SetValueAsFloat(CooldownKeyName, Cooldown);
			BlackboardComp->SetValueAsObject("SelfActor", sheep);
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

bool AAISheepController::StartInteraction(IInteractable& interactable)
{
	if (GetSheepState() == ESheepStates::Interacting)
	{
		return false;
	}
	BlackboardComp->SetValueAsObject(TargetInteractableKeyName, Cast<UObject>(&interactable));
	SetSheepState(ESheepStates::StartingInteraction);
	return true;
}

bool AAISheepController::IsInteracting()
{
	return GetSheepState() == ESheepStates::Interacting;
}

void AAISheepController::MoveToLocation(FVector & location)
{
	UE_LOG(LogTemp, Warning, TEXT("Moving"));
	BlackboardComp->SetValueAsVector(TargetLocationKeyName, location); 
	SetSheepState(ESheepStates::MoveTo);
}

void AAISheepController::Scare(AActor & guard)
{
	SetSheepState(ESheepStates::Scared);
}


void AAISheepController::Select()
{
	auto sheep = Cast<ASheepCharacter>(GetPawn());
	if (sheep)
	{
		m_bIsSelected = true;
		sheep->SelectionSprite->SetVisibility(true);
		SetSheepState(ESheepStates::Selected);
	}
}

void AAISheepController::Deselect(bool switchToIdle)
{
	auto sheep = Cast<ASheepCharacter>(GetPawn());
	if (sheep)
	{
		m_bIsSelected = false;
		sheep->SelectionSprite->SetVisibility(false);
		if(switchToIdle)
			SetSheepState(ESheepStates::Idle);
	}
}

ESheepStates AAISheepController::GetSheepState()
{
	if (BlackboardComp && BlackboardComp->HasBeenInitialized())
	{
		return static_cast<ESheepStates>(BlackboardComp->GetValueAsEnum(SheepStateKeyName));
	}
	return ESheepStates::Idle;
}

void AAISheepController::SetSheepState(ESheepStates state)
{
	if (!BlackboardComp || !BlackboardComp->HasBeenInitialized())
	{
		UE_LOG(LogSheepError, Fatal, TEXT("Blackboard not initialized"));
	}
	BlackboardComp->SetValueAsEnum(SheepStateKeyName, static_cast<uint8>(state));
}

bool AAISheepController::CanBeSelected()
{
	if (!BlackboardComp)
	{
		UE_LOG(LogSheepError, Warning, TEXT("No blackboard component."));
		return false;
	}
	ESheepStates sheepState = static_cast<ESheepStates>(BlackboardComp->GetValueAsEnum(SheepStateKeyName));
	return sheepState != ESheepStates::Scared;
}
