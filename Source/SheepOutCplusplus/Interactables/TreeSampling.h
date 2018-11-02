// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TreeSampling.generated.h"

UCLASS()
class SHEEPOUTCPLUSPLUS_API ATreeSampling : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		class UPaperFlipbookComponent* RenderComponent;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* CollisionComponent;
	// Sets default values for this actor's properties
	ATreeSampling();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StopInteraction(class IICommandable& commandable) override;
	virtual bool StartInteraction(class IICommandable& commandable) override;

};
