// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICommandable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICommandable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SHEEPOUTCPLUSPLUS_API IICommandable
{
	GENERATED_BODY()

public:
	virtual bool StartInteraction(class IInteractable& interactable) = 0;
	virtual bool IsInteracting() = 0;
};
