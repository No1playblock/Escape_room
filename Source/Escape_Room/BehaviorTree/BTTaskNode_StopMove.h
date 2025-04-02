// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_StopMove.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API UBTTaskNode_StopMove : public UBTTaskNode
{
	GENERATED_BODY()

private:

	UBTTaskNode_StopMove();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
