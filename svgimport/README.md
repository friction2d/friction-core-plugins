# SVG Animation Import

Imports animated SVG files as editable Friction objects. The import dialog can
scale the SVG to the active scene, preserve or flatten its structure, and
extend or replace the scene duration.

## Build

Clone this repository as `src/plugins` inside a checkout of Friction's
`core-plugins` branch, then configure and build Friction normally. The plugin
target is named `SvgImportPlugin`.

The resulting module is written to the `plugins` directory next to the
Friction executable. On macOS it is written to:

```
build_dir/src/app/friction.app/Contents/MacOS/plugins/SvgImportPlugin.so
```

Build release artifacts with the same SDK and deployment process used for the
target Friction release. On macOS, extract the module only after
`macdeployqt` has processed the application bundle; this rewrites its Qt
dependencies to the copies shipped by Friction.

## Install

Close Friction, copy the single plugin module into Friction's configured
plugins directory, and restart the application. By default this is the
`plugins` directory next to the executable. The `plugin.json` metadata is
embedded in the module and does not need to be copied separately.

Plugins are native binaries. Distribute a separate build for each supported
operating system and architecture, and state the target Friction release and
CorePluginInterface API version alongside the download.

This plugin is licensed under GPL-3.0-only. Binary distributions must provide
the corresponding source code as required by that license.
