# OpenRCT2
An open-source re-implementation of RollerCoaster Tycoon 2. A construction and management simulation video game that simulates amusement park management.

### Build Status
|             | Windows | Linux / Mac | Download |
|-------------|---------|-------------|----------|
| **master**  | [![AppVeyor](https://ci.appveyor.com/api/projects/status/7efnemxhon6i5n34/branch/master?svg=true)](https://ci.appveyor.com/project/IntelOrca/openrct2-ject9) | [![Travis CI](https://travis-ci.org/OpenRCT2/OpenRCT2.svg?branch=master)](https://travis-ci.org/OpenRCT2/OpenRCT2) | [![OpenRCT2.org](https://img.shields.io/badge/stable-v0.0.4-green.svg)](https://openrct2.org/downloads/master/latest) |
| **develop** | [![AppVeyor](https://ci.appveyor.com/api/projects/status/7efnemxhon6i5n34/branch/develop?svg=true)](https://ci.appveyor.com/project/IntelOrca/openrct2-ject9) | [![Travis CI](https://travis-ci.org/OpenRCT2/OpenRCT2.svg?branch=develop)](https://travis-ci.org/OpenRCT2/OpenRCT2) | [![OpenRCT2.org](https://img.shields.io/badge/develop-v0.0.5-blue.svg)](https://openrct2.org/downloads/develop/latest) |

### Chat
English:<br />
[![Gitter](https://img.shields.io/badge/gitter-general-blue.svg)](https://gitter.im/OpenRCT2/OpenRCT2/non-dev)<br />
[![Gitter](https://img.shields.io/badge/gitter-development-yellowgreen.svg)](https://gitter.im/OpenRCT2/OpenRCT2)<br />
Nederlands:<br />
[![Gitter](https://img.shields.io/badge/gitter-general-blue.svg)](https://gitter.im/OpenRCT2/OpenRCT2/Nederlands)

# Contents
- 1 - [Introduction](#1-introduction)
- 2 - [Downloading the game (pre-built)](#2-downloading-the-game-pre-built)
- 3 - [Building the game](#3-building-the-game)
  - 3.1 - [Building prerequisites](#31-building-prerequisites)
  - 3.2 - [Compiling and running](#32-compiling-and-running)
- 4 - [Contributing](#4-contributing)
  - 4.1 - [Bug fixes](#41-bug-fixes)
  - 4.2 - [New features](#42-new-features)
  - 4.3 - [Translation](#43-translation)
- 5 - [Licence](#5-licence)
- 6 - [More information](#6-more-information)

# 1 Introduction

**OpenRCT2** is an open-source re-implementation of RollerCoaster Tycoon 2 (RCT2). The gameplay revolves around building and maintaining an amusement park containing attractions, shops and facilities. The player must try to make a profit and maintain a good park reputation whilst keeping the guests happy. OpenRCT2 allows for both scenario and sandbox play. Scenarios require the player to complete a certain objective in a set time limit whilst sandbox allows the player to build a more flexible park with optionally no restrictions or finance.

RollerCoaster Tycoon 2 was originally written by Chris Sawyer in x86 assembly and is the sequel to RollerCoaster Tycoon. The engine was based on Transport Tycoon, an older game which also has an equivalent open-source project, [OpenTTD](http://openttd.org). OpenRCT2 attempts to provide everything from RCT2 as well as many improvements and additional features, some of these include support for modern platforms, an improved interface, improved guest and staff AI, more editing tools, increased limits, and cooperative multiplayer. It also re-introduces mechanics from RollerCoaster Tycoon that were not present in RollerCoaster Tycoon 2. Some of those include; mountain tool in-game, the *"have fun"* objective, launched coasters (not passing-through the station) and several buttons on the toolbar.

# 2 Downloading the game (pre-built)

OpenRCT2 requires original files of RollerCoaster Tycoon 2 to play. It can be bought at either [Steam](http://store.steampowered.com/app/285330/) or [GOG.com](http://www.gog.com/game/rollercoaster_tycoon_2).

[OpenRCT2.org](https://openrct2.org/downloads) offers precompiled builds and installers of the latest stable and the develop branch. There is also a cross platform [Launcher](https://github.com/LRFLEW/OpenRCT2Launcher/releases) available that will automatically update your build of the game so that you always have the latest version.

# 3 Building the game

## 3.1 Building prerequisites

OpenRCT2 requires original files of RollerCoaster Tycoon 2 to play. It can be bought at either [Steam](http://store.steampowered.com/app/285330/) or [GOG.com](http://www.gog.com/game/rollercoaster_tycoon_2).

### Windows:
- Vista / 7 / 8 / 10
- Visual Studio 2015 Update 2 (Enterprise / Professional / [Community (Free)](https://www.visualstudio.com/products/visual-studio-community-vs))
- [Powershell 4.0](http://social.technet.microsoft.com/wiki/contents/articles/21016.how-to-install-windows-powershell-4-0.aspx).

### Mac:
- [Homebrew](http://brew.sh)

### Mac / Linux:
- sdl2
- sdl2-ttf
- speexdsp
- curl (only if building with network support)
- jansson (only if building with network support)
- iconv (part of glibc on Linux)
- cmake
All libs listed here (bar cmake) required in 32 bit variants.

## 3.2 Compiling and running
### Windows:
1. Check out the repository. This can be done using [GitHub Desktop](https://desktop.github.com) or [other tools](https://help.github.com/articles/which-remote-url-should-i-use).
2. Open a new Developer Command Prompt for VS2015, run PowerShell and then navigate to the repository.
3. Run the ```setenv.ps1``` script in the repository to set up your PowerShell environment for OpenRCT2 development. This will warn you of any missing applications required to build OpenRCT2.
4. Run ```install``` to download the required dependencies to build OpenRCT2.
5. Run ```build all``` to build all the required components for OpenRCT2.
6. Run ```run``` to run OpenRCT2.

These PowerShell scripts are stored in ```.\scripts\ps``` and have parameters. Once you have used the build script once, further development can be done within Visual Studio by opening ```openrct2.sln```. The build scripts have several commands allowing you to rebuild certain components such ```g2.dat``` or language files.

### Mac:
We support native builds for macOS (limited to i386 only for now).
Make sure that you have [Homebrew](http://brew.sh/) installed and than run the following commands to install all the needed libraries and build OpenRCT2.
```
# Install libraries
./install.sh

# Build OpenRCT2
./build.sh

# Run the game
./openrct2
```

### Linux:
We support native builds for Linux (limited to i386 only for now).
As the easiest approach depends on your distribution, please take a look at the [wiki](https://github.com/OpenRCT2/OpenRCT2/wiki/Building-OpenRCT2-on-Linux).


# 4 Contributing
OpenRCT2 uses the [gitflow workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow). If you are implementing a new feature or logic from the original game, please branch off and perform pull requests to ```develop```. If you are fixing a bug for the next release, please branch off and perform pull requests to the correct release branch. ```master``` only contains tagged releases, you should never branch off this.

Please read our [contributing guidelines](https://github.com/OpenRCT2/OpenRCT2/blob/develop/CONTRIBUTING.md) for information.

## 4.1 Bug fixes
A list of bugs can be found on the [issue tracker](https://github.com/OpenRCT2/OpenRCT2/issues). Feel free to work on any bug and submit a pull request to the develop branch with the fix. Mentioning that you intend to fix a bug on the issue will prevent other people from trying as well.

## 4.2 New features
Please talk to the OpenRCT2 team first before starting to develop a new feature. We may already have plans or reasons against it, therefore contacting us will allow us to help you or prevent you from wasting any time. You can talk to us via gitter, see links at the top of this page.

## 4.3 Translation
You can translate the game into other languages by editing the language files in ```data/language``` directory. Please join discussions and submit pull requests to [OpenRCT2/Localisation](https://github.com/OpenRCT2/Localisation).

# 5 Licence
**OpenRCT2** is licensed under the GNU General Public License version 3.

# 6 More information
- [GitHub](https://github.com/OpenRCT2/OpenRCT2)
- [OpenRCT2.org](https://openrct2.org)
- [Forums](https://openrct2.org/forums/)
- [Facebook](https://www.facebook.com/OpenRCT2)
- [RCT subreddit](http://www.reddit.com/r/rct/)
- [OpenRCT2 subreddit](http://www.reddit.com/r/openrct2/)
