// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialChangerInterface.h"
#include "GameFramework/Actor.h"
#include "ChangeMaterialActor.generated.h"

UCLASS()
class VRTEST_API AChangeMaterialActor : public AActor, public IMaterialChangerInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDecalComponent* DecalComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentMaterial, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* CurrentMaterial;
	
public:
	AChangeMaterialActor();

	virtual void ChangeMaterial_Implementation(UMaterialInterface* NewMaterial) override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnRep_CurrentMaterial();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_CreateMaterialSelectionWidget(bool bActiveMenuHandRight);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_RemoveMaterialSelectionWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_ToggleMaterialSelectionWidget(bool bActiveMenuHandRight);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_ShowSelectionDecal();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_HideSelectionDecal();
};
