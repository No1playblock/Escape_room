// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/ZombieCharacter.h"

AZombie_AIController::AZombie_AIController()
{
	//UE_LOG(LogTemp, Log, TEXT("constructor"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	check(BlackboardComp);

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComp);

}


void AZombie_AIController::OnPossess(APawn* InPawn)		//pawn's name : FPBossCharacter
{
	Super::OnPossess(InPawn);

	AZombieCharacter* possessedPawn = Cast<AZombieCharacter>(InPawn);


	if (InPawn != nullptr)
	{

		BlackboardComp->InitializeBlackboard(*(possessedPawn->GetBehaviorTree()->BlackboardAsset));
		
		BehaviorTreeComp->StartTree(*(possessedPawn->GetBehaviorTree()));
		

	}

}
