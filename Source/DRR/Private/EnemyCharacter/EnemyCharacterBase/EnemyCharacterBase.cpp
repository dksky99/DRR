// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter/EnemyCharacterBase/EnemyCharacterBase.h"
#include "DBEnemyCharacterSetting.h"
#include "Components/CapsuleComponent.h"
#include "GameManager/GameManager.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"

AEnemyCharacterBase::AEnemyCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// UI Widget
	EnemyHPBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHPBar"));
	EnemyHPBar->SetupAttachment(GetMesh());
	EnemyHPBar->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget> EnemyHPBarWidgetRef(TEXT("/Game/Asset/UI/WBP_EnemyHPBar.WBP_EnemyHPBar"));
	if (EnemyHPBarWidgetRef.Class)
	{
		EnemyHPBar->SetWidgetClass(EnemyHPBarWidgetRef.Class);
		EnemyHPBar->SetWidgetSpace(EWidgetSpace::Screen);
		EnemyHPBar->SetDrawSize(FVector2D(150.0f, 20.0f));
		EnemyHPBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

}

AEnemyCharacterBase::AEnemyCharacterBase(int Type)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UDBEnemyCharacterSetting> EnemyDataAssetRef(TEXT("/Game/Blueprints/DataAsset/EnemeyData/EnemeyCharacter.EnemeyCharacter"));
	UDBEnemyCharacterSetting* EnemyDataAsset = nullptr;
	EnemyType = Type;
	if (EnemyDataAssetRef.Succeeded())
	{
		EnemyDataAsset = EnemyDataAssetRef.Object;
	}
	if (EnemyDataAsset)
	{
		// Iterate through the array and access individual settings
		const FEnemyCharacterSetting& EnemyData = EnemyDataAsset->SEnemyData[EnemyType];

		// Access variables from the EnemyData structure
		EnemyName = EnemyData.Name;
		CapsuleSize = EnemyData.CapsuleSize;
		CapsuleHeight = EnemyData.CapsuleHeight;
		CapsuleProfileName = EnemyData.CapsuleProfileName;
		MeshVector = EnemyData.MeshVector;
		MeshRotator = EnemyData.MeshRotator;
		CharacterbOrientRotationToMovement = EnemyData.CharacterbOrientRotationToMovement;
		CharacterRotationRate = EnemyData.CharacterRotationRate;
		CharacterJumpZVelocity = EnemyData.CharacterJumpZVelocity;
		CharacterAirControl = EnemyData.CharacterAirControl;
		CharacterMaxWalkSpeed = EnemyData.CharacterMaxWalkSpeed;
		CharacterMinAnalogWalkSpeed = EnemyData.CharacterMinAnalogWalkSpeed;
		CharacterBrakingDecelerationWalking = EnemyData.CharacterBrakingDecelerationWalking;
		CharacterMesh = EnemyData.CharacterMesh;
		CharacterAnimBP = EnemyData.CharacterAnimBP;
		MaxHP = EnemyData.HP;
		physicsAttack = EnemyData.PhysicsAttackCoefficient;
	//	MagicAttack = EnemyData.MagicAttackCoefficient;
		physicsDef = EnemyData.PhysicsDefCoefficient;
//		MagicDef = EnemyData.MagicDefCoefficient;
		HPRegenSpeed = EnemyData.HPRegenerationSpeed;

	}

	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(CapsuleSize, CapsuleHeight);
	GetCapsuleComponent()->SetCollisionProfileName(FName(*CapsuleProfileName));

	// Set Mesh-Kwakhyunbin
	GetMesh()->SetRelativeLocationAndRotation(MeshVector, MeshRotator);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Set Movement Default-Kwakhyunbin
	GetCharacterMovement()->bOrientRotationToMovement = CharacterbOrientRotationToMovement;
	GetCharacterMovement()->RotationRate = CharacterRotationRate;
	GetCharacterMovement()->JumpZVelocity = CharacterJumpZVelocity;
	GetCharacterMovement()->AirControl = CharacterAirControl;
	GetCharacterMovement()->MaxWalkSpeed = CharacterMaxWalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = CharacterMinAnalogWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = CharacterBrakingDecelerationWalking;

	//Set Rotation Remit-Kwakhyunbin
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Set Mesh and Anim BP-Kwakhyunbin
	GetMesh()->SetSkeletalMesh(CharacterMesh);
	GetMesh()->SetAnimInstanceClass(CharacterAnimBP);

}

void AEnemyCharacterBase::OnPerception(AActor* Actor, FAIStimulus stimulus)
{
}

void AEnemyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	UGameManager* GameInstance = Cast<UGameManager>(GetGameInstance());
	if (GameInstance)
	{
		Level = GameInstance->ReturnLevel()/difficulty;
	}
	else
	{
		Level = 1;
	}
	MaxHP = MaxHP * (100 + Level);
	CurrentHP = MaxHP;
	physicsAttack = physicsAttack * (100 + Level);
	//MagicAttack = MagicAttack * (100 + Level);
	physicsDef = physicsAttack * (100 + Level);
	//MagicDef = MagicDef * (100 + Level);
}

void AEnemyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacterBase::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0.0f, 1000.0f);
}
