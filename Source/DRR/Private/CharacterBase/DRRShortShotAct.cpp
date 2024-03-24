// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase/DRRShortShotAct.h"
#include "Interface/DRRActableInterface.h"

DRRShortShotAct::DRRShortShotAct(IDRRActableInterface* Target):DRRAct(Target)
{
    
}

DRRShortShotAct::~DRRShortShotAct()
{
}


bool DRRShortShotAct::BeginAct()
{
    return false;
}

bool DRRShortShotAct::NextReset()
{
    return false;
}
float DRRShortShotAct::GetNextTime()
{
    return CurAct->EffectiveFrameCount[0] / CurAct->FrameRate;
}



void DRRShortShotAct::EndAct()
{
}

bool DRRShortShotAct::AfterAct()
{
    return true;
}
