// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBEditorTarget : TargetRules
{
	public ProjectBEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProjectB");
	}
}
