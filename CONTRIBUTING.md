# Contributing to MetaModule

Thanks for your interest in improving MetaModule firmware or simulator!

We use GitHub Issues and Pull Requests (PR) as the primary contribution method.
Bug reports, fixes, and features are all welcome.

If you want to make a feature request, open a discussion about a possible
bug or issue, or discuss a feature you're interested in contributing, please
use the [MetaModule forum](https://forum.4ms.info).


## Where should I post an issue or PR?

- **Issues with 4ms modules** should be reported in
  [CoreModules](https://github.com/4ms/metamodule-core-modules)
- **Issues with non-4ms built-in modules** (brands in firmware/vcv_ports/) can
  be reported here, or on the submodule's github repo.
- **The 4ms VCV Rack plugin** (MetaModule hub and 4ms modules for VCV) lives in
  [4ms-vcv](https://github.com/4ms/4ms-vcv).
- **Submodules**: a lot of code here is pulled in as git submodules (the plugin
  SDK, CoreModules, mdrivlib, cpputil, the ported VCV brands, etc. See
  `.gitmodules`). Changes to that code need a PR in the submodule's own repo
  first, followed by a PR here that updates the submodule pointer.
- **Everything else** (firmware, simulator, docs): open a PR here.

## Reporting bugs

You are welcome to report bugs on the MetaModule forum in the [Bug Reports and
Fixes category](https://forum.4ms.info/c/bug-reports-and-fixes/10). This is
recommended if you'd like to open a discussion with other users around the
issue or are unsure if what you're seeing is a bug.

Otherwise, if you prefer to report a bug on the repo, open a [GitHub
issue](https://github.com/4ms/metamodule/issues) and include:

- Firmware version, and which plugins were loaded if relevant
- Steps to reproduce, and what you expected to happen vs. what actually happened
- The patch file (`.yml`) if the bug involves a particular patch
- Whether it also happens in the simulator (if you're able to check)

## Contributing code (bug fixes, improvements, or features)

Create a PR (pull request) on this repo.
- Fork the repo, creating a copy of the repo on your github account.
    - If you have push access to the 4ms/metamodule repo, then
      a fork is not necessary, just use a new branch.
- Branch from `main`, and do your work on that branch, pushing to your repo.
- Open the PR against `main`.
- Keep each PR to one topic. Smaller PRs get reviewed faster.
- Write short, imperative commit subjects, like the existing history:
  `Fix off-by-one in context menus with unknown widgets`. For submodule
  updates, say why: `Update sdk (docs for createDirectories)`.
- In the PR description, say what changed, why, and how you tested it.
  Include a screenshot for GUI changes.

## Building and testing

Set up your environment with [Setup](./docs/Setup.md), then see the
[firmware](./firmware/README.md) and [simulator](./simulator/README.md) guides.

CI does not run automatically on pull requests, so please check these locally
before you submit:

```bash
# Unit tests (host compiler only, no arm toolchain needed)
cd firmware && make -f tests/Makefile

# Firmware build
cd firmware && make configure && make all

# Simulator build
cd simulator && make config-sim && make
```

Run whichever of these your change could affect. 

## Code style

- Format C++ with the `.clang-format` at the root of the repo.
- Match the code around your change: tabs for indentation, `snake_case`
  functions and variables, `PascalCase` types, `.hh` for C++ headers.
- Don't reformat or refactor code unrelated to your change.


## AI tools

You may use AI tools to help write code, but you are the author of what you
submit and are responsible for it. You should understand it, have tested it,
and be able to answer review questions about it yourself.

- Do not add `Co-Authored-By:` trailers that name an AI tool or agent.
- Do not set an AI tool as the commit author or committer.
- Do not add "Generated with ..." lines to commit messages or PR descriptions.

Commits containing these will need to be rewritten before the PR is merged.
(`Co-Authored-By:` for human collaborators is fine.)

## License

MetaModule is licensed under the GNU GPL, version 3 or (at your option) any
later version. See [LICENSE.md](./LICENSE.md).

By submitting a contribution, you agree that it is licensed under those same
terms, and you confirm that you wrote it or otherwise have the right to submit
it under that license. You keep the copyright on your contribution.

If your PR includes code or assets that you didn't write (a library, a ported
module, a font, artwork, etc.), say in the PR where it came from and what license it's
under, and keep the original license and copyright notices. Code must be under
a GPLv3-compatible license. 
