// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTDecorator_IsDead.h"
#include "AIController.h"
#include "Character/ZombieCharacter.h"

UBTDecorator_IsDead::UBTDecorator_IsDead()
{
    NodeName = TEXT("BTD_IsDead");
}

bool UBTDecorator_IsDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return false;
    }

    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return false;
    }

    AZombieCharacter* Zombie = Cast<AZombieCharacter>(ControlledPawn);
    if (!Zombie)
    {
        return false;
    }

    return Zombie->GetIsDead();

}

