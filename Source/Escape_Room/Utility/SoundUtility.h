// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "UObject/NoExportTypes.h"
#include "SoundUtility.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API USoundUtility : public UObject
{
	GENERATED_BODY()

public:

    UFUNCTION()
    static void PlaySoundAtLocation(UObject* WorldContextObject, const FString& SoundPath, FVector Location);
    
    UFUNCTION()
    static void PlaySound2D(UObject* WorldContextObject, const FString& SoundPath);

private:
    UFUNCTION()
    static USoundBase* LoadSoundFromPath(const FString& Path);
};
