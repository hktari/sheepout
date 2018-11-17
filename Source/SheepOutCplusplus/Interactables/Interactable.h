// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IICommandable;

/**
 * 
 */
class SHEEPOUTCPLUSPLUS_API IInteractable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	DECLARE_EVENT_TwoParams(IInteractable, FInteractionStartedEvent, IInteractable&, IICommandable&)
	FInteractionStartedEvent& OnInteractionStarted() { return InteractionStartedEvent; }
	
	DECLARE_EVENT_TwoParams(IInteractable, FInteractionStoppedEvent, IInteractable&, IICommandable&)
	FInteractionStoppedEvent& OnInteractionStopped() { return InteractionStoppedEvent; }

	virtual bool StartInteraction(IICommandable& commandable);
	virtual void StopInteraction(IICommandable& commandable);

	/*UFUNCTION(BlueprintImplementableEvent)
		void InteractionStarted(IICommandable* commandable);
	UFUNCTION(BlueprintImplementableEvent)
		void InteractionStopped(IICommandable* commandable);
*/
private:
	FInteractionStartedEvent InteractionStartedEvent;
	FInteractionStoppedEvent InteractionStoppedEvent;
};
