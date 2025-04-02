// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnStartButtonClicked();

    void UpdateOpacity();

    UFUNCTION()
    void PlayFirstGunChromakeyMedia();

    void PlaySecondGunChromakeyMedia();

    void DelayedLevelLoad();
    
    void PlayFirstGunSound();
    void PlaySecondGunSound();

   
    //컴포넌트

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> StartBtn;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UButton> RunAwayBtn;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> OpacityBackGround;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> FirstGun;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UImage> SecondGun;

    //매개변수
    UPROPERTY(EditAnywhere)
    TObjectPtr<class UMediaPlayer> MPBackGround;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class UMediaPlayer> MPFirstGunChromakey;

    UPROPERTY(EditAnywhere)
    TObjectPtr<class UMediaPlayer> MPSeconGunChromakey;

    UPROPERTY(EditAnywhere, Category = "Media")
    TObjectPtr<class UMediaSource> TitleBackground;

    UPROPERTY(EditAnywhere, Category = "Media")
    TObjectPtr<class UMediaSource> GunChromakey;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> StartBtnSound;

    UPROPERTY(EditAnywhere, Category = "Sound")
    TObjectPtr<class USoundBase> GunShotSound;
    
    FName LevelName = "FirstPersonMap";

    float Opacity = 0.0f;

    float InterpSpeed = 0.33f;

    float FadeUpdateRate = 0.01f; 

    FTimerHandle LevelLoadTimerHandle;
    FTimerHandle SoundTimerHandle;
    FTimerHandle FunctionTimerHandle;
    FTimerHandle OpacityTimerHandle;
};
