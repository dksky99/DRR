// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "CharacterBase/DRRActComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	//추가사항3
	ActComponent= CreateDefaultSubobject<UDRRActComponent>(TEXT("Act"));

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

//추가사항4
void ACharacterBase::Act()
{
	ActComponent->ActFunc();

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

