// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRActComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "DataAsset/DA_ActData.h"
#include "DataAsset/DA_ChargeActData.h"
#include "DataAsset/DA_CastActData.h"
#include "DataAsset/DA_ComboActData.h"
#include "DataAsset/DA_ShortShotActData.h"
#include "Interface/DRRActableInterface.h"
#include "CharacterBase/DRRShortShotAct.h"
#include "CharacterBase/DRRCastAct.h"
#include "CharacterBase/DRRChargeAct.h"
#include "CharacterBase/DRRComboAct.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
// Sets default values for this component's properties
UDRRActComponent::UDRRActComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Actor = nullptr;

	//Take Item Section
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::ShortShot)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Charging)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Casting)));
	ActActions.Add(FOnActDelegateWrapper(FOnActDelegate::CreateUObject(this, &UDRRActComponent::Combo)));



	// ...
}


// Called when the game starts
void UDRRActComponent::BeginPlay()
{
	Super::BeginPlay();

	
}



void UDRRActComponent::AfterAct()
{
	hasNextAct= Actor->AfterAct();
}


// Called every frame
void UDRRActComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDRRActComponent::Act(IDRRActableInterface* Actable)
{
	if (Actor == nullptr)
	{
		EraseAct();
		ActActions[(uint8)Actable->GetActData()->Type].ActDelegate.ExecuteIfBound(Actable);
		BeginAct();
		return;
	}
	//���� ����̶�� ���� �ൿ������ �ٸ� �ൿ. �ƴ϶�� ���ο� �ൿ
	if (Actor->GetCurAct()->ActionName.Equals(Actable->GetActData()->ActionName))
	{
		AfterAct();

		return;
	}

}

void UDRRActComponent::ActFunc()
{

	if (Actor == nullptr)
	{
		return;
	}

	Actor->DoAct();

}


void UDRRActComponent::ShortShot( IDRRActableInterface* Target)
{
	Actor = new DRRShortShotAct(Target);
	
}

void UDRRActComponent::Charging(IDRRActableInterface* Target)
{
	Actor = new DRRChargeAct(Target);
}

void UDRRActComponent::Casting(IDRRActableInterface* Target)
{
	Actor = new DRRCastAct(Target);
	
}

void UDRRActComponent::Combo(IDRRActableInterface* Target)
{
	Actor = new DRRComboAct(Target);

}

void UDRRActComponent::BeginAct()
{
	
	UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
	//��Ÿ�� ����
	animInstance->Montage_Play(Actor->GetCurAct()->ActionMontage);
	//��Ÿ�ְ� ������ ȣ��Ǵµ�������Ʈ
	FOnMontageEnded endDelegate;
	//��������Ʈ ���ε�
	endDelegate.BindUObject(this, &UDRRActComponent::EndAct);
	//�ִ��ν��Ͻ��� ���嵨������Ʈ�� ����� ��������Ʈ ����
	animInstance->Montage_SetEndDelegate(endDelegate, Actor->GetCurAct()->ActionMontage);
	hasNextAct = Actor->BeginAct();
	//�޺�üũŸ�̸� ����
	CheckActTimer();
}

void UDRRActComponent::CheckActTimer()
{
	float NextCheckTime = Actor->GetNextTime();
	if (NextCheckTime > 0.0f)
	{


		//Ÿ�̸� ����: (Ÿ���ڵ鷯, ��ü, ������ �Լ�,�����ð�, ���� ����)
		GetWorld()->GetTimerManager().SetTimer(ActTimerHandle, this, &UDRRActComponent::CheckAct, NextCheckTime, false);
	}
}

void UDRRActComponent::CheckAct()
{
	//�޺�Ÿ�̸� �ڵ� ��Ȱ��ȭ
	ActTimerHandle.Invalidate();


	if (hasNextAct)
	{
		uint8 curActCount=Actor->NextAct();

		UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
		FString CombineString = Actor->GetCurAct()->MontageSectionPrefix + FString::FromInt(curActCount);
		//������ �����̸� ���� ���� FString �տ��� *�� ���ٿ������
		FName nextSectionName(*CombineString);
			//��Ÿ�� ����
		//��Ÿ���� Ư�� �̸��� �׼� ���� 
		animInstance->Montage_JumpToSection(nextSectionName, Actor->GetCurAct()->ActionMontage);
		
		//�޺�Ÿ�̸� Ȱ��ȭ
		CheckActTimer();
		hasNextAct = Actor->NextReset();
	}

}

void UDRRActComponent::EndAct(UAnimMontage* targetMontage, bool isInteruped)
{
	EraseAct();

}

void UDRRActComponent::EraseAct()
{
	delete(Actor);
}



