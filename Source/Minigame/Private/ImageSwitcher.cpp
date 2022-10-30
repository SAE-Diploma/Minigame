// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageSwitcher.h"

class IMediaTextureSample;
// Sets default values
AImageSwitcher::AImageSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyPlane"));
	RootComponent = Mesh;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	StaticMesh = MeshAsset.Object;
}

void AImageSwitcher::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StaticMesh))
	{
		// Initialize the mesh 
		Mesh->SetStaticMesh(StaticMesh);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RootComponent->SetRelativeRotation(Rotation);
		SetTexture(CurrentIndex);
	}
}

void AImageSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * @brief Sets the CurrentIndex
 * @param Index New Index
 */
void AImageSwitcher::SetIndex(int32 Index)
{
	if (Index != CurrentIndex)
	{
		CurrentIndex = Index;
		SetTexture(CurrentIndex);
	}
}

/**
 * @brief Set the texture by index
 * @param Index Index of the Texture in the Textures Array
 */
void AImageSwitcher::SetTexture(int32 Index)
{
	if (Textures.Num() > Index && IsValid(Material))
	{
		const int32 Width = Textures[Index]->GetSizeX();
		const int32 Height = Textures[Index]->GetSizeY();
		const FVector3d Size = FVector(Width,Height,1)/Width;
		// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Size %f"), Scale));
		
		Mesh->SetRelativeScale3D(Size*Scale);
	
		// set texture to material
		dynMaterial = UMaterialInstanceDynamic::Create(Material,Mesh);
		dynMaterial->SetTextureParameterValue("Texture",Textures[Index]);
		Mesh->SetMaterial(0,dynMaterial);
	}
}




