// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SunFlower.generated.h"

UCLASS()
class ESCAPE_ROOM_API ASunFlower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASunFlower();

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	UUserWidget* WidgetInstance;

	bool IsHit=false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CrossHairWidget;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USoundBase* ScreamSound;

	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
