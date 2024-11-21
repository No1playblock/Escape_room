// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bed.generated.h"

UCLASS()
class ESCAPE_ROOM_API ABed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
	void OpenBed();
};
