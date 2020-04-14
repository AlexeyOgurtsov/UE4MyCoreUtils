#include "MyProjectileBase.h"
#include "MyDefaultProjectile.generated.h"

UCLASS(BlueprintType)
class AMyDefaultProjectile : public AMyProjectileBase
{
	GENERATED_BODY()

public:
	AMyDefaultProjectile();
};
