// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup player camera component
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));
	PlayerCamComp->SetupAttachment(GetMesh(), "head");
	PlayerCamComp->bUsePawnControlRotation = true;

	// Setup arrays for resource amount and name
	ResourcesArray.SetNum(3);
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));

}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreaseStats, 2.0f, true);
	
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump);
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject);
}

// Handles player forward and backward movement
void APlayerChar::MoveForward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

// Handles player left and right movement
void APlayerChar::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

// Sets player jump state to true
void APlayerChar::StartJump()
{
	bPressedJump = true;
}

// Sets player jump state to false
void APlayerChar::StopJump()
{
	bPressedJump = false;
}

void APlayerChar::FindObject()
{
	// Setup HitResult for line trace
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;
	FVector EndLocation = StartLocation + Direction;

	// Setup collision query parameters
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	// Perform line trace
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor());

		// Check if player has enough stamina
		if (Stamina > 5.0f)
		{
			// If HitResource is AResource_M
			if (HitResource)
			{
				// Get name and value from HitResource
				FString hitName = HitResource->resourceName;
				int resourceValue = HitResource->resourceAmount;

				// Give resourceAmount to player
				GiveResource(resourceValue, hitName);

				check(GEngine != nullptr);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected"));

				// Spawn hitDecal
				UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

				// Remove 5 stamina from player
				SetStamina(-5.0);
				
				// Remove resourceAmount from totalResource of the resource node
				HitResource->totalResource = HitResource->totalResource - resourceValue;

				int totalResource = HitResource->totalResource;
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Total Resource: %i"), totalResource));

				// If there is nothing left in the resource node
				if (HitResource->totalResource < resourceValue)
				{
					HitResource->Destroy();
					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
				}

				
			}
		}

		
	}
}

// Set player health
void APlayerChar::SetHealth(float amount)
{
	if (Health + amount <= 100)
	{
		Health = Health + amount;
	}
}

// Set player hunger
void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount <= 100)
	{
		Hunger = Hunger + amount;
	}
}

// Set player stamina
void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount <= 100)
	{
		Stamina = Stamina + amount;
	}
}

// Handles modifying player stats when called by game timer
void APlayerChar::DecreaseStats()
{
	// If player has hunger, decrease hunger
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}
	
	// Recharge stamina
	SetStamina(10.0f);

	// If player has no hunger, decrease health
	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}

	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Health: %.1f"), Health));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Hunger: %.1f"), Hunger));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Stamina: %.1f"), Stamina));

}

// Give resource to player
void APlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}
	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}
	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
}

