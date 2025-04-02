// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_RunAway.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API UBTTaskNode_RunAway : public UBTTaskNode
{
	GENERATED_BODY()
	

private:
    
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UBTTaskNode_RunAway();

    // Ž���ݰ� 
    UPROPERTY(EditAnywhere, Category = "Search")
    float SearchRadius = 1000.0f;

    // �ּ� �Ÿ� 
    UPROPERTY(EditAnywhere, Category = "Validation")
    float MinAcceptanceRadius = 200.0f;


    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector RandomLocationKey;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FBlackboardKeySelector TargetToFollowKey;
};
