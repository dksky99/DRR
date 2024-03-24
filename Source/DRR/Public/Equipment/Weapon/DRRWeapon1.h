// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/Weapon/DRRWeaponBase.h"
#include "DRRWeapon1.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API ADRRWeapon1 : public ADRRWeaponBase
{
	GENERATED_BODY()
public:
	virtual TArray<FOnActFuncDelegate> GetActFunc() override;
	virtual FOnActFuncDelegate GetBeginActFunc() override;
protected:

	virtual void BeginFunc() override;
private:
	void Func1();
	void Func2();
	void Func3();


};
