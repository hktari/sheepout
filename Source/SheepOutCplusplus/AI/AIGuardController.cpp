// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGuardController.h"
#include "AI/GuardCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AAIGuardController::AAIGuardController(const FObjectInitializer & objectInitializer)
{
	m_pBehaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	m_pBlackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AAIGuardController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	
	AGuardCharacter* guard = Cast<AGuardCharacter>(InPawn);
	if (guard && guard->GetBehaviorTree())
	{
		if (auto behaviorTree = guard->GetBehaviorTree()) 
		{
			if (behaviorTree->BlackboardAsset)
			{
				m_pBlackboardComp->InitializeBlackboard(*behaviorTree->BlackboardAsset);
			}
			m_pBehaviorComp->StartTree(*behaviorTree);
		}
	}
}

void AAIGuardController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	m_pBehaviorComp->StopTree();
}

EGuardStates AAIGuardController::GetState()
{
	if (m_pBlackboardComp)
	{
		return static_cast<EGuardStates>(m_pBlackboardComp->GetValueAsEnum(StateKeyName));
	}
	return EGuardStates::Idle;
}
