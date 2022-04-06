// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleofDronesServerTarget : TargetRules
{
	public BattleofDronesServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BattleofDrones" } );

		DisablePlugins.Add("WMFMediaPlayer");
		DisablePlugins.Add("WindowsMoviePlayer");
		DisablePlugins.Add("MediaFoundationMediaPlayer");
	}
}
