#include "fxList.hpp"
#include "plugin.hpp"
#include "processors/audio_processor.hh"
#include "processors/tools/dcBlock.h"
#include "util/math.hh"

using namespace MathTools;

struct Dual_opener : Module {
	enum ParamIds {
		FILTER1TYPE_PARAM,
		FREQ1ROTARY_PARAM,
		FILTER2TYPE_PARAM,
		FREQ2ROTARY_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		FREQ1CV_INPUT,
		FREQ2CV_INPUT,
		Q1CV_INPUT,
		Q2CV_INPUT,
		IN1_INPUT,
		IN2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		ENUMS(FREQ1_LIGHT, 3),
		ENUMS(FREQ2_LIGHT, 3),
		ENUMS(QUALITY1_LIGHT, 3),
		ENUMS(QUALITY2_LIGHT, 3),
		NUM_LIGHTS
	};

	class ChannelParameters {
	public:
		float cvIn[2];
		int selectedParam = 0;
		float knobValue[2];

		void knobUpdate(float knobInput)
		{
			lastKnob[selectedParam] = currentKnob[selectedParam];
			currentKnob[selectedParam] = knobInput;
			if (currentKnob[selectedParam] != lastKnob[selectedParam])
				knobValue[selectedParam] = knobInput;
		}

		float finalValue(int paramNum)
		{
			return (constrain(cvIn[paramNum] / 5.0f + knobValue[paramNum], 0.0f, 1.0f));
		}

		void readToggle(int buttonInput)
		{
			lastToggle = currentToggle;
			currentToggle = buttonInput;

			if (currentToggle > lastToggle)
				selectedParam = !selectedParam;
		}

	private:
		float currentKnob[2];
		float lastKnob[2];
		int currentToggle;
		int lastToggle;
	};

	int previousLeftEffect;
	int previousRightEffect;
	int currentRightEffect = 0;
	int currentLeftEffect = 0;
	int leftEffect;
	int rightEffect;

	ChannelParameters channelParameters[2];

	FXList LfxList;
	FXList RfxList;

	AudioProcessor *Lfx;
	AudioProcessor *Rfx;

	DCBlock dcBlock[2];

	//Todo: share the list?

	Dual_opener()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(FILTER1TYPE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FREQ1ROTARY_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FILTER2TYPE_PARAM, 0.f, 1.f, 0.f, "");
		configParam(FREQ2ROTARY_PARAM, 0.f, 1.f, 0.f, "");
		last_samplerate = 0.F;

		currentLeftEffect = 0;
		currentRightEffect = 0;

		Lfx = LfxList[currentLeftEffect];
		Rfx = RfxList[currentRightEffect];
		previousLeftEffect = currentLeftEffect;
		previousRightEffect = currentRightEffect;
	}
	~Dual_opener()
	{
		// Todo: make this work to avoid memory leaks!
		// for (auto fx : LfxList)
		// 	delete fx;
		// for (auto fx : RfxList)
		// 	delete fx;
	}

	json_t *dataToJson() override
	{
		json_t *rootJ = json_object();
		json_object_set_new(rootJ, "Algorithm", json_integer(currentRightEffect));
		return rootJ;
	}

	void dataFromJson(json_t *rootJ) override
	{
		json_t *modeJ = json_object_get(rootJ, "Algorithm");
		if (modeJ)
			currentRightEffect = json_integer_value(modeJ);
	}

	void process_channel(AudioProcessor *fx, OutputIds out_id, InputIds in_id)
	{
		float inputSignal = inputs[in_id].getVoltage() / 5.0f;
		float in_v = fx->update(dcBlock->update(inputSignal));
		outputs[out_id].setVoltage(in_v * 5.0f);
	}

	void process(const ProcessArgs &args) override
	{
		if (args.sampleRate != last_samplerate) {
			last_samplerate = args.sampleRate;
			Lfx->set_samplerate(args.sampleRate);
			Rfx->set_samplerate(args.sampleRate);
		}

		channelParameters[0].readToggle(params[FILTER1TYPE_PARAM].getValue());
		channelParameters[1].readToggle(params[FILTER2TYPE_PARAM].getValue());

		lights[FREQ1_LIGHT + 1].setBrightness(!channelParameters[0].selectedParam);
		lights[QUALITY1_LIGHT + 1].setBrightness(channelParameters[0].selectedParam);

		lights[FREQ2_LIGHT + 1].setBrightness(!channelParameters[1].selectedParam);
		lights[QUALITY2_LIGHT + 1].setBrightness(channelParameters[1].selectedParam);

		//Todo: update params every new block?
		{
			if (currentRightEffect != previousRightEffect) {
				if (currentRightEffect < 5 && currentRightEffect >= 0) {
					Rfx = RfxList[currentRightEffect];
					Rfx->set_samplerate(args.sampleRate);
				}
				previousRightEffect = currentRightEffect;
			}

			if (currentLeftEffect != previousLeftEffect) {
				if (currentLeftEffect < 5 && currentLeftEffect >= 0) {
					Lfx = LfxList[currentLeftEffect];
					Lfx->set_samplerate(args.sampleRate);
				}
				previousLeftEffect = currentLeftEffect;
			}

			//Todo: param_freq += CV... bounds...
			channelParameters[0].cvIn[0] = inputs[FREQ1CV_INPUT].getVoltage() / 5.0f;
			channelParameters[0].cvIn[1] = inputs[Q1CV_INPUT].getVoltage() / 5.0f;

			channelParameters[1].cvIn[0] = inputs[FREQ2CV_INPUT].getVoltage() / 5.0f;
			channelParameters[1].cvIn[1] = inputs[Q2CV_INPUT].getVoltage() / 5.0f;

			channelParameters[0].knobUpdate(params[FREQ1ROTARY_PARAM].getValue());
			channelParameters[1].knobUpdate(params[FREQ2ROTARY_PARAM].getValue());

			Lfx->set_param(0, channelParameters[0].finalValue(0));
			Lfx->set_param(1, channelParameters[0].finalValue(1));

			Rfx->set_param(0, channelParameters[1].finalValue(0));
			Rfx->set_param(1, channelParameters[1].finalValue(1));
		}

		process_channel(Lfx, OUT1_OUTPUT, IN1_INPUT);
		process_channel(Rfx, OUT2_OUTPUT, IN2_INPUT);
	}

	float last_samplerate;
};

struct Dual_openerWidget : ModuleWidget {
	Dual_openerWidget(Dual_opener *module)
	{
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/dual_opener.svg")));

		addParam(createParamCentered<BefacoPush>(mm2px(Vec(23.292, 14.977)), module, Dual_opener::FILTER1TYPE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(9.627, 17.01)), module, Dual_opener::FREQ1ROTARY_PARAM));
		addParam(createParamCentered<BefacoPush>(mm2px(Vec(6.704, 47.678)), module, Dual_opener::FILTER2TYPE_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(20.587, 48.145)), module, Dual_opener::FREQ2ROTARY_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.897, 68.27)), module, Dual_opener::FREQ1CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(21.956, 68.27)), module, Dual_opener::FREQ2CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.897, 82.24)), module, Dual_opener::Q1CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(21.956, 82.24)), module, Dual_opener::Q2CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.859, 96.809)), module, Dual_opener::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(21.993, 96.809)), module, Dual_opener::IN2_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.859, 110.779)), module, Dual_opener::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(21.993, 110.779)), module, Dual_opener::OUT2_OUTPUT));

		addChild(createLight<SmallLight<RedGreenBlueLight>>(mm2px(Vec(2.78f, 24.27f)), module, Dual_opener::FREQ1_LIGHT));
		addChild(createLight<SmallLight<RedGreenBlueLight>>(mm2px(Vec(13.79f, 55.43f)), module, Dual_opener::FREQ2_LIGHT));
		addChild(createLight<SmallLight<RedGreenBlueLight>>(mm2px(Vec(2.78f, 27.8f)), module, Dual_opener::QUALITY1_LIGHT));
		addChild(createLight<SmallLight<RedGreenBlueLight>>(mm2px(Vec(13.79f, 58.96f)), module, Dual_opener::QUALITY2_LIGHT));
	}

	void appendContextMenu(Menu *menu) override
	{
		Dual_opener *module = dynamic_cast<Dual_opener *>(this->module);

		menu->addChild(new MenuEntry);
		menu->addChild(createMenuLabel("Algorithm"));

		struct ModeItem : MenuItem {
			Dual_opener *module;
			int mode;
			void onAction(const event::Action &e) override
			{
				module->currentRightEffect = mode;
			}
		};

		std::string modeNames[5] = {"LPF", "LPG", "VCA", "Wavefolder", "Bitcrusher"};
		for (int i = 0; i < 5; i++) {
			ModeItem *modeItem = createMenuItem<ModeItem>(modeNames[i]);
			modeItem->rightText = CHECKMARK(module->currentRightEffect == i);
			modeItem->module = module;
			modeItem->mode = i;
			menu->addChild(modeItem);
		}
	}
};

Model *modelDual_opener = createModel<Dual_opener, Dual_openerWidget>("dual_opener");
