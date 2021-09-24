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
