#pragma once

#include "GameplayTagContainer.h"

#include "LyraCloneCosmeticAnimationTypes.generated.h"

USTRUCT(BlueprintType)
struct FLyraCloneAnimBodyStyleSelectionEntry
{
	GENERATED_BODY()

	// Layer to apply if the tag matches
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> Mesh = nullptr;

	// Cosmetic tags required (all of these must be present to be considered a match)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Cosmetic"))
	FGameplayTagContainer RequiredTags;
};

USTRUCT(BlueprintType)
struct FLyraCloneAnimBodyStyleSelectionSet
{
	GENERATED_BODY()

	// List of layer rules to apply, first one that matches will be used
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLyraCloneAnimBodyStyleSelectionEntry> MeshRules;

	// The layer to use if none of the LayerRules matches
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> DefaultMesh = nullptr;

	// If set, ensures this physics asset is always used
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPhysicsAsset> ForcedPhysicsAsset = nullptr;

};
