// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MaterialChangerInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMaterialChangerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VRTEST_API IMaterialChangerInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Material")
	void ChangeMaterial(UMaterialInterface* NewMaterial);
};
