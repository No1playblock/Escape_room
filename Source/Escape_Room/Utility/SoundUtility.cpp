// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundUtility.h"

USoundBase* USoundUtility::LoadSoundFromPath(const FString& Path)
{
	return Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr, *Path));
}

void USoundUtility::PlaySoundAtLocation(UObject* WorldContextObject, const FString& SoundPath, FVector Location)
{
    USoundBase* Sound = LoadSoundFromPath(SoundPath);
    if (Sound)
    {
        UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location);
    }
}

void USoundUtility::PlaySound2D(UObject* WorldContextObject, const FString& SoundPath)
{
    USoundBase* Sound = LoadSoundFromPath(SoundPath);
    if (Sound)
    {
        UGameplayStatics::PlaySound2D(WorldContextObject, Sound);
    }
}