#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AlsAnimNotifyState_BlockInput.generated.h"

/**
 * Used to block input during an animation
 */
UCLASS()
class ALS_API UAlsAnimNotifyState_BlockInput : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAlsAnimNotifyState_BlockInput();

	// Begin UAnimNotifyState
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence, float Duration, const FAnimNotifyEventReference& NotifyEventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence, const FAnimNotifyEventReference& NotifyEventReference) override;
	// End UAnimNotifyState
};
