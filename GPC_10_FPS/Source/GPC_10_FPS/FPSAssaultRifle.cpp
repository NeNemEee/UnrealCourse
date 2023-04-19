// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAssaultRifle.h"

AFPSAssaultRifle::AFPSAssaultRifle()
{
	GunType = EFPSGunType::AssaultRifle;
}

bool AFPSAssaultRifle::Fire()
{
	return false;
}