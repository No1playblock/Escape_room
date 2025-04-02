// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointerWidget.generated.h"

/**
 * 
 */
UCLASS()
class ESCAPE_ROOM_API UPointerWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void StartSubTitle();

	void HasKeySubTitle();

private:

	int Index;

	void DisplaySubTitle();

	void DisplayBlankSubTitle();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	UPROPERTY(EditAnywhere, Category = "Subtitles")
	UDataTable* SubtitleDataTable;

	FTimerHandle TimerHandle;

	FString SoundPathFront = "/Game/Narration/Narration";
	FString SoundPathBack = ".Narration";
};
