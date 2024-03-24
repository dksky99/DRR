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

#include "Utilities/UtilityList.h"

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

	CLog::Log("Act");
	if (Actor == nullptr)
	{

		CLog::Log("Begin");
		EraseAct();
		ActActions[(uint8)Actable->GetActData()->Type].ActDelegate.ExecuteIfBound(Actable);
		BeginAct();
		return;
	}
	//같은 명령이라면 같은 행동선에서 다른 행동. 아니라면 새로운 행동
	if (Actor->GetCurAct()->ActionName.Equals(Actable->GetActData()->ActionName))
	{

		CLog::Log("Second");
		AfterAct();

		return;
	}

}

void UDRRActComponent::ActRelease(IDRRActableInterface* Actable)
{
	if (Actor == nullptr)
	{
		return;
	}
	Actor->ActRelease();
}

void UDRRActComponent::ActFunc()
{
	CLog::Log("ActFunc");

	if (Actor == nullptr)
	{
		return;
	}

	Actor->DoAct();

}


void UDRRActComponent::ShortShot( IDRRActableInterface* Target)
{
	CLog::Log("ShortShot");
	Actor = new DRRShortShotAct(Target);
	
}

void UDRRActComponent::Charging(IDRRActableInterface* Target)
{
	CLog::Log("Charging");
	Actor = new DRRChargeAct(Target);
}

void UDRRActComponent::Casting(IDRRActableInterface* Target)
{
	CLog::Log("Casting");
	Actor = new DRRCastAct(Target);
	
}

void UDRRActComponent::Combo(IDRRActableInterface* Target)
{
	CLog::Log("Combo");
	Actor = new DRRComboAct(Target);

}

void UDRRActComponent::BeginAct()
{

	CLog::Log("UDRRActComponent::BeginAct");

	UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
	//몽타주 실행
	animInstance->Montage_Play(Actor->GetCurAct()->ActionMontage);


	Actor->DoBeginAct();
	//몽타주가 끝날떄 호출되는델리게이트
	FOnMontageEnded endDelegate;
	//델리게이트 바인딩
	endDelegate.BindUObject(this, &UDRRActComponent::EndAct);
	//애님인스턴스가 엔드델리게이트로 사용할 델리게이트 설정
	animInstance->Montage_SetEndDelegate(endDelegate, Actor->GetCurAct()->ActionMontage);
	hasNextAct = Actor->BeginAct();
	//콤보체크타이머 세팅
	CheckActTimer();
}

void UDRRActComponent::CheckActTimer()
{
	float NextCheckTime = Actor->GetNextTime();
	if (NextCheckTime > 0.0f)
	{


		//타이머 설정: (타임핸들러, 객체, 실행할 함수,지연시간, 루프 여부)
		GetWorld()->GetTimerManager().SetTimer(ActTimerHandle, this, &UDRRActComponent::CheckAct, NextCheckTime, false);
	}
}

void UDRRActComponent::CheckAct()
{
	//콤보타이머 핸들 비활성화
	ActTimerHandle.Invalidate();
	CLog::Log("UDRRActComponent::CheckAct");


	if (hasNextAct)
	{
		CLog::Log(hasNextAct);
		
		uint8 curActCount=Actor->NextAct();

		ActFunc();
		UAnimInstance* animInstance = Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance();
		//실행할 색션이름 지정 포맷 FString 앞에는 *을 꼭붙여줘야함
		FName nextSectionName(Actor->GetMontgeSectionName());
		CLog::Log(nextSectionName.ToString());
			//몽타주 실행
		//몽타주의 특정 이름의 액션 실행 
		animInstance->Montage_JumpToSection(nextSectionName, Actor->GetCurAct()->ActionMontage);
		
		//콤보타이머 활성화
		CheckActTimer();
		hasNextAct = Actor->NextReset();
	}

}

void UDRRActComponent::EndAct(UAnimMontage* targetMontage, bool isInteruped)
{
	CLog::Log("UDRRActComponent::EndAct");
	EraseAct();

}

void UDRRActComponent::EraseAct()
{
	delete(Actor);
}



