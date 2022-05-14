```sh
# Clone this repo
git clone https://github.com/youssef-aydi/Space_Invaders.git
cd Space_Invaders

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./Space_Invaders
```

***Note:*** To use SDL2_ttf, SDL2_net or SDL2_mixer, you should uncomment some
instructions in the CMakeLists.txt file and re-execute the `make` command.
