#include "TUTypes.h"
#include "TUTypesLib.h"
#include "Util\Core\LogUtilLib.h"

void FTUConfig::SetFlags(ETUFlags const InFlagMask)
{
	UTUTypesLib::LogTUFlags(GetFlags());
	Flags |= static_cast<uint8>(InFlagMask);
	M_LOG(TEXT("New flags:"));
	UTUTypesLib::LogTUFlags(GetFlags());
}

void FTUConfig::UnsetFlags(ETUFlags const InFlagMask)
{
	UTUTypesLib::LogTUFlags(GetFlags());
	Flags &= static_cast<uint8>(~InFlagMask);
	M_LOG(TEXT("New flags:"));
	UTUTypesLib::LogTUFlags(GetFlags());
}

bool FTUConfig::HasAnyFlags(ETUFlags const InFlagMask) const
{
	return ((GetFlags() & InFlagMask) != ETUFlags::None);
}

bool FTUConfig::HasAllFlags(ETUFlags const InFlagMask) const
{
	return ((GetFlags() & InFlagMask) != ETUFlags::None);
}
