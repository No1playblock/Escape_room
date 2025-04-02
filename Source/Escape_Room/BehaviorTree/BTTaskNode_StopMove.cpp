// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTTaskNode_StopMove.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/ZombieCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
EBTNodeResult::Type UBTTaskNode_StopMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    // 컨트롤된 Pawn 가져오기
    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ControlledPawn);
    if (!Zombie)
    {
        return EBTNodeResult::Failed;
    }
    Zombie->GetCharacterMovement()->StopMovementImmediately();


	return EBTNodeResult::Succeeded;
}

UBTTaskNode_StopMove::UBTTaskNode_StopMove()
{
	NodeName = TEXT("StopMove");
}