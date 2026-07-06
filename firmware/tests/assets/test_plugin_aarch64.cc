// Test fixture for the ELF64/AArch64 plugin relocator.
// Built with: aarch64-linux-gnu-g++ -shared -fPIC -nostdlib -fno-exceptions -fno-rtti
//             -o test_plugin_aarch64.so test_plugin_aarch64.cc

extern "C" int host_provided_func(int); // undefined -> R_AARCH64_JUMP_SLOT/GLOB_DAT
extern int host_provided_data;			// undefined -> R_AARCH64_GLOB_DAT

int local_value = 42;
int *ptr_to_local = &local_value; // R_AARCH64_RELATIVE

extern "C" int local_func(int x) {
	return x + local_value;
}
extern "C" int (*ptr_to_func)(int) = local_func; // R_AARCH64_RELATIVE (or ABS64)

extern "C" int use_host(int x) {
	return host_provided_func(x) + host_provided_data;
}

extern "C" bool ctor_ran = false;
struct CtorTest {
	CtorTest() {
		ctor_ran = true;
	}
};
CtorTest ctor_test; // .init_array entry
