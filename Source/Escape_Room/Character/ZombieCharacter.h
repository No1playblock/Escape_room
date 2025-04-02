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
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetIsDead() { return bIsDead; }

	FORCEINLINE bool GetIsAttacked() { return bIsAttacked; }

	void GrowlingZombie();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }

private:

	AZombieCharacter();

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void SetHP(int Damage);

	void PlaySoundCue();

	UPROPERTY(EditAnywhere, Category = "BehaviorTree")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> ScreamSound;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundCue> GrowlingSoundCue;

	bool bIsAttacked;

	int HP;

	FTimerHandle GrowlingHandle;;

	bool bIsDead;
	
};
