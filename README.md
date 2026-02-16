![SunsetLogo](https://files.catbox.moe/a5kp6e.png)

# Sunset MC SDK (PS3)

Sunset is a PS3 mod loader for Minecraft SPRX mods.

## Output

- Project: `sunset`
- Built artifact: `Sunset/PS3_Debug/sunset.prx`
- Signed artifact: `Sunset/PS3_Debug/sunset.sprx`

## Quick Build

### Windows

```bat
Sunset\build-sunset.bat
```

Or specify config:

```bat
Sunset\build-sunset.bat Release
```

### Shell (Git Bash/WSL)

```sh
./Sunset/build-sunset.sh
```

Or:

```sh
./Sunset/build-sunset.sh Release
```

`build-sunset.sh` now always:

- builds `.prx`
- signs `.prx` to `.sprx` using `scetool`

## Signing Setup

Default paths used by shell scripts:

- `SCETOOL_EXE=C:/Users/liams/Downloads/scetool/scetool.exe`
- `SCETOOL_WORK_DIR=C:/Users/liams/Videos/sunset/dependencies/scetool/bin`

`SCETOOL_WORK_DIR` must contain `data/keys`, `data/ldr_curves`, and `data/vsh_curves`.

## Environment

Scripts default to:

- `SCE_PS3_ROOT=C:\usr\local\cell`
- `SN_PS3_PATH=C:\usr\local\cell\host-win32\sn`

Override these if your SDK is installed elsewhere.

## Mod Loading

Sunset scans:

- `/dev_hdd0/tmp/sunsetml/mods/`

Supported inputs:

- `.sprx` (direct load)
- `.sunset` (package containing SPRX + metadata JSON + optional preview image)

`.sunset` packages are extracted to:

- `/dev_hdd0/tmp/sunsetml/cache/`

## Example Mods

Example projects are located in:

- `C:\Users\liams\Videos\SunsetExampleMods`

Each example includes:

- `src/main.cpp`
- `mod.json`
- `preview.txt`
- `build.bat`
- `build.sh`

Each example `build.sh` now builds `.prx`, signs to `.sprx`, and packs `.sunset`.

## Notes

- Current default fallback title id in loader source is `NPUB31419` (`MODLOADER_TITLE_ID` macro).