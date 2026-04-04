// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TwistedShadows : ModuleRules
{
	public TwistedShadows(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate", "MassEntity","GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TwistedShadows",
			"TwistedShadows/Variant_Strategy",
			"TwistedShadows/Variant_Strategy/UI",
			"TwistedShadows/Variant_TwinStick",
			"TwistedShadows/Variant_TwinStick/AI",
			"TwistedShadows/Variant_TwinStick/Gameplay",
			"TwistedShadows/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
