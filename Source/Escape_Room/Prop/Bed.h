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

	UFUNCTION(BlueprintImplementableEvent, Category = "Custom")
	void OpenBed();


private:	
	// Sets default values for this actor's properties
	ABed();

};
