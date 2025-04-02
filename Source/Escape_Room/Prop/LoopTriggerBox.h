// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoopTriggerBox.generated.h"

UCLASS()
class ESCAPE_ROOM_API ALoopTriggerBox : public AActor
{
	GENERATED_BODY()
	
private:
	ALoopTriggerBox();

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrossHairWidget;

	TObjectPtr<UUserWidget> WidgetInstance;

	int LoopCount=0;
};
