#pragma once

namespace MetaModule
{

// SD card bring-up test: raw read speed, mount FatFS ("1:"), list the root directory,
// then write/verify/delete a test file. Prints the results to the console.
void sd_card_test();

// Call periodically: prints when a card is inserted or removed
void sd_card_poll();

} // namespace MetaModule
