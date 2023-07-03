// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeMaterialActor.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class VRTEST_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaterialChanger")
	AChangeMaterialActor* SelectedActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaterialChanger")
	float DistanceToCheckTrace = 10000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaterialChanger")
	bool bIsInSelectingModeLeft = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaterialChanger")
	bool bIsInSelectingModeRight = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaterialChanger")
	class UWidgetInteractionComponent* WidgetInteractionLeftRef;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "MaterialChanger")
	UWidgetInteractionComponent* WidgetInteractionRightRef;

public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;

	void LineTraceByChannelBasedOnSceneComponent(USceneComponent* SceneComponent);

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
