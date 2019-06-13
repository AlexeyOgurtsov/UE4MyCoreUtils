// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyCoreUtilsEditorTarget_NoPrecomp : MyCoreUtilsEditorTarget
{
	public MyCoreUtilsEditorTarget_NoPrecomp(TargetInfo Target) : base(Target)
	{
		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
