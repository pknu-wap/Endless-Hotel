// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Endless_Hotel : ModuleRules
{
	public Endless_Hotel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
