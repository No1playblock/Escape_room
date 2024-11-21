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
    // AI Controller 가져오기
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

    // Blackboard 가져오기
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    // TargetToFollow 위치 가져오기
    AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TargetToFollowKey.SelectedKeyName));
    if (!TargetActor)
    {
        return EBTNodeResult::Failed;
    }

    FVector Origin = TargetActor->GetActorLocation();

    // 랜덤 위치 생성
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

    // Blackboard에 위치 저장
    BlackboardComp->SetValueAsVector(RandomLocationKey.SelectedKeyName, RandomLocation.Location);

    return EBTNodeResult::Succeeded;
}