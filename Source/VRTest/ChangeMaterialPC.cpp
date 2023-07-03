// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeMaterialPC.h"
#include "ChangeMaterialActor.h"
#include "MaterialChangerInterface.h"
#include "VRPawn.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

void AChangeMaterialPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChangeMaterialPC::Server_SetMaterial_Implementation(UMaterialInterface* NewMaterial)
{
	AVRPawn* PawnToChange = Cast<AVRPawn>(GetPawn());
	if(PawnToChange != nullptr)
	{
		if(PawnToChange->SelectedActor != nullptr)
		{
			PawnToChange->SelectedActor->DecalComponent->SetVisibility(false);

			if(UKismetSystemLibrary::DoesImplementInterface(PawnToChange->SelectedActor, UMaterialChangerInterface::StaticClass()))
			{
				PawnToChange->SelectedActor->Execute_ChangeMaterial(PawnToChange->SelectedActor, NewMaterial);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UMaterialChangerInterface Not Implemented!!!"));
			}
			
			PawnToChange->SelectedActor->CurrentMaterial = NewMaterial;
		}
	}
}
