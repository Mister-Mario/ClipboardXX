# System tests
System tests are done by using [SikuliX] (http://sikulix.com/)
## How to use
Firstly follow the [download guide on SikuliX] (http://sikulix.com/#home3)
Secondly create a paths.json at the same level as this readme file, paths.json must follow this structure:
```json
{
    "shortcuts_path" : "<<absolute-path>>", 
    "app_exe_path" : "<<absolute-path>>",
    "sikuli_jar_path" : "<<absolute-path>>",
    "text_editor" : "<<absolute-path>>"
}
```
This paths are used by sikulix to open different kind of files and launch executables.