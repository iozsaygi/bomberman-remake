# Bomberman: Remake

This is a hobby project where I am implementing a Bomberman-inspired game by creating a custom engine on top of
the [SDL](https://www.libsdl.org/) library. I do not own any of the textures.

Please see [this](https://en.wikipedia.org/wiki/Bomberman_(1983_video_game)) page for more information on Bomberman.

## Preview

1. Initial rendering of the map and player.

![Initial rendering of the map and player](https://github.com/iozsaygi/bomberman-remake/blob/main/media/map-and-player-rendering.png)

2. Added textures for player, map, and bomb. (No animations are available yet.)

![Added textures for player, map, and bomb](https://github.com/iozsaygi/bomberman-remake/blob/main/media/map-and-player-textures.png?raw=true)

3. Added first non-functional enemy.

![Added first non-functional enemy](https://github.com/iozsaygi/bomberman-remake/blob/main/media/first-enemy.png)

## Building

### Windows

1. Download and install [CMake](https://cmake.org/download/)
2. Ensure that you already installed [Microsoft Visual Studio](https://visualstudio.microsoft.com/downloads/) with
   the ``Desktop development with C++`` workload selected
3. ``cd`` to the repository directory by using ``Visual Studio Developer Command Prompt``
4. ``mkdir build``
5. ``cd build``
6. ``cmake -G "Visual Studio 17 2022" -A x64 ..``
7. ``msbuild /m /p:Configuration=Debug /p:Platform=x64 bomberman_remake.sln``

## Possible improvements to make

- AI with path-finding
- Better collision handling
- Gameplay animations
- Procedural levels

## License

[MIT License](https://github.com/iozsaygi/bomberman-remake/blob/main/LICENSE)