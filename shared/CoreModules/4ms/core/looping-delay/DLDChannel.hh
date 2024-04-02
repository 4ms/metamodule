namespace MetaModule
{

template <class Parent, class Mapping>
class DLDChannel
{
private:
	template<Parent::Info::Elem EL>
	void setOutput(auto val)
	{
		return parent->template setOutput<EL>(val);
	}

	template<Parent::Info::Elem EL>
	auto getInput()
	{
		return parent->template getInput<EL>();
	}

	template<Parent::Info::Elem EL, typename VAL>
	void setLED(const VAL &value)
	{
		return parent->template setLED<EL>(value);
	}

	template<Parent::Info::Elem EL>
	auto getState()
	{
		return parent->template getState<EL>();
	}

private:
	Parent* parent;

public:
	DLDChannel(Parent* parent_)
		: parent(parent_)
	{}

    void update()
    {

    }
    void set_samplerate(float sr) {
    }

}; 

}