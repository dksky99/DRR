// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "CharacterControllDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	//Set character capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);

	//Set character collision
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCapsule"));

	//Set Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/Asset/Character/Meshes/4DRR_Player.4DRR_Player"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}


}

void ACharacterBase::SetCharacterControlData(const UCharacterControlDataAsset* CharacterControlData)
{
	//pawn
	bUseControllerRotationPitch = CharacterControlData->bUseControlRotationPitch;
	bUseControllerRotationYaw = CharacterControlData->bUseControlRotationYaw;
	bUseControllerRotationRoll = CharacterControlData->bUseControlRotationRoll;

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;

}



