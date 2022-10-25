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
	dynMaterial = UMaterialInstanceDynamic::Create(Material,Mesh);
	SetActorRotation(Rotation);

	
	if (IsValid(StaticMesh) && IsValid(dynMaterial) && IsValid(Texture))
	{
		Mesh->SetStaticMesh(StaticMesh);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		const int32 width = Texture->GetSizeX();
		const int32 height = Texture->GetSizeY();
		FVector3d size = FVector3d(width,height,0)/width;
		Mesh->SetRelativeScale3D(size);
		dynMaterial->SetTextureParameterValue("Texture",Texture);
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, size.ToString());
		Mesh->SetMaterial(0,dynMaterial);
	
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Something not valid"));
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


