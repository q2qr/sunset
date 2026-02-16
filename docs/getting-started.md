# Getting Started

1. Build the framework:
   - `cd framework && make`
2. Build the loader:
   - `cd ../loader && make`
3. Build an example mod:
   - `cd ../example-mods/NoFallMod && make`
4. (Optional) Package a mod as `.sunset`:
   - `powershell -ExecutionPolicy Bypass -File ../../tools/pack-sunset.ps1 -Sprx .\NoFallMod.sprx -MetadataJson .\mod.json -PreviewImage .\preview.png -Output .\NoFallMod.sunset`
5. Copy built `.sprx` or `.sunset` mods to `/dev_hdd0/game/<TITLEID>/USRDIR/mods/`.
