namespace MousaiMux
{

// Mux Pins for buttons and their LEDs.
// TCA9555 Muxes are used.
// Note: Some of these are not LEDs (*EncSw, and OnOffPedal)
enum ButtonMux0 {
	// Button Mux U12 (I2C:0x20). LED Mux U14 (I2C:0x23)
	Prog1,
	Prog2,
	Prog3,
	Prog4,
	Prog5,
	Prog6,
	Prog7,
	Prog8,
	Save,
	Bank,
	GenA,
	GenB,
	GenC,
	GenD,
	GenType,
	TuneEncSw, //not an LED
};

enum ButtonMux1 {
	// Button Mux U9 (I2C:0x21). LED Mux U10 (I2C:0x24)
	OctUp,
	OctDown,
	ModA,
	ModB,
	ModC,
	ModD,
	ModType,
	Rand,
	RandEdit,
	Record,
	Trigger,
	RecMode,
	Route,
	DistMode,
	FiltMode,
	ResMode,
};

enum ButtonMux2 {
	// Button Mux U7 (I2C:0x22). LED Mux U11 (I2C:0x25)
	EchoMode,
	ReverbMode,
	MapRnd,
	MapGen,
	MapCV1,
	MapCV2,
	Shift,
	Global,
	Clear,
	Left,
	Right,
	Unused1,
	DataEncSw,		//not an LED
	OnOffPedalRing, //not an LED
	OnOffPedalTip,	//not an LED
	Unused2,
};

// Mux connections for DG408 chips
enum ADCMuxPins {
	// MUX1
	ReverbFilter,
	ReverbSpaceTime,
	ReverbDeccay,
	EchoFilter,
	EchoTime,
	EchoFeedback,
	ResonatorFeedback,
	ResonatorTune,
	// MUX2
	LooperLength,
	LooperSOS,
	DistorAmnt,
	FilterMode,
	FilterCuttoff,
	FilterResonance,
	FilterSpread,
	// MUX3
	LooperSpeed,
	LooperStart,
	LooperFilter,
	ModulatorSpeed,
	ModulatorPhase,
	GenerartorParam1,
	GenerartorParam2,
	GeneratorStWidth,
	// MUX4
	DryWetFilter,
	DryWetResonator,
	DryWetDistortion,
	DryWetEcho,
	DryWetReverb,
	MasterFilter,
	MasterVolume,
	// MUX5
	ProgramerMorphTime,
	VolEXT,
	VolLooper,
	VolGenA,
	VolGenB,
	VolGenC,
	VolGenD,
	UnusedMux5,
};

} // namespace MousaiMux
