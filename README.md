Space Rocks
======

[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/for-you.svg)](https://forthebadge.com)

| Branch        | Status        | 
| ------------- |:-------------:| 
| Master        | [![Build status](https://ci.appveyor.com/api/projects/status/i8pd1360bfrbaxw4/branch/master?svg=true)](https://ci.appveyor.com/project/SubStrifer/spacerocks/branch/master) |

------
### Building Space Rocks from source on Windows
#### Software:
- [CMake](https://cmake.org/).
- [Visual Studio](https://visualstudio.microsoft.com/downloads/).
- (optional) Git client; [git-scm](https://git-scm.com/downloads).

#### Instructions
1. Install required software.
2. Clone or download this repository.
3. In CMake:
    1. Set "Where is the source code" path to the local repository folder.
    2. Set "Where to build the binaries" to a different folder (**outside the repository**).
    3. Press:
        1. **Configure**.
        2. **Generate** (select *Visual Studio 15 2017*, or any other newer version).
        3. **Open Project**.
4. In Visual Studio
    1. Change to a *Release* configuration if desired.
    2. Right click on the *SPACE_ROCKS* project (in the *Solution Explorer*).
    3. Select *Build*.
5. If successful, you can find .exe file in the *Build folder*\bin\Release (or bin\Debug) folder.
__________________________________________________________________________________________________
>###### Note
>When launching, in case of an error involving "openal32.dll", 
please copy it over from *Repository folder*[\lib\sfml\extlibs\bin\x86](https://github.com/SFML/SFML/tree/0980e90ee486de80b082bf77c3e4762b885b4d67/extlibs/bin/x86) to *Build folder*\bin\Release (or bin\Debug).
