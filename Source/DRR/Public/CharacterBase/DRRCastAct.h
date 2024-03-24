// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRRAct.h"


/**
 * 
 */
class DRR_API DRRCastAct : public DRRAct
{
public:

	DRRCastAct(IDRRActableInterface* Target);
	~DRRCastAct();
	virtual bool BeginAct() override;
	virtual bool NextReset() override;
	virtual FName GetMontgeSectionName() override;
protected:
	virtual void EndAct() override;
	virtual bool AfterAct() override;
	
protected:


};
