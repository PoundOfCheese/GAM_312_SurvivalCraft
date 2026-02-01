// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingPart.h"
#include "PlayerWidget.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAM312_SURVIVALCRAFT_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles player forward and backward movement
	UFUNCTION()
	void MoveForward(float axisValue);

	// Handles player left and right movement
	UFUNCTION()
	void MoveRight(float axisValue);

	// Sets player jump state to true
	UFUNCTION()
	void StartJump();

	// Sets player jump state to false
	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void FindObject();

	// Player camera component
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamComp;

	// Player health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health = 100.0f;

	// Player Hunger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Hunger = 100.0f;

	// Player Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina = 100.0f;

	// Owned wood
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Wood;

	// Owned stone
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Stone;

	// Owned berry
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Berry;

	// Array of integers for owned resources
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		TArray<int> ResourcesArray;

	// Array of names for owned resources
	UPROPERTY(EditAnywhere, Category = "Resources")
		TArray<FString> ResourcesNameArray;

	// Decal for hit feedback
	UPROPERTY(EditAnywhere, Category = "HitMarker")
		UMaterialInterface* hitDecal;

	// Store number of each building part the player has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies")
		TArray<int> BuildingArray;

	// Is the player currently building?
	UPROPERTY()
		bool isBuilding;

	// 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<ABuildingPart>BuildPartClass;

	// Variable to set which building part is being spawned
	UPROPERTY()
		ABuildingPart* spawnedPart;

	// PlayerWidget
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPlayerWidget* playerUI;

	// Set player health
	UFUNCTION(BlueprintCallable)
		void SetHealth(float amount);

	// Set player hunger
	UFUNCTION(BlueprintCallable)
		void SetHunger(float amount);

	// Set player stamina
	UFUNCTION(BlueprintCallable)
		void SetStamina(float amount);

	// Decrease player stats
	UFUNCTION(BlueprintCallable)
		void DecreaseStats();

	// Give resource to player
	UFUNCTION()
		void GiveResource(float amount, FString resourceType);

	// Update player resources when crafting building objects
	UFUNCTION(BlueprintCallable)
		void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject);

	// Spawn building in world
	UFUNCTION(BlueprintCallable)
		void SpawnBuilding(int buildingID, bool& isSuccess);

	// Rotate building in world
	UFUNCTION()
		void RotateBuilding();
};
