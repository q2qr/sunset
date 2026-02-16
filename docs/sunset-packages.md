# Sunset Packages (.sunset)

The loader now supports both raw `.sprx` mods and `.sunset` package files.

## Package Layout

`.sunset` is a binary container with these entries:
- Type `1`: mod SPRX payload (required)
- Type `2`: metadata JSON payload (required)
- Type `3`: preview image payload (optional)

Metadata JSON fields currently read by the loader:
- `name`
- `author`
- `version`
- `description`
- `image`

## Build a Package

Use the packer script:

```powershell
powershell -ExecutionPolicy Bypass -File tools/pack-sunset.ps1 \
  -Sprx example-mods/NoFallMod/NoFallMod.sprx \
  -MetadataJson example-mods/NoFallMod/mod.json \
  -PreviewImage example-mods/NoFallMod/preview.png \
  -Output example-mods/NoFallMod/NoFallMod.sunset
```

## Load Path

Copy `.sunset` files (or `.sprx` files) to:

`/dev_hdd0/game/<TITLEID>/USRDIR/mods/`

At runtime, `.sunset` packages are extracted to:

`/dev_hdd0/tmp/ps3_mc_modloader/`

Then the extracted SPRX is loaded through the same PRX flow as standard mods.
