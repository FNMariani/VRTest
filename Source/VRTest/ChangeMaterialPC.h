// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChangeMaterialActor.h"
#include "GameFramework/PlayerController.h"
#include "ChangeMaterialPC.generated.h"

/**
 * 
 */
UCLASS()
class VRTEST_API AChangeMaterialPC : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AActor* ActorToChange;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* _NewMaterial;

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SetMaterial(UMaterialInterface* NewMaterial);
};
