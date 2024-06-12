<a name="readme-top"></a>

<div align="center">

[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

# Chess Game

A simple chess game written in C++ using SDL2.

</div>

## Requirements

- At least C++17
- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://github.com/libsdl-org/SDL_image)

## Installation

1. Clone the repository

```bash
git clone --recursive https://github.com/AlejandroSuero/chess-game.git
# or
gh repo clone AlejandroSuero/chess-game -- --recursive
```

2. Copy the **sdl2** cmake files in their respective folders:

```bash
cp -r /path/to/SDL2/sdl2-config.cmake /path/to/chess-game/sdl2-config.cmake
cp -r /path/to/SDL2_Image/sdl2-image-config.cmake /path/to/chess-game/sdl2-image-config.cmake
```

3. Build the project

```bash
cd chess-game
make
```

## Usage

Run the executable file `chess-game` in the terminal or double click the file.

You can also run it from the command line using the following command after building the project:

```bash
make run
```

[stars-shield]: https://img.shields.io/github/stars/AlejandroSuero/chess-game.svg?style=for-the-badge
[stars-url]: https://github.com/AlejandroSuero/chess-game/stargazers
[issues-shield]: https://img.shields.io/github/issues/AlejandroSuero/chess-game.svg?style=for-the-badge
[issues-url]: https://github.com/AlejandroSuero/chess-game/issues
[license-shield]: https://img.shields.io/github/license/AlejandroSuero/chess-game.svg?style=for-the-badge
[license-url]: https://github.com/AlejandroSuero/chess-game/blob/main/LICENSE
