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
	
	FORCEINLINE UBlackboardComponent* GetBlackboard() { return BlackboardComp; }
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
private:

	AZombie_AIController();

	TObjectPtr<class UBlackboardComponent> BlackboardComp;

	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComp;
	
	virtual void OnPossess(APawn* InPawn) override;

};
