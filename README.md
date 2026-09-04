# Friction Core Plugins

Community Core (C++) Plugins for Friction.

## Plugins

* Hello World *(Example)*
* Import Text File

## Interface *(coreplugininterface.h)*

```cpp
class FrictionCorePluginInterface
{
public:
    virtual ~FrictionCorePluginInterface() = default;

    virtual void init() {};

    virtual QList<QAction*> createMenuActions(QObject* parent)
    {
        Q_UNUSED(parent);
        return {};
    }

    virtual QList<QAction*> createToolbarActions(QObject* parent)
    {
        Q_UNUSED(parent);
        return {};
    }

    virtual void triggerAction(Document& doc,
                               Canvas* const scene,
                               const QAction *act)
    {
        Q_UNUSED(doc);
        Q_UNUSED(scene);
        Q_UNUSED(act);
    }

    virtual qsptr<BoundingBox> importFile(Canvas* const scene,
                                          const QString &path)
    {
        Q_UNUSED(scene);
        Q_UNUSED(path);
        return nullptr;
    }
};
```

## Meta *(plugin.json)*

```
{
    "id": "graphics.friction.plugin.helloworld",
    "name": "Hello World",
    "version": "1.0.0",
    "author": "Friction",
    "url": "https://friction.graphics",
    "description": "Hello World Example Plugin",
    "group": "Test",
    "api": "graphics.friction.CorePluginInterface/1.0"
}
```

## Build

In your Friction source repo:

```
cd src
git clone https://github.com/friction2d/friction-core-plugins plugins
```

Now reconfigure your project and plugins should show up in your IDE (or whatever you use).

As default, plugins will be built in `build_dir/src/app/plugins`. Friction will search in the folder `plugins` relative to the binary for plugins. UI for setting different folder and support for enable/disable will be added in Friction later.

## Contribute

Fork and make a pull request. This repo is less restrictive than the Friction repo, we allow the use of "AI" tools.

## License

**`SPDX-License-Identifier: GPL-3.0-only`**

All plugins must use this license.
