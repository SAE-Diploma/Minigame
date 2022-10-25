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
	// Sets default values for this actor's properties
	AImageSwitcher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	UMaterial* Material;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Texture;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* dynMaterial;

	UPROPERTY(EditAnywhere)
	FRotator Rotation; 
	
	UFUNCTION(BlueprintCallable)
	void SetIndex(int32 Index);


};
