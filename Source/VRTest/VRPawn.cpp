// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Components/WidgetInteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	//We look for the widgets interaction in components
	TArray<UWidgetInteractionComponent*> MyComponents;
	GetComponents<UWidgetInteractionComponent>(MyComponents);

	if (MyComponents.Num() >= 2)
	{
		WidgetInteractionLeftRef = MyComponents[0];
		WidgetInteractionRightRef = MyComponents[1];
	}
}

void AVRPawn::LineTraceByChannelBasedOnSceneComponent(USceneComponent* SceneComponent)
{
	FVector StartLocation = SceneComponent->GetComponentLocation();
	FVector EndLocation = SceneComponent->GetComponentLocation() + SceneComponent->GetForwardVector()*DistanceToCheckTrace;

	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_Visibility);

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = false;

	FHitResult OutHit;

	bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, TraceChannel, false, TArray<AActor*>(), EDrawDebugTrace::None, OutHit, true, FLinearColor::Red, FLinearColor::Green, 5.f);

	if (bHit)
	{
		AChangeMaterialActor* HitActor = Cast<AChangeMaterialActor>(OutHit.GetActor());
		if (HitActor != nullptr)
		{
			if(HitActor != SelectedActor)
			{
				if (SelectedActor != nullptr)
				{
					SelectedActor->BP_RemoveMaterialSelectionWidget();
					SelectedActor->BP_HideSelectionDecal();
				}

				HitActor->BP_ShowSelectionDecal();
				SelectedActor = HitActor;
				SelectedActor->BP_ToggleMaterialSelectionWidget(false);
			}
		}
	}
}

void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsInSelectingModeLeft)
	{
		LineTraceByChannelBasedOnSceneComponent(WidgetInteractionLeftRef);
	}

	if(bIsInSelectingModeRight)
	{
		LineTraceByChannelBasedOnSceneComponent(WidgetInteractionRightRef);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

