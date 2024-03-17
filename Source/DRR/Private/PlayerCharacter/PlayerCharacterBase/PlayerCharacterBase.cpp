// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Equipment/Weapon/DRRWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "DataAsset/Item/DA_WeaponData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utilities/UtilityList.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(500.0f, 100.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// Set Mesh-Kwakhyunbin
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement Default-Kwakhyunbin
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;


	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));


	//Set Rotation Remit-Kwakhyunbin
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set Mesh and Anim BP-Kwakhyunbin
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/ProtoTypeAsset/Characters/Heroes/Wraith/Meshes/Wraith.Wraith"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/ProtoTypeAsset/Characters/Heroes/Wraith/Wraith_AnimBlueprint.Wraith_AnimBlueprint_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FClassFinder<ADRRWeaponBase> WeaponClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Weapon/BP_Weapon1.BP_Weapon1_C'"));
		CLog::Log(WeaponClassRef.Class);
	if (WeaponClassRef.Class)
	{
		Weapon = WeaponClassRef.Class;

		
	}

}

void APlayerCharacterBase::BeginPlay()
{
	SetWeapon(Weapon);
}

void APlayerCharacterBase::SetWeapon(TSubclassOf<class ADRRWeaponBase> NewWeapon)
{
	Weapon = NewWeapon;

	WeaponObject = NewObject<ADRRWeaponBase>(Weapon);

	
}


