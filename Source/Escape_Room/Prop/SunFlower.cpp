// Fill out your copyright notice in the Description page of Project Settings.


#include "SunFlower.h"
#include "UI/CrossHairWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

ASunFlower::ASunFlower()
{
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));

}

void ASunFlower::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (Other->ActorHasTag("Arrow"))
	{
		UGameplayStatics::SpawnSound2D(this, ScreamSound);
		TArray<UUserWidget*> FoundWidgets;
		
		GetWorld()->GetTimerManager().SetTimer(FallTimerHandle, this, &ASunFlower::KilledSunFlower, 0.01f, true);

		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, CrossHairWidget, true);
		for (UUserWidget* Widget : FoundWidgets)
		{
			Widget->RemoveFromParent();
		}
		
		if (WidgetInstance && WidgetInstance->IsInViewport())
		{
			WidgetInstance->RemoveFromParent();
		}

		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CrossHairWidget);
		
		Cast<UCrossHairWidget>(WidgetInstance)->ShowSubTitleAfterSunFlowerHit();

		if (WidgetInstance)
		{
			
			WidgetInstance->AddToViewport();
		}
	}
}

void ASunFlower::KilledSunFlower()
{
	if (GetActorLocation().Z > 509.0f)
	{
		AddActorLocalOffset(FVector(0.0f, 0.0f, -18.0f));
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FallTimerHandle);
	}
}





