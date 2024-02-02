#include "info/Tapo_info.hh"
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"

#include "tapo/multitap_delay.hh"
#include "tapo/ui.hh"

namespace MetaModule
{

class TapoCore : public SmartCoreProcessor<TapoInfo> {
	using Info = TapoInfo;
	using ThisCore = TapoCore;
	using enum Info::Elem;

public:
	TapoCore() : audioBufferFillCount(0)
	{
		buffer = std::make_unique<Buffer_t>();
		delay.Init((short*)buffer->data(), buffer->size()/sizeof(short) / 2);

		ui.Init(&delay, &parameters);

		std::fill(audioBufferTX.begin(), audioBufferTX.end(), ShortFrame{0,0});
	}

	void update() override {

		ui.Poll();
		ui.DoEvents();
		delay.Poll();

		if (audioBufferFillCount == BlockSize)
		{
			ui.ReadParameters();
			delay.Process(&parameters, audioBufferRX.data(), audioBufferTX.data());

			audioBufferFillCount = 0;
		}

		packUnpackBlockBuffers();
		audioBufferFillCount++;
	}

	void set_samplerate(float sr) override {
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	void packUnpackBlockBuffers()
	{
		auto monoInput = int16_t(getInput<AudioIn>().value_or(0) * 32767.0 / 11.0);
		audioBufferRX[audioBufferFillCount] = {monoInput, monoInput};

		setOutput<AudioOut1Out>(float(audioBufferTX[audioBufferFillCount].l) / 32768.0 * 17.0);
		setOutput<AudioOut2Out>(float(audioBufferTX[audioBufferFillCount].r) / 32768.0 * 17.0);
	}

private:
	static constexpr std::size_t BufferSizeInBytes = 0x02000000;
	using Buffer_t = std::array<uint8_t,BufferSizeInBytes>;

	std::unique_ptr<Buffer_t> buffer;

	MultitapDelay delay;
	Parameters parameters;
	Ui ui;
	

	static constexpr std::size_t BlockSize = kBlockSize;
	std::array<ShortFrame,BlockSize> audioBufferRX;
	std::array<ShortFrame,BlockSize> audioBufferTX;
	std::size_t audioBufferFillCount;
};

} // namespace MetaModule

