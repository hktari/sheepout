// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGuardController.h"
#include "AI/GuardCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "SheepCharacter.h"
#include "AI/AISheepController.h"

AAIGuardController::AAIGuardController(const FObjectInitializer & objectInitializer) 
	: m_wpSheepControllerCollection(TArray<TWeakObjectPtr<AAISheepController>>())
	, m_dtSheepSeenTimestampCollection(TArray<FDateTime>())
{
	PrimaryActorTick.bCanEverTick = true;
	
	m_pBehaviorComp = objectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	m_pBlackboardComp = objectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
	
	StateKeyName = "State";
	TargetKeyName = "Target";
	HomLocationKeyName = "HomeLocation";	

	SheepForgetTime = FTimespan(0, 0, 3);
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

				m_pBlackboardComp->SetValueAsVector(HomLocationKeyName, InPawn->GetActorLocation());
			}
			
			/* This is the earliest moment we can bind our delegates to the component */
			if(auto pawnSensingComp = guard->GetPawnSensingComp())
			{
				pawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuardController::OnSeePawn);
				pawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuardController::OnHearNoise);
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


void AAIGuardController::OnSeePawn(APawn* Pawn)
{
	/* Keep track of the time the player was last sensed in order to clear the target */
	/*LastSeenTime = GetWorld()->GetTimeSeconds();
	bSensedTarget = true;*/

	if (ASheepCharacter* sheep = Cast<ASheepCharacter>(Pawn))
	{
		if (auto sheepController = Cast<AAISheepController>(sheep->GetController()))
		{
			int32 idx = m_wpSheepControllerCollection.IndexOfByKey(sheep->GetController());
			if (idx == INDEX_NONE)
			{
				m_wpSheepControllerCollection.Add(sheepController);
				m_dtSheepSeenTimestampCollection.Add(FDateTime::UtcNow());
				UE_LOG(LogTemp, Warning, TEXT("I see you %s"), *sheepController->GetName());
			}
			else 
			{
				// Update last seen timestamp
				m_dtSheepSeenTimestampCollection[idx] = FDateTime::UtcNow();
			}
		}
	}
}


void AAIGuardController::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	/*if (!IsAlive())
	{
		return;
	}

	if (!bSensedTarget)
	{
		BroadcastUpdateAudioLoop(true);
	}

	bSensedTarget = true;
	LastHeardTime = GetWorld()->GetTimeSeconds();

	ASZombieAIController* AIController = Cast<ASZombieAIController>(GetController());
	if (AIController)
	{
		AIController->SetTargetEnemy(PawnInstigator);
	}*/
}

void AAIGuardController::Tick(float DeltaTime)
{
	auto state = static_cast<EGuardStates>(m_pBlackboardComp->GetValueAsEnum(StateKeyName));
	if (state != EGuardStates::Herding)
	{
		auto nowTimestamp = FDateTime::UtcNow();
		for (auto it = m_dtSheepSeenTimestampCollection.CreateIterator(); it; ++it)
		{
			if (nowTimestamp - *it >= SheepForgetTime)
			{
				int32 idx = it.GetIndex();
				m_dtSheepSeenTimestampCollection.RemoveAt(idx);
				m_wpSheepControllerCollection.RemoveAt(idx);
				it--;
			}
		}

		for (auto sheepControllerPtr : m_wpSheepControllerCollection)
		{
			if (sheepControllerPtr.IsValid())
			{
				auto sheepController = sheepControllerPtr.Get();
				if (sheepController->IsInteracting())
				{
					m_pBlackboardComp->SetValueAsObject(TargetKeyName, sheepController->GetPawn());
					m_pBlackboardComp->SetValueAsEnum(StateKeyName, static_cast<uint8>(EGuardStates::Herding));
				}
			}
		}
	}
}
