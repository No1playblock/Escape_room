// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TitleWidget.h"
#include "MediaPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
void UTitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartBtn)
    {
        StartBtn->OnClicked.AddDynamic(this, &UTitleWidget::OnStartButtonClicked);
        RunAwayBtn->OnClicked.AddDynamic(this, &UTitleWidget::PlayFirstGunChromakeyMedia);
    }

    if (MPBackGround && TitleBackground)
    {
        if (MPBackGround->OpenSource(TitleBackground))
        {
            MPBackGround->Play();
        }
    }
}

void UTitleWidget::OnStartButtonClicked()
{
   
    GetWorld()->GetTimerManager().SetTimer(OpacityTimerHandle,this,&UTitleWidget::UpdateOpacity, FadeUpdateRate, true);

    if (StartBtnSound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), StartBtnSound);
    }

    GetWorld()->GetTimerManager().SetTimer(LevelLoadTimerHandle, this, &UTitleWidget::DelayedLevelLoad, 3.0f, false);
}

void UTitleWidget::UpdateOpacity()
{
    const float DeltaTime = FadeUpdateRate;
    Opacity = UKismetMathLibrary::FInterpTo(Opacity, 1.0f, DeltaTime, InterpSpeed);

    if (OpacityBackGround)
    {
        OpacityBackGround->SetRenderOpacity(Opacity);
    }

    if (FMath::IsNearlyEqual(Opacity, 1.0f, 0.01f))
    {
        GetWorld()->GetTimerManager().ClearTimer(OpacityTimerHandle);
        Opacity = 1.0f;
    }
}

void UTitleWidget::PlayFirstGunChromakeyMedia()
{
    RunAwayBtn->SetIsEnabled(false);

    if (MPFirstGunChromakey)
    {
        if (MPFirstGunChromakey->OpenSource(GunChromakey))
        {
            MPFirstGunChromakey->Play();
        }
    }
    GetWorld()->GetTimerManager().SetTimer(SoundTimerHandle, this, &UTitleWidget::PlayFirstGunSound, 0.2f, false);
    
}

void UTitleWidget::PlaySecondGunChromakeyMedia()
{
    if (MPSeconGunChromakey)
    {
        if (MPSeconGunChromakey->OpenSource(GunChromakey))
        {
            MPSeconGunChromakey->Play();
        }
    }
    GetWorld()->GetTimerManager().SetTimer(SoundTimerHandle, this, &UTitleWidget::PlaySecondGunSound, 0.2f, false);
}

void UTitleWidget::DelayedLevelLoad()
{
    UGameplayStatics::OpenLevel(this, LevelName);
}

void UTitleWidget::PlayFirstGunSound()
{
    UGameplayStatics::PlaySound2D(GetWorld(), GunShotSound);
    FirstGun->SetVisibility(ESlateVisibility::Visible);
    GetWorld()->GetTimerManager().SetTimer(FunctionTimerHandle, this, &UTitleWidget::PlaySecondGunChromakeyMedia, 0.1f, false);
}

void UTitleWidget::PlaySecondGunSound()
{
    UGameplayStatics::PlaySound2D(GetWorld(), GunShotSound);
    SecondGun->SetVisibility(ESlateVisibility::Visible);
   
}

