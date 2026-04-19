// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MPCRASH : ModuleRules
{
	public MPCRASH(ReadOnlyTargetRules Target) : base(Target)
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
			"MPCRASH",
			"MPCRASH/Variant_Platforming",
			"MPCRASH/Variant_Platforming/Animation",
			"MPCRASH/Variant_Combat",
			"MPCRASH/Variant_Combat/AI",
			"MPCRASH/Variant_Combat/Animation",
			"MPCRASH/Variant_Combat/Gameplay",
			"MPCRASH/Variant_Combat/Interfaces",
			"MPCRASH/Variant_Combat/UI",
			"MPCRASH/Variant_SideScrolling",
			"MPCRASH/Variant_SideScrolling/AI",
			"MPCRASH/Variant_SideScrolling/Gameplay",
			"MPCRASH/Variant_SideScrolling/Interfaces",
			"MPCRASH/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
