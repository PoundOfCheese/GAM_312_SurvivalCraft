// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource_M.h"

// Sets default values
AResource_M::AResource_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup ResourceNameTxt and Mesh
	ResourceNameTxt = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// Set RootComponent to Mesh
	RootComponent = Mesh;

	// Attach ResourceNameTxt to Mesh
	ResourceNameTxt->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AResource_M::BeginPlay()
{
	Super::BeginPlay();

	// Set tempText to resourceName
	tempText = tempText.FromString(resourceName);
	
	// Set text renderer with tempText
	ResourceNameTxt->SetText(tempText);
}

// Called every frame
void AResource_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

