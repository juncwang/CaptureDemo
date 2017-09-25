// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class C_FSGameTarget : TargetRules
{
	public C_FSGameTarget(TargetInfo Target)
	{
		Type = TargetType.Game;
    }

	//
	// TargetRules interface.
	//

	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
        //ref List<string> PublicDependencyModuleNames
        )
	{
		OutExtraModuleNames.AddRange( new string[] { "C_FSGame" } );
        //PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent" });
    }
}
