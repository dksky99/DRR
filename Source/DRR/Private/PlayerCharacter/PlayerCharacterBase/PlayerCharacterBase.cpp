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

#include "Equipment/Weapon/DRRWeapon1.h"

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


	//입력  
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
	//향상된 입력 시스템 사용
	// 입력 매핑컨텍스트에서 액션과 함수 연결

	//형변환: 최신 트랜드. CastChecked로 형변환이 제대로 됬는지 확인
	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInputComponent->BindAction(ActPressAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::WeaponAttackPress);
	enhancedInputComponent->BindAction(ActReleaseAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::WeaponAttackRelaease);

	//매핑 컨택스트를 컨트롤러와 연결해야함




}

void APlayerCharacterBase::BeginPlay()
{
	//SetWeapon(Weapon);


	CLog::Log("SetMappingContext");
	//매핑 콘텍스트를 컨트롤러에 연결하는 작업
	APlayerController* playerController = CastChecked<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (nullptr != subsystem)
	{
		//매핑 컨택스트들을 전부 제거
		subsystem->ClearAllMappings();
		if (defaultMappingContext)
		{
			//매핑 콘텍스트 컨트롤러에 연결. removeMappingContext로 지우고 다른걸 추가할 수도 있음
			subsystem->AddMappingContext(defaultMappingContext, 0);
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
	ActComponent->Act(Cast<IDRRActableInterface>(Weapon->GetDefaultObject()));
}

void APlayerCharacterBase::WeaponAttackRelaease()
{
	CLog::Log("WeaponAttackRelaease");
	ActComponent->ActRelease(Cast<IDRRActableInterface>(Weapon->GetDefaultObject()));
}


