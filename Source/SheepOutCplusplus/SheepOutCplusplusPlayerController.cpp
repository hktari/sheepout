// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SheepOutCplusplusPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SheepOutCplusplusCharacter.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "SheepCharacter.h"
#include "SheepOutCplusplus.h"
#include "AIController.h"
#include "AI/AISheepController.h"

ASheepOutCplusplusPlayerController::ASheepOutCplusplusPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASheepOutCplusplusPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ASheepOutCplusplusPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASheepOutCplusplusPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASheepOutCplusplusPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASheepOutCplusplusPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASheepOutCplusplusPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ASheepOutCplusplusPlayerController::OnResetVR);
}

void ASheepOutCplusplusPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASheepOutCplusplusPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ASheepOutCplusplusCharacter* MyPawn = Cast<ASheepOutCplusplusCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		
		if (Hit.bBlockingHit)
		{
			// Move to the location
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ASheepOutCplusplusPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		if(TrySelectCommandable(HitResult))
		{
			return;
		}
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASheepOutCplusplusPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	ACharacter* const MyPawn = Cast<ACharacter>(GetPawn());
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ASheepOutCplusplusPlayerController::OnSetDestinationPressed()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (selectedMinion)
		{
			// TODO: is interactable object hit ?
			// if yes: start action
			// if no: move to position
			selectedMinion->MoveToLocation(Hit.Location);
			DeselectCommandable();
		}
		else if (TrySelectCommandable(Hit))
		{
			// We have selected a minion successfully
			return;
		} 
		else
		{
			bMoveToMouseCursor = true;
		}
	}
}

void ASheepOutCplusplusPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

bool ASheepOutCplusplusPlayerController::TrySelectCommandable(FHitResult hit)
{
	ASheepCharacter* sheepActor = nullptr;

	if (hit.Actor.IsValid())
	{
		sheepActor = Cast<ASheepCharacter>(hit.Actor.Get());
	}

	// If commandable actor hit, select it
	if (sheepActor)
	{
		auto sheepController = Cast<AAISheepController>(sheepActor->GetController());
		if (sheepController)
		{
			sheepController->Select();
			selectedMinion = sheepController;
			return true;
		}
		// TODO: open GUI
		// TODO: call command with chosen param
		//commandableActor->Command(0);
	}
	return false;
}

void ASheepOutCplusplusPlayerController::DeselectCommandable()
{
	if (selectedMinion == nullptr)
	{
		UE_LOG(LogSheepError, Error, TEXT("Can't deselect null!"));
		return;
	}
	selectedMinion->Deselect();
	selectedMinion = nullptr;
}