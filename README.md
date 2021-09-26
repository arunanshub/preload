# preload

> This is currently a WIP

This preload is a clone of [Behdad Esfahbod's preload](http://preload.sf.net).
The only difference is that this project uses [`meson`](https://mesonbuild.com)
as its build system.

Note that this is a work in progress. So, if you're going to use it, make sure
that you check [`meson.build`](/meson.build) first.

Configuration file for `preload` can be generated via:

```sh
./gen.preload.conf.sh preload.conf.in ./include/confkeys.h
```

Although there are better ways to do this, I'll simply leave it like this for
now.

## Why `meson`?

- Because it is easier to configure.
- Also because I hate Make, CMake and all other shit.
- Also because I had no intention to understand how the author's build config
  worked/works.
- Because I wanted a cleaner codebase.

## Style Guide

[Chromium Style Guide](https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/c++/c++.md)
is used with some minor modifications:

- Maximum column length: 79
- Indent width: 4

Use this to generate a `.clang-format` file:

```bash
clang-format \
    -style="{BasedOnStyle: Chromium, ColumnLimit: 79, IndentWidth: 4}" \
    --dump-config > .clang-format
```

Since `include/confkeys.h` is also used by a configuration file generator
script, don't run `clang-format` on it. You can put that file in
`.clang-format-ignore` like this:

```bash
echo 'include/confkeys.h' > .clang-format-ignore
```

Check [Mesonbuild's guide on `clang-format`](https://mesonbuild.com/Code-formatting.html)
for more info.
