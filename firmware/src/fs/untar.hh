#pragma once
#include <cstddef>
#include <span>

namespace Tar
{

struct tar_t {
	char original_name[100]; // original filenme; only availible when writing into a tar
	unsigned int begin;		 // location of data in file (including metadata)
	union {
		union {
			// Pre-POSIX.1-1988 format
			struct {
				char name[100]; // file name
				char mode[8];	// permissions
				char uid[8];	// user id (octal)
				char gid[8];	// group id (octal)
				char size[12];	// size (octal)
				char mtime[12]; // modification time (octal)
				char check
					[8]; // sum of unsigned characters in block, with spaces in the check field while calculation is done (octal)
				char link;			 // link indicator
				char link_name[100]; // name of linked file
			};

			// UStar format (POSIX IEEE P1003.1)
			struct {
				char old[156];			  // first 156 octets of Pre-POSIX.1-1988 format
				char type;				  // file type
				char also_link_name[100]; // name of linked file
				char ustar[8];			  // ustar\000
				char owner[32];			  // user name (string)
				char group[32];			  // group name (string)
				char major[8];			  // device major number
				char minor[8];			  // device minor number
				char prefix[155];
			};
		};

		char block[512]; // raw memory (500 octets of actual data, padded to 1 block)
	};

	tar_t *next;
};

bool read(std::span<char> data, tar_t **archive);
void tar_free(tar_t *archive);
int extract(std::span<char> data, tar_t *archive, size_t filecount, const char *files[]);

void print_info(std::span<char> data);

} // namespace Tar
