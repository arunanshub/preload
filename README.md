# preload

> This is currently a WIP

This preload is a clone of [Behdad Esfahbod's preload](https://preload.sf.net).
The only difference is that this project uses [`meson`](https://mesonbuild.com)
for building purposes.

Note that this is a work in progress, and several macros are handwritten in the
build script instead of automating the whole process. Also, the entire codebase
is in the root dir instead of being in a `src/` directory.

So, if you're going to use it, make sure that you check
[`meson.build`](/meson.build) first.
