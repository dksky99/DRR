
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRRActComponent.generated.h"



//매개변수가 하나인 델리게이트 생성

DECLARE_DELEGATE_OneParam(FOnActDelegate, class IDRRActableInterface* );

DECLARE_DELEGATE(FOnDoActDelegate);
USTRUCT(BlueprintType)
struct FOnActDelegateWrapper
{
	GENERATED_BODY()

	FOnActDelegateWrapper() {}
	FOnActDelegateWrapper(const FOnActDelegate& InActDelegate) :ActDelegate(InActDelegate) {}

	FOnActDelegate ActDelegate;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRR_API UDRRActComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDRRActComponent();

	void Act(class IDRRActableInterface* Actable); 
	void ActRelease(class IDRRActableInterface* Actable);

	
	void ActFunc();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AfterAct();

	void ShortShot( IDRRActableInterface* Target);
	void Charging(  IDRRActableInterface* Target);
	void Casting(   IDRRActableInterface* Target);
	void Combo(     IDRRActableInterface* Target);


	void BeginAct();
	void CheckActTimer();
	void CheckAct();
	void EndAct(UAnimMontage* targetMontage, bool isInteruped);

private:
	void EraseAct();
	


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:


	UPROPERTY()
	TArray<FOnActDelegateWrapper> ActActions;
	
	class DRRAct* Actor;	

	TObjectPtr<class UAnimMontage> ActionMontage;
	struct FTimerHandle ActTimerHandle;
	bool hasNextAct;

		
};

