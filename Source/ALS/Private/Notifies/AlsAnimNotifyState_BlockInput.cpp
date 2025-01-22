// This class
#include "Notifies/AlsAnimNotifyState_BlockInput.h"

// Engine
#include "NativeGameplayTags.h"

// Plugin
#include "AlsCharacter.h"
#include "AlsCharacterMovementComponent.h"

namespace AlsLocomotionActionTags
{
	// Since AAlsCharacter::Jump checks whether we are not doing any locomotion action, simply adding one for the purpose
	// of blocking jumps will suffice.
	UE_DEFINE_GAMEPLAY_TAG_STATIC(BlockJump, FName{ TEXTVIEW("Als.LocomotionAction.BlockJump") });
}

UAlsAnimNotifyState_BlockInput::UAlsAnimNotifyState_BlockInput()
{
#if WITH_EDITOR
	bShouldFireInEditor = false;
#endif
}

FString UAlsAnimNotifyState_BlockInput::GetNotifyName_Implementation() const
{
	return TEXT("AlsAnimNotifyState_BlockInput");
}

void UAlsAnimNotifyState_BlockInput::NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence, float Duration, const FAnimNotifyEventReference& NotifyEventReference)
{
	Super::NotifyBegin(Mesh, Sequence, Duration, NotifyEventReference);

	AAlsCharacter* const Character = Cast<AAlsCharacter>(Mesh->GetOwner());
	if (IsValid(Character))
	{
		UAlsCharacterMovementComponent* ALSCharacterMovementComponent = Cast<UAlsCharacterMovementComponent>(Character->GetMovementComponent());
		if (IsValid(ALSCharacterMovementComponent))
		{
			Character->SetLocomotionAction(AlsLocomotionActionTags::BlockJump);
			ALSCharacterMovementComponent->SetInputBlocked(true);
		}
	}
}

void UAlsAnimNotifyState_BlockInput::NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence, const FAnimNotifyEventReference& NotifyEventReference)
{
	Super::NotifyEnd(Mesh, Sequence, NotifyEventReference);

	AAlsCharacter* const Character = Cast<AAlsCharacter>(Mesh->GetOwner());
	if (IsValid(Character))
	{
		UAlsCharacterMovementComponent* ALSCharacterMovementComponent = Cast<UAlsCharacterMovementComponent>(Character->GetMovementComponent());
		if (IsValid(ALSCharacterMovementComponent))
		{
			Character->SetLocomotionAction(FGameplayTag::EmptyTag);
			ALSCharacterMovementComponent->SetInputBlocked(false);
		}
	}
}
