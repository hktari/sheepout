// Fill out your copyright notice in the Description page of Project Settings.

#include "TreeSampling.h"
#include "ICommandable.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "Classes/Components/BoxComponent.h"

// Sets default values
ATreeSampling::ATreeSampling()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	RenderComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("RenderComponent");
	RenderComponent->AttachTo(CollisionComponent);
	SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ATreeSampling::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreeSampling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATreeSampling::StopInteraction(IICommandable& commandable)
{
}

bool ATreeSampling::StartInteraction(IICommandable& commandable)
{
	// TODO: visual feedback

	return IInteractable::StartInteraction(commandable);
}

