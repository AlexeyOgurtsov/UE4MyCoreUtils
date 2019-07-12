#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUVisibleActor.h"
#include "TemplActor.generated.h"

UCLASS()
class ATemplActor : public ATUVisibleActor
{
	GENERATED_BODY()

public:
	ATemplActor();

	virtual void BeginPlay() override;
};
