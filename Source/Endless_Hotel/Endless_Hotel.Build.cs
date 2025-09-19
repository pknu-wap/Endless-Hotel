// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Endless_Hotel : ModuleRules
{
	public Endless_Hotel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "GameplayTasks",
            "GameplayTags",
            "GameplayAbilities",
            "MovieScene",
            "LevelSequence",
            "NavigationSystem",
            "UMG",
            "Niagara",
            "AdvancedWidgets"
        });

        PrivateIncludePaths.Add("Endless_Hotel");
        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}