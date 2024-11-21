// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Zombie_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API AZombie_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AZombie_AIController();
	virtual void OnPossess(APawn* InPawn) override;

	UBlackboardComponent* GetBlackboard();


public:
	UPROPERTY(BlueprintReadWrite, Category = Behavor)
	class UBlackboardComponent* BlackboardComp;

protected:
	UPROPERTY(BlueprintReadWrite, Category = Behavior)
	class UBehaviorTreeComponent* BehaviorTreeComp;

};
