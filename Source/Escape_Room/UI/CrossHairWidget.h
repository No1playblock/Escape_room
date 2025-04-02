// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CrossHairWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void ShowSubtitleAfterBowAcquired();

	void ShowSubTitleAfterZombieKill();
	
	void ShowSubTitleAfterSunFlowerHit();

	void ShowSubTitleShootSunFlower();

	void ShowSubTitleSecondLoop();

	void ShowSubTitleThirdLoop();

	void ShowSubTitleFourthLoop();

	void BeforeMap3Warp();

private:

	virtual void NativeConstruct() override;

	void StartSubtitles(int StartIndex, int Finishindex);

	void ShowSubTitleFirstLoop();

	void AfterMap3Warp();

	void StartOpacityUpdate();

	void StartLightingUpdate();

	void DisplayNextSubtitle();

	void Teleport();

	void RedLightSetIntensity();

	void UpdateText(FString NewText);
	void PlaySubtitleSound();
	void SetSubtitleDelay(float DelayTime);

	void UpdateOpacity();

	void UpdateLighting();

	//ÄÄÆ÷³ÍÆ®
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UImage> OpacityBackGround;


	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Warpsound;

	int Index = 0;
	FString SoundPathFront = "/Game/Narration/Narration";
	FString SoundPathBack = ".Narration";


	UPROPERTY(EditAnywhere, Category = "Subtitles")
	UDataTable* SubtitleDataTable;

	FTimerHandle SubtitleTimerHandle;
	FTimerHandle WarpTimerHandle;

	int32 CurrentIndex;
	
	int32 EndIndex;

	TArray<AActor*> YellowLight;

	TArray<AActor*> BlueLight;

	TArray<AActor*> RedLight;

	FLinearColor RedLightColor;

	float CurrentOpacity;

	bool bTeleportFinish;

	bool bLightFinish;

	float LightOpacity;

	bool bIsLightChange;

	float TargetOpacity;
	float BlueLightOpacity;


	float LightR;

	float LightG;

	float LightB;


	FVector TeleportLocation;
	FRotator TeleportRotation;

	// Timer handles
	FTimerHandle OpacityTimerHandle;
	FTimerHandle LightingTimerHandle;
	FTimerHandle TeleportTimerHandle;
	// Function to start and stop timers
	
};
