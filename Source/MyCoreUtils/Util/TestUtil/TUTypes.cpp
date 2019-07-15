#include "TUTypes.h"
#include "TUTypesLib.h"
#include "Util\Core\LogUtilLib.h"

void FTUConfig::SetFlags(ETUFlags const InFlagMask)
{
	UTUTypesLib::LogTUFlags(Flags);
	Flags |= InFlagMask;
	M_LOG(TEXT("New flags:"));
	UTUTypesLib::LogTUFlags(Flags);
}

void FTUConfig::UnsetFlags(ETUFlags const InFlagMask)
{
	UTUTypesLib::LogTUFlags(Flags);
	Flags &= ~InFlagMask;
	M_LOG(TEXT("New flags:"));
	UTUTypesLib::LogTUFlags(Flags);
}

bool FTUConfig::HasAnyFlags(ETUFlags const InFlagMask) const
{
	return ((Flags & InFlagMask) != ETUFlags::None);
}

bool FTUConfig::HasAllFlags(ETUFlags const InFlagMask) const
{
	return ((Flags & InFlagMask) != ETUFlags::None);
}
