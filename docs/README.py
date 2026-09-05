# SPDX-License-Identifier: GPL-3.0-only

import os
import json
import re

def read_file(filepath):
    if os.path.exists(filepath):
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                return f.read().strip() + "\n\n"
        except Exception as e:
            return ""
    else:
        return ""

def get_plugin_dirs_from_cmake(cmake_path="CMakeLists.txt"):
    dirs = []
    if not os.path.exists(cmake_path):
        return dirs

    try:
        with open(cmake_path, 'r', encoding='utf-8') as f:
            content = f.read()

        pattern = re.compile(r'add_subdirectory\s*\(\s*([^\s)]+)\s*\)', re.IGNORECASE)
        matches = pattern.findall(content)

        for match in matches:
            folder = match.strip('\'"')
            dirs.append(folder)

    except Exception as e:
        print(f"Failed reading {cmake_path}: {e}")

    return dirs

def generate_plugin_markdown(root_dir="."):
    plugins = []

    cmake_path = os.path.join(root_dir, "CMakeLists.txt")
    plugin_dirs = get_plugin_dirs_from_cmake(cmake_path)

    for p_dir in plugin_dirs:
        json_path = os.path.join(root_dir, p_dir, "plugin.json")
        if os.path.exists(json_path):
            try:
                with open(json_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                    plugins.append(data)
            except Exception as e:
                print(f"Failed reading {json_path}: {e}")

    plugins.sort(key=lambda x: x.get("name", "").lower())

    md_lines = ["## Plugins\n"]

    for p in plugins:
        id = p.get("id", "")
        name = p.get("name", "Unknown")
        version = p.get("version", "Unknown")
        author = p.get("author", "Unknown")
        url = p.get("url", "")
        desc = p.get("description", "No description.")
        group = p.get("group", "Unknown")
        extensions = p.get("import_extensions", [])

        md_lines.append(f"### {name} `v{version}`")

        if id:
            md_lines.append(f"- **ID:** `{id}`")

        md_lines.append(f"- **Description:** {desc}")
        md_lines.append(f"- **Group:** {group}")
        md_lines.append(f"- **Author:** {author}")

        if url:
            md_lines.append(f"- **Url:** {url}")

        if extensions:
            ext_str = ", ".join([f"`{ext}`" for ext in extensions])
            md_lines.append(f"- **Supports Import:** {ext_str}")

        md_lines.append("") 

    return "\n".join(md_lines)

def build_readme():
    readme_content = ""
    readme_content += read_file("docs/INTRO.md")
    readme_content += generate_plugin_markdown() + "\n\n"
    readme_content += read_file("docs/INTERFACE.md")
    readme_content += read_file("docs/META.md")
    readme_content += read_file("docs/BUILD.md")
    readme_content += read_file("docs/CONTRIBUTE.md")
    readme_content += read_file("docs/LICENSE.md")

    try:
        with open("README.md", "w", encoding="utf-8") as f:
            f.write(readme_content)
    except Exception as e:
        print(f"Failed writing README.md: {e}")

if __name__ == "__main__":
    build_readme()
