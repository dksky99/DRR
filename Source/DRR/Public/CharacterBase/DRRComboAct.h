// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRAct.h"


/**
 * 
 */
class DRR_API DRRComboAct : public DRRAct
{
public:

	DRRComboAct(IDRRActableInterface* Target);
	~DRRComboAct();
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual FName GetMontgeSectionName() override;
protected:
	virtual void EndAct() override;
	virtual bool AfterAct() override;
	
protected:

};

