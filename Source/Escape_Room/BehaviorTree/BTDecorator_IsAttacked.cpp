// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BTDecorator_IsAttacked.h"
#include "AIController.h"
#include "Character/ZombieCharacter.h"
UBTDecorator_IsAttacked::UBTDecorator_IsAttacked()
{
	NodeName = TEXT("BTD_IsAttacked");
}

bool UBTDecorator_IsAttacked::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
	
    return Zombie->GetIsAttacked();

}