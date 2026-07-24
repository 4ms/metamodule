#include "safe_log.hh"
#include <cstdlib>
#include <cxxabi.h>
#include <exception>

// libstdc++'s default terminate handler is __gnu_cxx::__verbose_terminate_handler,
// which pulls in the C++ demangler (tens of KB of flash). Defining the symbol
// here preempts the library version: same diagnostics (exception type and
// what()), but with the mangled type name, and printed via SafeLog so it works
// even when the heap is exhausted -- the usual reason we are terminating.

namespace __gnu_cxx
{

void __verbose_terminate_handler() {
	static bool terminating = false;

	MetaModule::SafeLog log;

	if (terminating) {
		log.str("[terminate] called recursively");
		log.flush();
		std::abort();
	}
	terminating = true;

	log.str("[terminate] ");

	if (auto *t = abi::__cxa_current_exception_type()) {
		log.str("uncaught exception of type ");
		log.str(t->name()); // mangled: printing it raw avoids linking the demangler

		// Same trick as libstdc++: rethrow to inspect the active exception
		try {
			throw;
		} catch (std::exception &e) {
			log.str(": ");
			log.str(e.what());
		} catch (...) {
		}
	} else {
		log.str("called without an active exception");
	}

	log.flush();
	std::abort();
}

} // namespace __gnu_cxx
