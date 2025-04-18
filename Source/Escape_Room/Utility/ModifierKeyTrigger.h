#pragma once

//ModifierKeyTrigger.h
#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "ModifierKeyTrigger.generated.h"


UCLASS()
class ESCAPE_ROOM_API UModifierKeyTrigger : public UInputTrigger
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category = "Trigger Settings")
	FKey ModifierKey = EKeys::LeftShift;

protected:
	virtual ETriggerType GetTriggerType_Implementation() const override { return ETriggerType::Implicit; }
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput,
		FInputActionValue ModifiedValue, float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

};