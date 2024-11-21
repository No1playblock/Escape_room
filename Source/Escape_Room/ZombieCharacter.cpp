// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombie_AIController.h"
#include "Escape_RoomCharacter.h"
#include "CrossHairWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	IsAttacked = false;
	isDead = false;
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

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AZombieCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	

	//UE_LOG(LogTemp, Warning, TEXT("Hit"));
	if (Other->ActorHasTag("Arrow")&&!isDead)
	{
		SetHP(-50);
		
		TArray<AActor*> zombies;
		
		if (!IsAttacked) 
		{
			UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Zombie"), zombies);
			for (AActor* zombie : zombies)
			{
				//Cast<AZombie_AIController>(Cast<AZombieCharacter>(zombie)->GetController())->GetBlackboard()->SetValueAsBool("IsAttacked", true);
				Cast<AZombieCharacter>(zombie)->IsAttacked = true;
			}
		}
		
	
		
		if (isDead)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ScreamSound, GetActorLocation());
			AEscape_RoomCharacter* player =Cast<AEscape_RoomCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			player->KilZombie();
			GetWorld()->GetTimerManager().ClearTimer(GrowlingHandle);
			Other->Destroy();
		}
			
	}
}



// Called to bind functionality to input
void AZombieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
int AZombieCharacter::GetHP()
{
	return HP;
}
void AZombieCharacter::SetHP(int Num)
{
	HP += Num;

	if (HP == 0)
	{
		isDead = true;
		
	}
		
}
bool AZombieCharacter::GetisDead()
{
	return isDead;
}

