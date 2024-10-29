#pragma once
namespace MetaModule
{

struct Hardware {
	struct AudioExpCalibrationReader {
		bool read(unsigned addr, auto data) {
			return true;
		}
		bool read(auto data, unsigned addr) {
			return true;
		}
		bool write(auto data, unsigned addr) {
			return true;
		}
	};
	static inline AudioExpCalibrationReader codec_ext_memory;
};

} // namespace MetaModule
