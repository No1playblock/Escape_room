// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_RunAway.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"


UBTTaskNode_RunAway::UBTTaskNode_RunAway()
{
    NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTaskNode_RunAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // AI Controller ��������
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    // ��Ʈ�ѵ� Pawn ��������
    APawn* ControlledPawn = AIController->GetPawn();
    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    // Blackboard ��������
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // TargetToFollow ��ġ ��������
    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetToFollowKey.SelectedKeyName));
    if (!TargetActor)
    {
        return EBTNodeResult::Failed;
    }

    FVector Origin = TargetActor->GetActorLocation();

    // ���� ��ġ ����
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation RandomLocation;
    bool bFoundLocation = false;
    const float MaxAttempts = 100;
    for (int32 Attempt = 0; Attempt < MaxAttempts; Attempt++)
    {
        bFoundLocation = NavSys->GetRandomReachablePointInRadius(Origin, SearchRadius, RandomLocation);
        if (bFoundLocation)
        {
            float Distance = FVector::Dist2D(RandomLocation.Location, Origin);
            if (Distance >= MinAcceptanceRadius)
            {
                break;
            }
        }
    }

    if (!bFoundLocation)
    {
        return EBTNodeResult::Failed;
    }

    // Blackboard�� ��ġ ����
    BlackboardComp->SetValueAsVector(RandomLocationKey.SelectedKeyName, RandomLocation.Location);

    return EBTNodeResult::Succeeded;
}