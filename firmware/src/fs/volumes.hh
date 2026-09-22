#pragma once
namespace MetaModule
{
enum class Volume {
	USB = 0,
	SDCard = 1,
	RamDisk = 2,
	NorFlash = 3,

	MaxVolumes = 4,

	// Not a patch volume -- a FatFS drive number for the developer-mode USB
	// drive, which never appears in the patch browser or the file storage
	// proxy. Numbered above MaxVolumes so the bounds checks there exclude it.
	DevDrive = 5,
};
}
