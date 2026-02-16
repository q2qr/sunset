![SunsetLogo](https://files.catbox.moe/a5kp6e.png)

# Sunset MC SDK (PS3)

Sunset is a PS3 mod loader for Minecraft SPRX mods.

## Output

- Project: `sunset`
- Built artifact: `PS3_Debug/sunset.prx`

## Quick Build

### Windows

```bat
build-sunset.bat
```

Or specify config:

```bat
build-sunset.bat Release
```

### Shell (Git Bash/WSL)

```sh
./build-sunset.sh
```

Or:

```sh
./build-sunset.sh Release
```

## Environment

Scripts default to:

- `SCE_PS3_ROOT=C:\usr\local\cell`
- `SN_PS3_PATH=C:\usr\local\cell\host-win32\sn`

Override these if your SDK is installed elsewhere.

## Mod Loading

Sunset scans:

- `/dev_hdd0/game/<TITLEID>/USRDIR/mods/`

Supported inputs:

- `.sprx` (direct load)
- `.sunset` (package containing SPRX + metadata JSON + optional preview image)

`.sunset` packages are extracted to:

- `/dev_hdd0/tmp/ps3_mc_modloader/`

## Example Mods

Example projects are now located at:

- `https://github.com/q2qr/SunsetExampleMods`

Each example includes:

- `src/main.cpp`
- `mod.json`
- `preview.txt`
- `build.bat`
- `build.sh`

## Notes

- If `deps/scetool/bin/scetool.exe` is missing, signing is skipped (build still succeeds).
- Current default fallback title id in loader source is `NPUB31419` (`MODLOADER_TITLE_ID` macro).
