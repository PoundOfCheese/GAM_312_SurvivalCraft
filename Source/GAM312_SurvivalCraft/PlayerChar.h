// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
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
};
