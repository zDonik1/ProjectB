// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBTarget : TargetRules
{
	public ProjectBTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProjectB");
	}
}
