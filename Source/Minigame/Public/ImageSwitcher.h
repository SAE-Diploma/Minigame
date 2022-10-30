// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImageSwitcher.generated.h"

UCLASS()
class MINIGAME_API AImageSwitcher : public AActor
{
	GENERATED_BODY()
	
public:	
	AImageSwitcher();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UPROPERTY()
	UStaticMesh* StaticMesh;
	
	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* dynMaterial;
	
	UPROPERTY(EditAnywhere)
	UMaterial* Material;

	UPROPERTY(EditAnywhere)
	int32 Scale = 1;
	
	UPROPERTY(EditAnywhere)
	TArray<UTexture2D*> Textures;

	UPROPERTY(EditAnywhere)
	FRotator Rotation = FRotator(90,0,90); 

	UPROPERTY(EditAnywhere)
	int32 CurrentIndex = 0;
	
	UFUNCTION(BlueprintCallable)
	void SetIndex(int32 Index);

private:
	
	UFUNCTION(BlueprintCallable)
	void SetTexture(int32 Index);
};


