## Build

In your Friction source repo:

```
git clone https://github.com/friction2d/friction-core-plugins src/plugins
```

Now reconfigure your project (Friction will check for `src/plugins`) and plugins should show up in your IDE (or whatever you use).

As default, plugins will be built in `build_dir/src/app/plugins` on Linux or `build_dir/src/app/friction.app/Contents/MacOS/plugins` on macOS.

Plugins search paths (in order):

* Friction app folder/plugins
* Friction app folder/../CMAKE_INSTALL_LIBDIR/friction/plugins
* User config folder/CorePlugins or custom path from settings
