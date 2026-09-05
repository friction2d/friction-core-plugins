## Metadata

```
{
    "id": "graphics.friction.plugin.importtxt",
    "name": "Import Text File",
    "version": "1.0.0",
    "author": "Ole-André Rodlie",
    "url": "https://friction.graphics",
    "description": "Import Text File",
    "import_extensions": ["txt"],
    "group": "Import",
    "api": "graphics.friction.CorePluginInterface/1.0"
}
```

* `id` *(String, Required)*: A globally unique identifier for your plugin. Using reverse domain name notation is highly recommended to prevent conflicts in the plugin registry.

* `name` *(String, Required)*: The human-readable display name of the plugin. This is used in the UI, error messages, and log outputs.

* `version` *(String)*: The current version of your plugin (semantic versioning like `1.0.0`).

* `author` *(String)*: The name of the developer, team, or organization that created the plugin.

* `url` *(String)*: A link to the plugin's repository, documentation, or author's homepage.

* `description` *(String)*: A short summary detailing what the plugin does.

* `import_extensions` *(Array of Strings, Optional)*: A list of file extensions (without the leading dot) that this plugin is capable of importing. When a user attempts to open a file with a matching extension, Friction bypasses native importers and delegates the process to this plugin's importFile() method.

* `group` *(String, Required)*: The name of the UI sub-menu where the plugin's generated actions should be grouped. If the sub-menu does not exist, the host will create it automatically.

* `api` *(String, Required)*: The specific interface version this plugin is built against. This must exactly match the Friction interface. Friction checks this string to verify API compatibility before loading the C++ binary into memory.
