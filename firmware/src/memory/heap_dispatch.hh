#pragma once
#include <cstddef>

// Address-dispatching free/realloc (see heap_dispatch.cc). The firmware links
// with --wrap=free/_free_r/realloc/_realloc_r so every firmware call site
// reaches these; plugin imports of the same symbols are rebound here by the
// dynloader (allocator_redirect in plugin_allocator.cc).

extern "C" {

void __wrap_free(void *p);
void __wrap__free_r(struct _reent *r, void *p);
void *__wrap_realloc(void *p, size_t size);
void *__wrap__realloc_r(struct _reent *r, void *p, size_t size);

} // extern "C"
