// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeMaterialActor.h"
#include "Components/DecalComponent.h"
#include "Net/UnrealNetwork.h"

AChangeMaterialActor::AChangeMaterialActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->SetupAttachment(MeshComponent);

	bReplicates = true;
	CurrentMaterial = nullptr;
}

void AChangeMaterialActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChangeMaterialActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChangeMaterialActor::ChangeMaterial_Implementation(UMaterialInterface* NewMaterial)
{
	if (MeshComponent)
	{
		if (NewMaterial != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ChangeMaterial_Implementation: %s"), *NewMaterial->GetName());
		}
		else UE_LOG(LogTemp, Warning, TEXT("ChangeMaterial_Implementation NULL"));
		MeshComponent->SetMaterial(0, NewMaterial);
		CurrentMaterial = NewMaterial;
	}
}

void AChangeMaterialActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AChangeMaterialActor, CurrentMaterial, COND_None);
}

void AChangeMaterialActor::OnRep_CurrentMaterial()
{
	if (MeshComponent && CurrentMaterial)
	{
		MeshComponent->SetMaterial(0, CurrentMaterial);
	}
}