<!-- SPDX-License-Identifier: 0BSD -->

# Pool (algorithms-suggestions)

This is one of two partial implementations of the
[**algorithms-suggestions**](https://github.com/EliahKagan/algorithms-suggestions)
exercises. The other is **Search** (not yet released).

This was an experiment in doing some of those exercise ideas solo.

## License

[0BSD](https://spdx.org/licenses/0BSD.html). See [**`LICENSE`**](LICENSE).

## Building and running

These steps build the code and run the tests:

```sh
mkdir build
cd build
cmake -G Ninja ..
ninja
ctest
```

To follow those steps, you need `cmake` and `ninja` to be installed. If you
want to use a different generator than `ninja`, that should be fine. (Also,
Visual Studio Code is a nice environment for automatically configuring and
running CMake builds.)

Built executables can be run directly, but there isn't really any functionality
besides what is demonstrated in the tests. This is, after all, just a
collections of some solutions our proposed C++ algorithms and data structures
exercises in
[algorithms-suggestions](https://github.com/EliahKagan/algorithms-suggestions).

Running the built executables directly gives more verbose output than running
them through `ctest` with no arguments as above. Another way to see the
messages sent to standard output is to run:

```sh
ctest --verbose
```
