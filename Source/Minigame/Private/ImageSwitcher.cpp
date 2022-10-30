// Fill out your copyright notice in the Description page of Project Settings.


#include "ImageSwitcher.h"

class IMediaTextureSample;
// Sets default values
AImageSwitcher::AImageSwitcher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyPlane"));

	RootComponent = Mesh;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	StaticMesh = MeshAsset.Object;

	
	


}

// Called when the game starts or when spawned
void AImageSwitcher::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), GetWorld()->TimeSeconds));

	if (IsValid(StaticMesh))
	{
		Mesh->SetStaticMesh(StaticMesh);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RootComponent->SetRelativeRotation(Rotation);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Rotation.ToString());
		SetTexture(CurrentIndex);
	}
}

// Called every frame
void AImageSwitcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AImageSwitcher::SetIndex(int32 Index)
{
	FString number = "";
	number.AppendInt(Index);
	UE_LOG(LogTemp,Warning,TEXT("Index is: %s"),*number);
}

void AImageSwitcher::SetTexture(int32 Index)
{
	if (Textures.Num() > Index && IsValid(Material))
	{
		const int32 width = Textures[Index]->GetSizeX();
		const int32 height = Textures[Index]->GetSizeY();
		FVector3d size = FVector(width,height,1)/width*Scale;
		
		Mesh->SetWorldScale3D(size);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, size.ToString());
	
		// set texture to material
		dynMaterial = UMaterialInstanceDynamic::Create(Material,Mesh);
		dynMaterial->SetTextureParameterValue("Texture",Textures[Index]);
		Mesh->SetMaterial(0,dynMaterial);
	}
}




