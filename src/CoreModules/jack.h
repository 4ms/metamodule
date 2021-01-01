#include <cstdint>

// Node ptr style jacks:
struct Jack_nodes {
	float *node_value = nullptr;
	float unpatched_value = 0.f;

	Jack_nodes() {}
	Jack_nodes(float *node)
		: node_value{node}
	{}

	float get()
	{
		return is_patched() ? *node_value : unpatched_value;
	}
	void set(float val)
	{
		if (is_patched())
			*node_value = val;
	}
	bool is_patched()
	{
		return node_value != nullptr;
	}
};

// Netlist index style jacks:
struct Jack_netlist {
	uint32_t net_num = 0;
	float val()
	{
		// Todo: need some Nets array, or pass the module ref in the ctor? parent->Nets[net_num]
		// return Nets[net_num];
	}
	bool is_patched()
	{
		return net_num != 0;
	}
	void set_netnum(uint32_t netnum)
	{
		net_num = netnum;
	}
};

// VCV style jacks:
struct Jack_vcv {
private:
	float _val;
	bool _is_patched;

public:
	float get_val()
	{
		return _val;
	}
	void set_val(float val)
	{
		_val = val;
	}
	bool is_patched()
	{
		return _is_patched;
	}
};

