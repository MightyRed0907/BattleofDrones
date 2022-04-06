// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayfabGsdkGameInstance.h"
#include "PlayfabGSDK.h"
#include "GSDKUtils.h"

#if !UE_SERVER
DEFINE_LOG_CATEGORY(LogPlayFabGSDK);
#endif

void UPlayfabGsdkGameInstance::Init()
{
    if (IsDedicatedServerInstance() == true)
    {
        FOnGSDKShutdown_Dyn OnGsdkShutdown;
        OnGsdkShutdown.BindDynamic(this, &UPlayfabGsdkGameInstance::OnGSDKShutdown);
        FOnGSDKHealthCheck_Dyn OnGsdkHealthCheck;
        OnGsdkHealthCheck.BindDynamic(this, &UPlayfabGsdkGameInstance::OnGSDKHealthCheck);
        FOnGSDKServerActive_Dyn OnGSDKServerActive;
        OnGSDKServerActive.BindDynamic(this, &UPlayfabGsdkGameInstance::OnGSDKServerActive);
        FOnGSDKReadyForPlayers_Dyn OnGSDKReadyForPlayers;
        OnGSDKReadyForPlayers.BindDynamic(this, &UPlayfabGsdkGameInstance::OnGSDKReadyForPlayers);

        UGSDKUtils::RegisterGSDKShutdownDelegate(OnGsdkShutdown);
        UGSDKUtils::RegisterGSDKHealthCheckDelegate(OnGsdkHealthCheck);
        UGSDKUtils::RegisterGSDKServerActiveDelegate(OnGSDKServerActive);
        UGSDKUtils::RegisterGSDKReadyForPlayers(OnGSDKReadyForPlayers);
    }

#if UE_SERVER
    UGSDKUtils::SetDefaultServerHostPort();
#endif
}

void UPlayfabGsdkGameInstance::OnStart()
{
    UE_LOG(LogPlayFabGSDK, Warning, TEXT("Reached onStart!"));
    UGSDKUtils::ReadyForPlayers();
}

void UPlayfabGsdkGameInstance::OnGSDKShutdown()
{
    UE_LOG(LogPlayFabGSDK, Warning, TEXT("Shutdown!"));
    FPlatformMisc::RequestExit(false);
}

bool UPlayfabGsdkGameInstance::OnGSDKHealthCheck()
{
    UE_LOG(LogPlayFabGSDK, Warning, TEXT("Healthy!"));
    return true;
}

void UPlayfabGsdkGameInstance::OnGSDKServerActive()
{
    /**
     * Server is transitioning to an active state.
     * Optional: Add in the implementation any code that is needed for the game server when
     * this transition occurs.
     */
    UE_LOG(LogPlayFabGSDK, Warning, TEXT("Active!"));
}

void UPlayfabGsdkGameInstance::OnGSDKReadyForPlayers()
{
    /**
     * Server is transitioning to a StandBy state. Game initialization is complete and the game is ready
     * to accept players.
     * Optional: Add in the implementation any code that is needed for the game server before
     * initialization completes.
     */
    UE_LOG(LogPlayFabGSDK, Warning, TEXT("Finished Initialization - Moving to StandBy!"));
}
