#include "central_data.hh"

std::unique_ptr<CentralData> centralData;

void initializeCentralData() {
	centralData = std::make_unique<CentralData>();
}