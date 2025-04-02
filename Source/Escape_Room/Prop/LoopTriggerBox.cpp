// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/LoopTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/CrossHairWidget.h"

ALoopTriggerBox::ALoopTriggerBox()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALoopTriggerBox::OnBoxBeginOverlap);
}

void ALoopTriggerBox::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (LoopCount < 4)
	{
		FVector LoopLocation;
		LoopLocation.X = -1471.5f;
		LoopLocation.Y = OtherActor->GetActorLocation().Y;
		LoopLocation.Z = OtherActor->GetActorLocation().Z;

		OtherActor->SetActorLocation(LoopLocation);
		LoopCount++;

		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UUserWidget::StaticClass(), false);
		for (UUserWidget* Widget : FoundWidgets)
		{
			Widget->RemoveFromParent();
		}

		WidgetInstance = CreateWidget<UCrossHairWidget>(GetWorld(), CrossHairWidget);

		switch (LoopCount)
		{
		case 1:
			Cast<UCrossHairWidget>(WidgetInstance)->ShowSubTitleSecondLoop();
			break;
		case 2:
			Cast<UCrossHairWidget>(WidgetInstance)->ShowSubTitleThirdLoop();
			break;
		case 3:
			Cast<UCrossHairWidget>(WidgetInstance)->ShowSubTitleFourthLoop();
			break;
		case 4:
			Cast<UCrossHairWidget>(WidgetInstance)->BeforeMap3Warp();
			break;
		}
		WidgetInstance->AddToViewport();

	}
}

