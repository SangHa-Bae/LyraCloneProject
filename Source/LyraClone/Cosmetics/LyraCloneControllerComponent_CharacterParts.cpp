#include "LyraCloneControllerComponent_CharacterParts.h"
#include "LyraClonePawnComponent_CharacterParts.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraCloneControllerComponent_CharacterParts)

ULyraCloneControllerComponent_CharacterParts::ULyraCloneControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void ULyraCloneControllerComponent_CharacterParts::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (AController* OwningController = GetController<AController>())
		{
			OwningController->OnPossessedPawnChanged.AddDynamic(this, &ThisClass::OnPossessedPawnChanged);
		}
	}
}

void ULyraCloneControllerComponent_CharacterParts::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveAllCharacterParts();

	Super::EndPlay(EndPlayReason);
}

ULyraClonePawnComponent_CharacterParts* ULyraCloneControllerComponent_CharacterParts::GetPawnCustomizer() const
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		return ControlledPawn->FindComponentByClass<ULyraClonePawnComponent_CharacterParts>();
	}
	return nullptr;
}

void ULyraCloneControllerComponent_CharacterParts::AddCharacterPartInternal(const FLyraCloneCharacterPart& NewPart)
{
	FLyraCloneControllerCharacterPartEntry& NewEntry = CharacterParts.AddDefaulted_GetRef();
	NewEntry.Part = NewPart;

	if (ULyraClonePawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		NewEntry.Handle = PawnCustomizer->AddCharacterPart(NewPart);
	}
}

void ULyraCloneControllerComponent_CharacterParts::AddCharacterPart(const FLyraCloneCharacterPart& NewPart)
{
	AddCharacterPartInternal(NewPart);
}

void ULyraCloneControllerComponent_CharacterParts::RemoveAllCharacterParts()
{
	if (ULyraClonePawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		for (FLyraCloneControllerCharacterPartEntry& Entry : CharacterParts)
		{
			PawnCustomizer->RemoveCharacterPart(Entry.Handle);
		}
	}

	CharacterParts.Reset();
}

void ULyraCloneControllerComponent_CharacterParts::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if(ULyraClonePawnComponent_CharacterParts * OldCustomizer = OldPawn ? OldPawn->FindComponentByClass<ULyraClonePawnComponent_CharacterParts>() : nullptr)
	{
		for (FLyraCloneControllerCharacterPartEntry& Entry : CharacterParts)
		{
			OldCustomizer->RemoveCharacterPart(Entry.Handle);
			Entry.Handle.Reset();
		}
	}
	if (ULyraClonePawnComponent_CharacterParts* NewCustomizer = NewPawn ? NewPawn->FindComponentByClass<ULyraClonePawnComponent_CharacterParts>() : nullptr)
	{
		for (FLyraCloneControllerCharacterPartEntry& Entry : CharacterParts)
		{
			check(!Entry.Handle.IsValid());
			Entry.Handle = NewCustomizer->AddCharacterPart(Entry.Part);
		}
	}
}
