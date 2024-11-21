// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Sound/SoundCue.h>
#include "BehaviorTree/BehaviorTreeTypes.h"

#include "ZombieCharacter.generated.h"


UCLASS()
class ESCAPE_ROOM_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieCharacter();

	UFUNCTION(BlueprintCallable)
	void GrowlingZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	void PlaySoundCue();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Pawn)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* ScreamSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundCue* GrowlingSoundCue;

	UFUNCTION(BlueprintCallable, Category = "Info")
	int GetHP();

	UFUNCTION(BlueprintCallable, Category = "Info")
	void SetHP(int Damage);

	UFUNCTION(BlueprintCallable, Category = "Info")
	bool GetisDead();



private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsAttacked;

	int HP;

	FTimerHandle GrowlingHandle;;

	bool isDead;
	
};
