// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ICommandable.h"
#include "AISheepController.generated.h"

class UBehaviorTreeComponent;

UENUM(BlueprintType)
enum class ESheepStates : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Selected UMETA(DisplayName = "Selected"),
	MoveTo UMETA(DisplayName = "MoveTo"),
	Interacting UMETA(DisplayName = "Interacting"),
	Scared UMETA(DisplayName = "Scared")
};
/**
 * 
 */
UCLASS()
class SHEEPOUTCPLUSPLUS_API AAISheepController : public AAIController, public IICommandable
{
	GENERATED_BODY()

	AAISheepController(const class FObjectInitializer& ObjectInitializer);

	/* Called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	UBehaviorTreeComponent* BehaviorComp;

	UBlackboardComponent* BlackboardComp;

public:
	virtual bool StartInteraction(class IInteractable& interactable) override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetLocationKeyName;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName SheepStateKeyName;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetInteractableKeyName;

	void MoveToLocation(FVector& location);
	void Scare(AActor& guard);

	UBehaviorTreeComponent* GetBehaviorComp() { return BehaviorComp; }
	UBlackboardComponent* GetBlackbardComp() { return BlackboardComp; }

	void Select();
	void Deselect(bool switchToIdle = true);

	UFUNCTION(BlueprintCallable)
	ESheepStates GetSheepState();

	bool CanBeSelected();
	bool GetIsSelected() { return m_bIsSelected; }
private:
	bool m_bIsSelected;
};
