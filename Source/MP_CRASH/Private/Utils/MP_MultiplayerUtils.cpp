// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Utils/MP_MultiplayerUtils.h"

void UMP_MultiplayerUtils::PrintLocalNetRole(AActor* Actor)
{
	if (Actor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] Has Authority."), *Actor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor [%s] does not have Authority."), *Actor->GetName());
	}

	switch (Actor->GetLocalRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("ROLE_None."));
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("ROLE_SimulatedProxy."));
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("ROLE_AutonomousProxy."));
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("ROLE_Authority."));
		break;
	case ROLE_MAX:
		UE_LOG(LogTemp, Warning, TEXT("ROLE_MAX."));
		break;
	default:
		break;
	}
}

void UMP_MultiplayerUtils::PrintRemoteNetRole(AActor* Actor)
{
	switch (Actor->GetRemoteRole())
	{
	case ROLE_None:
		UE_LOG(LogTemp, Warning, TEXT("Remote ROLE_None."));
		break;
	case ROLE_SimulatedProxy:
		UE_LOG(LogTemp, Warning, TEXT("Remote ROLE_SimulatedProxy."));
		break;
	case ROLE_AutonomousProxy:
		UE_LOG(LogTemp, Warning, TEXT("Remote ROLE_AutonomousProxy."));
		break;
	case ROLE_Authority:
		UE_LOG(LogTemp, Warning, TEXT("Remote ROLE_Authority."));
		break;
	case ROLE_MAX:
		UE_LOG(LogTemp, Warning, TEXT("Remote ROLE_MAX."));
		break;
	default:
		break;
	}
}
