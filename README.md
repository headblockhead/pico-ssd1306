# pico-ssd1306

![Nix Flake](https://img.shields.io/badge/NIX%20FLAKE-5277C3.svg?logo=NixOS&logoColor=white) 

Simple library for using ssd1306 displays with the Raspberry Pi Pico and the pico-sdk.
This is an opinionated fork of [David Schramm's pico-ssd1306](https://github.com/daschr/pico-ssd1306) that adds CMake and Nix support (plus a few changes by [Jonas Grosse-Holz](https://github.com/daschr/pico-ssd1306/pull/18) to add rotation), and generally removes all the extra unnecessary stuff ;)

## Usage
* Import this project as a submodule in your project
* Add the following lines to your `CMakeLists.txt`:
```cmake
add_subdirectory(pico-ssd1306)
target_link_libraries(your_project pico-ssd1306)
```
* Make sure `PICO_SDK_PATH` is set
* Happy coding!

## Draw Images
For converting an image to the supported bitmap format:

* install [ImageMagick](https://imagemagick.org/)
* use `convert you_image.png -monochrome your_image.bmp`

For embedding your image, use `bin2c`.

## Fonts

Font arrays are 1D arrays of `uint8_t` values with the structure:
- height per character
- width per character
- additional spacing between characters
- index of the first ascii character in the array
- index of the last ascii character in the array
- the font data, encoded from bottom to top per bit, then left to right per byte (see [jared.geek.nz](https://web.archive.org/web/20140621120334/https://jared.geek.nz/2014/jan/custom-fonts-for-microcontrollers#expand) for an example).
