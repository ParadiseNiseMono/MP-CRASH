// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MP_CRASH : ModuleRules
{
	public MP_CRASH(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MP_CRASH",
			"MP_CRASH/Variant_Platforming",
			"MP_CRASH/Variant_Platforming/Animation",
			"MP_CRASH/Variant_Combat",
			"MP_CRASH/Variant_Combat/AI",
			"MP_CRASH/Variant_Combat/Animation",
			"MP_CRASH/Variant_Combat/Gameplay",
			"MP_CRASH/Variant_Combat/Interfaces",
			"MP_CRASH/Variant_Combat/UI",
			"MP_CRASH/Variant_SideScrolling",
			"MP_CRASH/Variant_SideScrolling/AI",
			"MP_CRASH/Variant_SideScrolling/Gameplay",
			"MP_CRASH/Variant_SideScrolling/Interfaces",
			"MP_CRASH/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
