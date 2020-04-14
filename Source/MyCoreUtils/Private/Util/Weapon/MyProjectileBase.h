#pragma once

#include "Util/TestUtil/TUProjectileActor.h"
#include "MyProjectileBase.generated.h"

UCLASS()
class AMyProjectileBase : public ATUProjectileActor
{
	GENERATED_BODY()

public:
	/**
	* This function is to be called when launching any projectile
	* (right after spawned!)
	*/
	virtual void Launch();
};
