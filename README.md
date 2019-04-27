Space Rocks
======

[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com) [![forthebadge](https://forthebadge.com/images/badges/for-you.svg)](https://forthebadge.com)

| Branch        | Status        | 
| ------------- |:-------------:| 
| Master        | [![Build status](https://ci.appveyor.com/api/projects/status/i8pd1360bfrbaxw4/branch/master?svg=true)](https://ci.appveyor.com/project/SubStrifer/spacerocks/branch/master) |

------
### Building Space Rocks from source on Windows
#### Software:
- [CMake](https://cmake.org/)
- [Visual Studio](https://visualstudio.microsoft.com/downloads/)
- (optional) git client; [git-scm](https://git-scm.com/downloads)

#### Steps
1. Install required software
2. Clone or download this repository
3. In CMake:
  * Set *Where is the source code* path to the local repository folder
  * Set *Where to build the binaries* to a different folder (**outside the repository**)
  * Press *Configure*
  * Press *Generate* (select *Visual Studio 15 2017*, or any other newer version)
  * *Open Project*
4. In Visual Studio
  * You can change to a *Release* configuration
  * Right click on the *SPACE_ROCKS* project (in the *Solution Explorer*)
  * Select *Build*
5. If successful, you can find .exe file in the *Build folder*\bin\Release (or bin\Debug) folder

#### Note
When launching, in the case of an error about "openal32.dll",  
plase copy it over from *Repository folder*\lib\sfml\extlibs\bin\x86 to *Build folder*\bin\Release (or bin\Debug).

------
* Game Design Document
https://docs.google.com/document/d/1G6GCR1EvAarPW5XVATN63ufdhNCaqoHT2BB9JJ5qnwQ/edit?usp=sharing
