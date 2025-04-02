// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Controller/Zombie_AIController.h"
#include "Escape_RoomCharacter.h"
#include "UI/CrossHairWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsAttacked = false;
	bIsDead = false;
	HP = 50;
}

void AZombieCharacter::GrowlingZombie()
{
	
	GetWorld()->GetTimerManager().SetTimer(GrowlingHandle, this, &AZombieCharacter::PlaySoundCue, FMath::RandRange(4.0f, 5.0f) , true, 0.0f);
}

void AZombieCharacter::PlaySoundCue()
{
	if (GrowlingSoundCue)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GrowlingSoundCue, GetActorLocation());
	}
}
void AZombieCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	if (Other->ActorHasTag("Arrow")&&!bIsDead)
	{
		SetHP(-50);
		
		TArray<AActor*> zombies;
		
		if (!bIsAttacked) 
		{
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Zombie"), zombies);
			for (AActor* zombie : zombies)
			{
				Cast<AZombieCharacter>(zombie)->bIsAttacked = true;
			}
		}
		
		if (bIsDead)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ScreamSound, GetActorLocation());
			AEscape_RoomCharacter* player =Cast<AEscape_RoomCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			player->KilZombie();
			GetWorld()->GetTimerManager().ClearTimer(GrowlingHandle);
			Other->Destroy();
		}
			
	}
}

void AZombieCharacter::SetHP(int Num)
{
	HP += Num;

	if (HP == 0)
	{
		bIsDead = true;
		
	}
		
}

