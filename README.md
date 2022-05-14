# Space Invaders

## Description
This project is written in C and uses [CMake][] as a build system.<br>
It shows how we can make a basic arcade game using [SDL2][SDL].
![Untitled](https://user-images.githubusercontent.com/77480931/168448238-f61e3f95-5b88-46f9-b759-ba34936c2ae9.png)
![Untitled1](https://user-images.githubusercontent.com/77480931/168448243-70651a6f-64e6-44e2-a534-0c4e3a0192ec.png)


It could be used as a base for any SDL2 game. Just fork it, clone it and
execute the `rename_project.sh` script. You will be prompted to enter the new
project name, the new executable name and the new git repository, but you can
keep the autodetected values. Finally, just commit and push the result to your
repository.

## Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_image][] library
- [SDL2_gfx][] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev
```

**Optional packages:**

- [SDL2_ttf][] library
- [SDL2_net][] library
- [SDL2_mixer][] library

```sh
sudo apt install libsdl2-ttf-dev libsdl2-net-dev libsdl2-mixer-dev
```
## Contribution

Thank you for your interest in our project. There are many ways to contribute,
and we appreciate all of them :

- Source code
- Unit tests
- Bug Reports
- Documentation
- Localization (Translation)
- etc

Contributions should be under the terms of the MIT license [&lt;LICENSE&gt;](LICENSE).

## How to build
 See [BUILD.md](BUILD.md)

### Open the project with an IDE under Linux

See [IDE_USAGE.md](IDE_USAGE.md) for details.

## Authors / Contributors

The project was originally developed by:
 Amine B. Hassouna [@aminosbh](https://gitlab.com/aminosbh)
 Youssef Aydi [@youssef-aydi](https://github.com/youssef-aydi)
 Aymen Hammami [@aymendps](https://github.com/aymendps)
 Aziz Maazouz [@aziz-maazouz](https://github.com/aziz-maazouz)

## License

This project is distributed under the terms of the MIT license
[&lt;LICENSE&gt;](LICENSE).


[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[Git]: https://git-scm.com
[SDL2_image]: https://www.libsdl.org/projects/SDL_image
[SDL2_ttf]: https://www.libsdl.org/projects/SDL_ttf
[SDL2_net]: https://www.libsdl.org/projects/SDL_net
[SDL2_mixer]: https://www.libsdl.org/projects/SDL_mixer
[SDL2_gfx]: http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx
[CCBY]: http://creativecommons.org/licenses/by/4.0/
