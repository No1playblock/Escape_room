// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SunFlower.generated.h"

UCLASS()
class ESCAPE_ROOM_API ASunFlower : public AActor
{
	GENERATED_BODY()
	
private:

	ASunFlower();
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
	void KilledSunFlower();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Box;


	TObjectPtr<UUserWidget> WidgetInstance;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> CrossHairWidget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ScreamSound;

	FTimerHandle FallTimerHandle;

};
