// Fill out your copyright notice in the Description page of Project Settings.


#include "PointerWidget.h"
#include "Utility/SoundUtility.h"
#include "GameData/SubTitleStructure.h"
#include "Components/TextBlock.h"
void UPointerWidget::HasKeySubTitle()
{
	Index = 2;
	DisplaySubTitle();

}

void UPointerWidget::DisplaySubTitle()
{

	FString SoundPath = SoundPathFront + FString::FromInt(Index) +
		SoundPathBack + FString::FromInt(Index);
	USoundUtility::PlaySound2D(this, SoundPath);

	static const FString ContextString(TEXT("Subtitle Context"));
	FName RowName = FName(*FString::FromInt(Index));
	FSubTitleStructure* SubtitleData = SubtitleDataTable->FindRow<FSubTitleStructure>(RowName, ContextString);

	if (SubtitleData)
	{
		if (TextBlock)
		{
			TextBlock->SetText(FText::FromString(SubtitleData->Text));
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPointerWidget::DisplayBlankSubTitle, SubtitleData->Time, false);
		}
	}

}
void UPointerWidget::DisplayBlankSubTitle()
{
	if (TextBlock)
	{
		TextBlock->SetText(FText::FromString(""));
	}
}
void UPointerWidget::StartSubTitle()
{
	Index = 1;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPointerWidget::DisplaySubTitle, 5.0f, false);
}
