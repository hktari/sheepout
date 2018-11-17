// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
UInteractable::UInteractable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }
//
bool IInteractable::StartInteraction(IICommandable& commandable)
{
	//InteractionStarted(&commandable);
	InteractionStartedEvent.Broadcast(*this, commandable);
	return true;
}

void IInteractable::StopInteraction(IICommandable& commandable)
{
	//InteractionStopped(&commandable);
	InteractionStoppedEvent.Broadcast(*this, commandable);
}