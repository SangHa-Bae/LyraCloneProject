#pragma once

#include "Components/PawnComponent.h"
#include "LyraCloneCharacterPartTypes.h"
#include "LyraCloneCosmeticAnimationTypes.h"

#include "LyraClonePawnComponent_CharacterParts.generated.h"

/** 인스턴스화 된 Character Part의 단위 */
USTRUCT()
struct FLyraCloneAppliedCharacterPartEntry
{
	GENERATED_BODY()

	FLyraCloneAppliedCharacterPartEntry()
	{}
		
	// The character part being represented
	UPROPERTY()
	FLyraCloneCharacterPart Part;

	// Handle index we returned to the user (server only)
	UPROPERTY()
	int32 PartHandle = INDEX_NONE;

	// The spawned actor instance (client only)
	UPROPERTY()
	TObjectPtr<UChildActorComponent> SpawnedComponent = nullptr;
};

USTRUCT(BlueprintType)
struct FLyraCloneCharacterPartList
{
	GENERATED_BODY()

	FLyraCloneCharacterPartList()
		: OwnerComponent(nullptr)
	{
	}

	FLyraCloneCharacterPartList(ULyraClonePawnComponent_CharacterParts* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

	FGameplayTagContainer CollectCombinedTags() const;

	FLyraCloneCharacterPartHandle AddEntry(FLyraCloneCharacterPart NewPart);
	void RemoveEntry(FLyraCloneCharacterPartHandle Handle);

	bool SpawnActorForEntry(FLyraCloneAppliedCharacterPartEntry& Entry);
	void DestroyActorForEntry(FLyraCloneAppliedCharacterPartEntry& Entry);

	// Replicated list of equipment entries
	UPROPERTY()
	TArray<FLyraCloneAppliedCharacterPartEntry> Entries;

	// The component that contains this list
	UPROPERTY()
	TObjectPtr<ULyraClonePawnComponent_CharacterParts> OwnerComponent;

	// Upcounter for handles
	int32 PartHandleCounter = 0;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class ULyraClonePawnComponent_CharacterParts : public UPawnComponent
{
	GENERATED_BODY()

public:
	ULyraClonePawnComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
		
	USkeletalMeshComponent* GetParentMeshComponent() const;
	USceneComponent* GetSceneComponentToAttachTo() const;

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Cosmetics)
	FGameplayTagContainer GetCombinedTags(FGameplayTag RequiredPrefix) const;

	void BroadcastChanged();

	FLyraCloneCharacterPartHandle AddCharacterPart(const FLyraCloneCharacterPart& NewPart);

	void RemoveCharacterPart(FLyraCloneCharacterPartHandle Handle);
	
	// List of character parts
	UPROPERTY()
	FLyraCloneCharacterPartList CharacterPartList;

	// Rules for how to pick a body style mesh for animation to play on, based on character part cosmetics tags
	UPROPERTY(EditAnywhere, Category = Cosmetics)
	FLyraCloneAnimBodyStyleSelectionSet BodyMeshes;

};