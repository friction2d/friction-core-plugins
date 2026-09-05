## Build

In your Friction source repo:

```
git clone https://github.com/friction2d/friction-core-plugins src/plugins
```

Now reconfigure your project (Friction will check for `src/plugins`) and plugins should show up in your IDE (or whatever you use).

As default, plugins will be built in `build_dir/src/app/plugins`. Friction will search in the folder `plugins` relative to the `friction` binary. UI for settings etc will be added in Friction later.
