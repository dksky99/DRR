// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerCharacterBase/PlayerCharacterBase.h"

#include "CharacterBase/DRRActComponent.h"

#include "Components/CapsuleComponent.h"
#include "Equipment/Weapon/DRRWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "DataAsset/Item/DA_WeaponData.h"

#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Utilities/UtilityList.h"

#include "Equipment/Weapon/DRRWeaponBase.h"
#include "Skill/DRRActUnitBase.h"

APlayerCharacterBase::APlayerCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Capsule-Kwakhyunbin
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 100.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));

	// Set Mesh-Kwakhyunbin
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("Player"));
	
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


	//�Է�  
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Player/Input/PlayerInputMappingContext.PlayerInputMappingContext'"));
	if (InputMappingContextRef.Object)
	{
		defaultMappingContext = InputMappingContextRef.Object;
	}


	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionPressRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/Action/PressFireAction.PressFireAction'"));
	if (InputActionPressRef.Object)
	{
		ActPressAction = InputActionPressRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionReleaseRef(TEXT("/Script/EnhancedInput.InputAction'/Game/Player/Input/Action/ReleaseFireAction.ReleaseFireAction'"));
	if (InputActionReleaseRef.Object)
	{
		ActReleaseAction = InputActionReleaseRef.Object;
	}

	//Set Mesh and Anim BP-Kwakhyunbin
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/Player/TestAsset/Animation/Sword_And_Shield.Sword_And_Shield'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	//Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprints/Player/Test/ABP_PlayerAnimInstance.ABP_PlayerAnimInstance_C'"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FClassFinder<ADRRWeaponBase> WeaponClassRef(TEXT("/Game/Blueprints/Weapon/BP_Weapon2.BP_Weapon2_C"));
		//CLog::Log(WeaponClassRef.Object);
	if (WeaponClassRef.Class)
	{
		Weapon = WeaponClassRef.Class;

		
	}

}

void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	CLog::Log("SetupPlayerInputComponent");
	//���� �Է� �ý��� ���
	// �Է� �������ؽ�Ʈ���� �׼ǰ� �Լ� ����

	//����ȯ: �ֽ� Ʈ����. CastChecked�� ����ȯ�� ����� ����� Ȯ��
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ActPressAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::WeaponAttackPress);
	enhancedInputComponent->BindAction(ActReleaseAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::WeaponAttackRelaease);

	//���� ���ý�Ʈ�� ��Ʈ�ѷ��� �����ؾ���




}

void APlayerCharacterBase::BeginPlay()
{
	//SetWeapon(Weapon);


	CLog::Log("SetMappingContext");
	//���� ���ؽ�Ʈ�� ��Ʈ�ѷ��� �����ϴ� �۾�
	if (GetController()!=nullptr)
	{
		APlayerController* playerController = CastChecked<APlayerController>(GetController());

		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		if (nullptr != subsystem)
		{
			//���� ���ý�Ʈ���� ���� ����
			subsystem->ClearAllMappings();
			if (defaultMappingContext)
			{
				//���� ���ؽ�Ʈ ��Ʈ�ѷ��� ����. removeMappingContext�� ����� �ٸ��� �߰��� ���� ����
				subsystem->AddMappingContext(defaultMappingContext, 0);
			}

		}
	}
	
}

void APlayerCharacterBase::SetWeapon(TSubclassOf<class ADRRWeaponBase> NewWeapon)
{
	Weapon = NewWeapon;

	//WeaponObject = NewObject<ADRRWeaponBase>(Weapon);

	
}

void APlayerCharacterBase::WeaponAttackPress()
{
	CLog::Log("WeaponAttackPress");
	auto Temp = Cast<IDRRActableInterface>(Cast<ADRRWeaponBase>(Weapon->GetDefaultObject())->GetFirstAct());
	if (Temp)
	{
		
		ActComponent->Act(Temp);
	}
}

void APlayerCharacterBase::WeaponAttackRelaease()
{
	CLog::Log("WeaponAttackRelaease");
	auto Temp = Cast<IDRRActableInterface>(Cast<ADRRWeaponBase>(Weapon->GetDefaultObject())->GetFirstAct());
	if (Temp)
	{

		ActComponent->ActRelease(Temp);
	}
}


