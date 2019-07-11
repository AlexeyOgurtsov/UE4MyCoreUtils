#pragma once

#include "Math/Rotator.h"
#include "Math/Vector.h"

namespace VisibleActorConfig
{
	namespace Default
	{
		// ~Mesh Begin
		constexpr const TCHAR* MESH_ASSET_PATH = TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'");
		constexpr float MESH_BOUNDING_CUBE_SIDE = 100.0F;
		const FVector MESH_PIVOT_POINT_ACTOR_SPACE_LOCATION { MESH_BOUNDING_CUBE_SIDE/2.0F, MESH_BOUNDING_CUBE_SIDE/2.0F, 0.0F };
		const FVector MESH_REAL_CENTER_ACTOR_SPACE_LOCATION { 0, 0, MESH_BOUNDING_CUBE_SIDE/2.0F };
		// ~Mesh End

		// ~ProxSphere Begin
		constexpr float PROX_SPHERE_RADIUS_EXTRA = 50.0F;
		constexpr float PROX_SPHERE_RADIUS = MESH_BOUNDING_CUBE_SIDE/2.0F + PROX_SPHERE_RADIUS_EXTRA;
		// ~ProxSphere End

		// ~SpringArm Begin
		constexpr float SPRINGARM_TARGET_ARM_LENGTH_EXTRA = 300.0F;
		constexpr float SPRINGARM_TARGET_ARM_LENGTH = MESH_BOUNDING_CUBE_SIDE/2.0F + SPRINGARM_TARGET_ARM_LENGTH_EXTRA;
		constexpr bool SPRINGARM_ENABLE_CAMERA_LAG = false;
		constexpr float SPRINGARM_CAMERA_LAG_SPEED = 3.0F;
		const FRotator SPRINGARM_RELATIVE_ROTATION { -25.0F, 0.0F, 0.0F };
		const FVector SPRINGARM_RELATIVE_LOCATION { 0, 0, MESH_BOUNDING_CUBE_SIDE/2.0F };
		// ~SpringArm End

	}
}
