// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Utility/SoundUtility.h"
#include "GameData/SubTitleStructure.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/LightComponent.h"
#include "Character/Escape_RoomCharacter.h"
#include "Engine/PointLight.h" 
#include "Character/ZombieCharacter.h"

void UCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Light")), YellowLight);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("BlueLight")), BlueLight);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("RedLight")), RedLight);

	// Initialize default values
	CurrentOpacity = 0.0f;
	TargetOpacity = 0.0f;
	bTeleportFinish = false;
	bLightFinish = false;
	LightOpacity = 0.641298f;
	bIsLightChange = false;
	BlueLightOpacity = 0.0f;
	LightR = 1.0f;
	LightG = 0.165f;
	LightB = 0.0f;
	

	if (OpacityBackGround->Visibility != ESlateVisibility::Visible)
	{
		OpacityBackGround->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Visible"));
	}
	//CurrentIndex = 0;
}

void UCrossHairWidget::StartSubtitles(int StartIndex, int Finishindex)
{
	CurrentIndex = StartIndex;
	EndIndex = Finishindex;
	DisplayNextSubtitle();
}

void UCrossHairWidget::ShowSubtitleAfterBowAcquired()
{
	StartSubtitles(3, 5);
}
void UCrossHairWidget::ShowSubTitleShootSunFlower()
{
	StartSubtitles(5, 7);
}
void UCrossHairWidget::ShowSubTitleAfterSunFlowerHit()
{
	StartSubtitles(7, 13);
}
void UCrossHairWidget::ShowSubTitleFirstLoop()
{
	StartSubtitles(13, 14);
}
void UCrossHairWidget::ShowSubTitleSecondLoop()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("RedLight")), RedLight);
	for (AActor* Actor : RedLight)
	{
		if (Actor)
		{
			ULightComponent* LightComp = Cast<ALight>(Actor)->GetLightComponent();
			//ULightComponent* LightComp = Actor->FindComponentByClass<ULightComponent>();
			if (LightComp)
			{
				UE_LOG(LogTemp, Warning, TEXT("Intesnsity"));
				LightComp->SetIntensity(0.0f);
			}
		}
	}
	CurrentIndex = 14;
	// 0.5초 후에 SetIntensityAfterDelay 함수를 호출하도록 타이머 설정
	FTimerHandle TimerHandle;
	RedLightColor = FLinearColor(0.270498f, 0.116971f, 0.0, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCrossHairWidget::RedLightSetIntensity, 0.5f, false);


}
void UCrossHairWidget::ShowSubTitleThirdLoop()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("RedLight")), RedLight);
	for (AActor* Actor : RedLight)
	{
		if (Actor)
		{
			ULightComponent* LightComp = Cast<ALight>(Actor)->GetLightComponent();
			//ULightComponent* LightComp = Actor->FindComponentByClass<ULightComponent>();
			if (LightComp)
			{
				UE_LOG(LogTemp, Warning, TEXT("Intesnsity"));
				LightComp->SetIntensity(0.0f);
			}
		}
	}
	CurrentIndex = 15;
	// 0.5초 후에 SetIntensityAfterDelay 함수를 호출하도록 타이머 설정
	FTimerHandle TimerHandle;
	RedLightColor = FLinearColor(0.270498f, 0.152926f, 0.0, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCrossHairWidget::RedLightSetIntensity, 0.5f, false);


}

void UCrossHairWidget::ShowSubTitleFourthLoop()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("RedLight")), RedLight);
	for (AActor* Actor : RedLight)
	{
		if (Actor)
		{
			ULightComponent* LightComp = Cast<ALight>(Actor)->GetLightComponent();
			//ULightComponent* LightComp = Actor->FindComponentByClass<ULightComponent>();
			if (LightComp)
			{
				UE_LOG(LogTemp, Warning, TEXT("Intesnsity"));
				LightComp->SetIntensity(0.0f);
			}
		}
	}
	// 0.5초 후에 SetIntensityAfterDelay 함수를 호출하도록 타이머 설정
	CurrentIndex = 17;
	FTimerHandle TimerHandle;
	RedLightColor = FLinearColor(0.270498f, 0.019382f, 0.0, 1.0f);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCrossHairWidget::RedLightSetIntensity, 0.5f, false);


}
void UCrossHairWidget::ShowSubTitleAfterZombieKill()
{
	StartSubtitles(20, 25);
}
void UCrossHairWidget::DisplayNextSubtitle()
{
	if (CurrentIndex >= EndIndex)
	{
		UpdateText(TEXT(" "));
		GetWorld()->GetTimerManager().ClearTimer(SubtitleTimerHandle);

		if (CurrentIndex == 5)			//subtitle1
		{
			StartLightingUpdate();
		}
		else if (CurrentIndex == 7)		//subtitle1_2
		{

		}
		else if (CurrentIndex == 13)	//subtitle2
		{
			TargetOpacity = 1.0f;
			StartOpacityUpdate();

			TeleportLocation = FVector(-1471.0f, -9460.0f, 592.0f);
			TeleportRotation = FRotator(0.0f, 180.0f, 0.0f);

			GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &UCrossHairWidget::Teleport, 6.0f, false);

			AEscape_RoomCharacter* player = Cast<AEscape_RoomCharacter>(GetOwningPlayerPawn());
			player->SetCurrentMap(ECharacterMapState::Map2);
			player->SetCanShoot(false);
			GetWorld()->GetTimerManager().SetTimer(SubtitleTimerHandle, this, &UCrossHairWidget::ShowSubTitleFirstLoop, 6.0f, false);
		}
		else if (CurrentIndex == 24)	//subtitle7
		{
			AEscape_RoomCharacter* player = Cast<AEscape_RoomCharacter>(GetOwningPlayerPawn());
			player->UnbindAction();
			player->DisableInput(Cast<APlayerController>(player->GetController()));
		}
		else if (CurrentIndex == 5)
		{
			StartLightingUpdate();
		}


		return;
	}
	if (!SubtitleDataTable) return;

	static const FString ContextString(TEXT("Subtitle Context"));
	FName RowName = FName(*FString::FromInt(CurrentIndex));
	FSubTitleStructure* SubtitleData = SubtitleDataTable->FindRow<FSubTitleStructure>(RowName, ContextString);
	if (SubtitleData)
	{
		UpdateText(SubtitleData->Text);


		PlaySubtitleSound();

		CurrentIndex++;
		SetSubtitleDelay(SubtitleData->Time);


		UE_LOG(LogTemp, Warning, TEXT("Subtitle Text: %s, Time: %f"), *SubtitleData->Text, SubtitleData->Time);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Row not found in the data table."));


		GetWorld()->GetTimerManager().ClearTimer(SubtitleTimerHandle);

	}
}
void UCrossHairWidget::Teleport()
{
	APawn* PlayerPawn = GetOwningPlayerPawn();
	if (PlayerPawn)
	{
		
		FRotator NewRotation(0.0f, 0.0f, 0.0f);

		// 플레이어의 위치 설정
		PlayerPawn->SetActorLocationAndRotation(TeleportLocation, NewRotation, false, nullptr, ETeleportType::None);

		// 플레이어 컨트롤러의 회전 설정
		APlayerController* PlayerController = GetOwningPlayer();
		if (PlayerController)
		{
			PlayerController->SetControlRotation(TeleportRotation);
		}
	}
	TargetOpacity = 0.0f;		//0으로 바꿔주면 1로 서서히 오름
	GetWorld()->GetTimerManager().ClearTimer(TeleportTimerHandle);
	return;
	//UpdateOpacity();
}

void UCrossHairWidget::RedLightSetIntensity()
{

	// 불을키고 색을 바꿈
	for (AActor* Actor : RedLight)
	{
		if (Actor)
		{
			ULightComponent* LightComp = Cast<ALight>(Actor)->GetLightComponent();
			//ULightComponent* LightComp = Actor->FindComponentByClass<ULightComponent>();
			if (LightComp)
			{
				UE_LOG(LogTemp, Warning, TEXT("Color"));
				LightComp->SetIntensity(0.002f);
				LightComp->SetLightColor(RedLightColor, true);
			}
		}
	}
	if (CurrentIndex <= 14)
	{
		StartSubtitles(14, 15);
	}
	else if (CurrentIndex <= 15)
	{
		StartSubtitles(15, 17);
	}
	else if (CurrentIndex <= 17)
	{
		StartSubtitles(17, 18);
	}


}


void UCrossHairWidget::UpdateText(FString NewText)
{
	if (TextBlock)
	{
		TextBlock->SetText(FText::FromString(NewText));
	}
}

void UCrossHairWidget::PlaySubtitleSound()
{

	FString SoundPath = SoundPathFront + FString::FromInt(CurrentIndex) +
		SoundPathBack + FString::FromInt(CurrentIndex);
	USoundUtility::PlaySound2D(this, SoundPath);

}

void UCrossHairWidget::SetSubtitleDelay(float DelayTime)
{
	GetWorld()->GetTimerManager().SetTimer(SubtitleTimerHandle, this, &UCrossHairWidget::DisplayNextSubtitle, DelayTime, false);
}

void UCrossHairWidget::StartOpacityUpdate()
{
	TargetOpacity = 1.0f;
	UE_LOG(LogTemp, Warning, TEXT("SSSTargetOpacity : %f "), TargetOpacity);
	// Opacity 업데이트를 위한 타이머 설정 (0.05초 간격으로 UpdateOpacity 호출)
	GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle, this, &UCrossHairWidget::UpdateOpacity, 0.01f, true);
}

void UCrossHairWidget::StartLightingUpdate()
{
	// Lighting 업데이트를 위한 타이머 설정 (0.05초 간격으로 UpdateLighting 호출)
	GetWorld()->GetTimerManager().SetTimer(LightingTimerHandle, this, &UCrossHairWidget::UpdateLighting, 0.05f, true);
}

void UCrossHairWidget::UpdateOpacity()
{
	UE_LOG(LogTemp, Warning, TEXT("TargetOpacity : %f "), TargetOpacity);
	if (CurrentOpacity <= 0.08f && TargetOpacity == 0.0f)
	{
		bTeleportFinish = true;
		OpacityBackGround->SetRenderOpacity(0.0f);
		// 타이머 중지 (업데이트 완료 시 더 이상 필요 없음)
		GetWorld()->GetTimerManager().ClearTimer(OpacityTimerHandle);
	}
	else
	{
		
		CurrentOpacity = UKismetMathLibrary::FInterpTo(CurrentOpacity, TargetOpacity, GetWorld()->GetDeltaSeconds(), 0.4f);
		
		if (!OpacityBackGround)
		{
			UE_LOG(LogTemp, Warning, TEXT("OpacityBackGround is nullptr. Ensure it's bound in the widget blueprint."));
			return;
		}
		OpacityBackGround->SetRenderOpacity(CurrentOpacity);
		UE_LOG(LogTemp, Warning, TEXT("CurrentOpacity : %f"), OpacityBackGround->RenderOpacity);
		// 실제 UI의 Render Opacity를 설정하는 부분 추가 필요
	}

}

void UCrossHairWidget::UpdateLighting()
{
	if (LightR <= 0.0f && BlueLightOpacity >= 17.053461f)
	{
		bLightFinish = true;		//이것도 지워도 됨

		// 타이머 중지 (업데이트 완료 시 더 이상 필요 없음)
		GetWorld()->GetTimerManager().ClearTimer(LightingTimerHandle);
		//subtitle1_2

	}
	else
	{
		// BlueLight 배열을 순회하여 각 LightComponent의 Intensity를 설정합니다.
		for (AActor* Actor : YellowLight)
		{
			if (Actor)
			{
				// Actor에서 LightComponent 가져오기
				ULightComponent* LightComp = Actor->FindComponentByClass<ULightComponent>();
				if (LightComp)
				{
					// 색상 업데이트 (예: RGB 조절)
					LightR = FMath::FInterpTo(LightR, 0.0f, GetWorld()->GetDeltaSeconds(), 0.2f);
					LightG = FMath::FInterpTo(LightG, 0.597, GetWorld()->GetDeltaSeconds(), 0.2f);
					LightB = FMath::FInterpTo(LightB, 1.0, GetWorld()->GetDeltaSeconds(), 0.2f);
					FLinearColor NewColor(LightR, LightG, LightB, 0);
					LightOpacity = FMath::FInterpTo(LightOpacity, 0.1, GetWorld()->GetDeltaSeconds(), 0.2f);

					LightComp->SetLightColor(NewColor, true);
					// LightComponent의 Intensity를 BlueLightOpacity로 설정
					LightComp->SetIntensity(LightOpacity);
				}
			}
		}
		for (AActor* Actor : BlueLight)
		{
			if (Actor)
			{
				// Actor에서 LightComponent 가져오기
				ULightComponent* LightComp = Actor->FindComponentByClass<ULightComponent>();
				if (LightComp)
				{
					// 색상 업데이트 (예: RGB 조절)

					BlueLightOpacity = FMath::FInterpTo(BlueLightOpacity, 25.0f, GetWorld()->GetDeltaSeconds(), 0.4f);

					LightComp->SetIntensity(BlueLightOpacity);
				}
			}
		}




		// 예: YellowLight의 색상과 투명도 설정 (추가 코드 필요)
	}

}

void UCrossHairWidget::BeforeMap3Warp()
{
	if (Warpsound)
	{
		UGameplayStatics::PlaySound2D(this, Warpsound);
	}	
	// 플레이어 컨트롤러 가져오기
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// 플레이어 Pawn 가져오기
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			// 입력 비활성화
			PlayerPawn->DisableInput(PlayerController);
		}
	}
	TargetOpacity = 1.0f;
	StartOpacityUpdate();


	TeleportLocation = FVector(4930, -15210.0f, 582.0f);
	TeleportRotation = FRotator(0.0f, 6.0f, 0.0f);

	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &UCrossHairWidget::Teleport, 5.0f, false);
	GetWorld()->GetTimerManager().SetTimer(WarpTimerHandle, this, &UCrossHairWidget::AfterMap3Warp, 5.0f, false);
}

void UCrossHairWidget::AfterMap3Warp()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		// 플레이어 Pawn 가져오기
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			
			// 입력 비활성화
			PlayerPawn->EnableInput(PlayerController);
		}
	}

	AEscape_RoomCharacter* player = Cast<AEscape_RoomCharacter>(GetOwningPlayerPawn());
	player->SetCurrentMap(ECharacterMapState::Map3);
	StartSubtitles(18, 20);
	player->SetCanShoot(true);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieCharacter::StaticClass(), FoundActors);

	// 배열을 순회하며 Growling 함수 호출
	for (AActor* Actor : FoundActors)
	{
		AZombieCharacter* Zombie = Cast<AZombieCharacter>(Actor);
		if (Zombie)
		{
			Zombie->GrowlingZombie(); // Growling 함수 호출
		}
	}

}