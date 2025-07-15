# Space Game - Vulkan Edition

This refactor introduces a cross platform build based on Vulkan. The code now
uses GLFW for window creation and event handling and a small `VulkanRenderer`
class for initialization. The project can be built on Linux and Windows using
CMake and the official Vulkan SDK.

## Building

```
mkdir build && cd build
cmake ..
make
```

On Windows, run the same commands from a Visual Studio Developer Prompt to
generate Visual Studio projects.

## Replacing Windows specific libraries

The old Direct2D/Direct3D pipeline has been replaced with Vulkan. For windowing,
GLFW is used instead of the Win32 API. Audio playback used the WinMM API and
should be replaced with a cross platform library such as SDL2's audio
subsystem or OpenAL.

Image loading previously relied on Windows Imaging Component; consider using the
single header [stb_image](https://github.com/nothings/stb) which works on all
platforms.
