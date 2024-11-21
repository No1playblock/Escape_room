// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class ESCAPE_ROOM_API AArrow : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
public:	
	// Sets default values for this actor's properties
	AArrow();


	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns CollisionComp subobject **/
	UBoxComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	//전방을 가르키는 Arrow(화살표)
private:
	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent;

};
