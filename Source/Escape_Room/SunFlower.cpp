// Fill out your copyright notice in the Description page of Project Settings.


#include "SunFlower.h"
#include "CrossHairWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASunFlower::ASunFlower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASunFlower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASunFlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASunFlower::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	
	
	if (Other->ActorHasTag("Arrow")&& !IsHit)
	{
		UGameplayStatics::SpawnSound2D(this, ScreamSound);
		TArray<UUserWidget*> FoundWidgets;
		IsHit = true;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, CrossHairWidget, true);
		for (UUserWidget* widget : FoundWidgets)
		{
			widget->RemoveFromParent();
		}
		
		if (WidgetInstance && WidgetInstance->IsInViewport())
		{
			WidgetInstance->RemoveFromParent();
		}

		WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), CrossHairWidget);
		
		Cast<UCrossHairWidget>(WidgetInstance)->SubTitle2();

		if (WidgetInstance)
		{
			
			WidgetInstance->AddToViewport();
		}
	}
}
//void ASunFlower::DropSunFlower()
//{
//	
//}




