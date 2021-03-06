## 0.1.5 (2021-10-21)

### Fix

- **preload**: use appropriate naming for system dirs

## 0.1.4 (2021-10-05)

### Refactor

- **common**: remove check for stringize as it is done in the build script

## 0.1.3 (2021-09-25)

### Refactor

- use `G_CALLBACK` macro to construct callbacks

### Fix

- get rid of cast warnings

## 0.1.2 (2021-09-24)

### Refactor

- don't duplicate `free` function's name

## 0.1.1 (2021-09-24)

### Fix

- **confkeys**: fix indentations caused due to `clang-format`

## 0.1.0 (2021-09-24)

### Refactor

- **cmdline**: show package version
- **state**: rename `VERSION` to `PACKAGE_VERSION`
- **readahead**: mark unused field
- **cmdline**: remove redundant `const`s

### Fix

- **state**: use correct format code; don't use `__G_PRINTF_H__`
- **proc**: use correct format code; don't use `entry.d_name`

### Feat

- remove all build errors
- init
