// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "CrossHairWidget.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSubTitleS : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Time;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPlayingSound;*/
};
UCLASS()
class ESCAPE_ROOM_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()





public:

	UFUNCTION(BlueprintCallable)
	void StartSubtitles(int StartIndex, int Finishindex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	float TargetOpacity;

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle1();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle1_2();

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	void SubTitle2();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle3();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle4();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle5();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle6();

	UFUNCTION(BlueprintCallable, Category = "Custom")
	void SubTitle7();
	UFUNCTION(BlueprintCallable, Category = "Custom")
	void LastLoop();

	void Map3warp();

	UFUNCTION(BlueprintCallable)
	void StartOpacityUpdate();

	UFUNCTION(BlueprintCallable)
	void StartLightingUpdate();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundBase* warpsound;

private:
	int Index = 0;
	FString SoundPathFront = "/Game/Narration/Narration";
	FString SoundPathBack = ".Narration";

protected:
	virtual void NativeConstruct() override;

private:
	void DisplayNextSubtitle();

	void Teleport();

	void RedLightSetIntensity();

	void UpdateText(FString NewText);
	void PlaySubtitleSound();
	void SetSubtitleDelay(float DelayTime);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	class UImage* OpacityBackGround;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles", meta = (AllowPrivateAccess = "true"))
	USoundBase* SubtitleSound;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subtitles", meta = (AllowPrivateAccess = "true"))
	UDataTable* SubtitleDataTable;

	FTimerHandle SubtitleTimerHandle;
	FTimerHandle WarpTimerHandle;


	int32 CurrentIndex;
	
	int32 EndIndex;

	TArray<AActor*> YellowLight;

	TArray<AActor*> BlueLight;

	TArray<AActor*> RedLight;

	FLinearColor RedLightColor;

private:
	// Variables for opacity and light adjustment
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	float CurrentOpacity;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	bool bTeleportFinish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	bool bLightFinish;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	float LightOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	bool bIsLightChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	float BlueLightOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	float LightR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	float LightG;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting", meta = (AllowPrivateAccess = "true"))
	float LightB;

	// Function to update opacity and lighting
	UFUNCTION()
	void UpdateOpacity();



	void UpdateLighting();

	

	FVector TeleportLocation;
	FRotator TeleportRotation;

	// Timer handles
	FTimerHandle OpacityTimerHandle;
	FTimerHandle LightingTimerHandle;
	FTimerHandle TeleportTimerHandle;
	// Function to start and stop timers
	
};
