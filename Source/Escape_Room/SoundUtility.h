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
    UFUNCTION(BlueprintCallable, Category = "Sound")
    static USoundBase* LoadSoundFromPath(const FString& Path)
    {
        return Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr, *Path));
    }

    // 사운드를 특정 경로에서 재생하는 함수
    UFUNCTION(BlueprintCallable, Category = "Sound")
    static void PlaySoundAtLocation(UObject* WorldContextObject, 
                                        const FString& SoundPath, FVector Location)
    {
        USoundBase* Sound = LoadSoundFromPath(SoundPath);
        if (Sound)
        {
            UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location);
        }
    }
    
    UFUNCTION(BlueprintCallable, Category = "Sound")
    static void PlaySound2D(UObject* WorldContextObject, const FString& SoundPath)
    {
        USoundBase* Sound = LoadSoundFromPath(SoundPath);
        if (Sound)
        {
            UGameplayStatics::PlaySound2D(WorldContextObject, Sound);
        }
    }
};
