// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Escape_Room : ModuleRules
{
	public Escape_Room(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "Escape_Room" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "NavigationSystem" , "MediaAssets"});
	}
}
