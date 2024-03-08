// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CharacterBase/CharacterControllDataAsset.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ACharacterPlayer::ACharacterPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->bUsePawnControlRotation = true;
	//Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetCharacterControl(ECharacterControlType::Quater);
}

void ACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//향상된 입력 시스템 사용
	//입력매핑컨텍스트에서 액션과 함수
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked <UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(QuaterMoveAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::QuaterMove);
	EnhancedInputComponent->BindAction(ShoulderMoveAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(ShoulderLookAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(ChangeControlAction, ETriggerEvent::Triggered, this, &ACharacterPlayer::ChangeControl);

}

void ACharacterPlayer::SetCharacterControlData(const UCharacterControlDataAsset* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	//Input
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (nullptr != Subsystem)
	{
		Subsystem->ClearAllMappings();
		if (CharacterControlData->InputMappingContext)
		{
			Subsystem->AddMappingContext(CharacterControlData->InputMappingContext, 0);
		}
		//Subsystem->RemoveMappingContext(DefaultMappingContext);
	}

	//Camera
	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;

}




void ACharacterPlayer::QuaterMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	float MovementVectorsizeSquared = MovementVector.SquaredLength();
	if (MovementVectorsizeSquared > 1.0f)
	{
		//크기를 1로 고정
		MovementVector.Normalize();
		MovementVectorsizeSquared = 1.0f;
	}
	else{}

	FVector MoveDirection = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	GetController()->SetControlRotation(FRotationMatrix::MakeFromX(MoveDirection).Rotator());
	AddMovementInput(MoveDirection, MovementVectorsizeSquared);
}

void ACharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ACharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ACharacterPlayer::ChangeControl()
{
	//현재 캐릭터 컨트롤 타입이 쿼터이면 숄더로 숄더면 쿼터로 전환
	if (CurrentCharacterControlType == ECharacterControlType::Quater)
	{
		CurrentCharacterControlType = ECharacterControlType::Shoulder;
	}
	else if (CurrentCharacterControlType == ECharacterControlType::Shoulder)
	{
		CurrentCharacterControlType = ECharacterControlType::Quater;
	}

	SetCharacterControl(CurrentCharacterControlType);
}

void ACharacterPlayer::SetCharacterControl(ECharacterControlType ControlType)
{
	UCharacterControlDataAsset* NewCharacterControlData = CharacterControlManager[ControlType];
	SetCharacterControlData(NewCharacterControlData);
}

