# Watcher
A process/application monitor and manager for Linux. 

<p align="center">
    <img src="https://images2.imgbox.com/60/08/sorizb8q_o.png" />
</p>

## Build Process
### Prerequisite 
This project is fully compatible with  [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp). Please folllow the installation instruction provided in the mentioned documentation.
> This project is tested in `Arch Linux (Kernel 6.0.8-arch1-1)` with `GCC 12.2.0` and `CMake 3.24.3`

### Build with VS Code
This project can easily be built with `CMake:build` command of VS Code. 

> If the command is not found in command palette (<kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>), the [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) needs to be installed. Launch Quick Open with <kbd>Ctrl</kbd>+<kbd>P</kbd>, paste the following command and then press enter. 
> 
> `ext install ms-vscode.cpptools-extension-pack`

Use the `CMake: Run Without Debugging` command to run the built executable(s). You can also use the ▶️ button in the status bar at the bottom of the screen.

### Manual Build
Run the `run.sh` script to build and execute the project.

This project is version controlled with [git](https://git-scm.com/), and git does not retain the file permissions for non-binary files. Therefore, if you encounter permission error, you may need to change the script's permission.

```bash
chmod +x run.sh # to add execution permission
./run.sh # to execute the script
```

## Configuration
Watcher uses a `JSON` based configuration file to configure the applications to watch. This uses a very minimal syntax for simplicity and edge of usages. 

Path: `<PROJECT_ROOT>/config/watchdog.json`

```json
{
    "processes": [
        {
            "name": "uhura",
            "command": "bin/uhura",
            "args": []
        },
        {
            "name": "spock",
            "command": "bin/spock",
            "args": ["Needs of the many outweighs the needs of the few"],
            "foreground": true
        },
        {
            "name": "kirk",
            "command": "bin/kirk",
            "args": []
        },
    ]
}
```
`processes` is a `JSON array` that can have multiple objects with `name`, `command` and `args` keys. Description of the keys are followings:

* `name`: Name of the process/application that watcher going to use to identify it
* `command`: The command to initiate the process/application. If the application name is not included in the system path, then it has to be specified relative to the `<PROJECT_ROOT>/build` directory.
* `args`: An array that takes `string` arguments as startup parameter to the process/application
* `foreground` is an optional key that will mark this process/application as the foreground process. That process will be on top of all other process/applications in GUI prespective.

## Sample Porcesses
Five sample processes has been created for watcher to demonstrate what it can do. These processes are named after five Star Trek characters. 
* Kirk
* Spock
* Uhura
* Picard
* Data

All these processes logs a message to `<PROJECT_ROOT>/logs/<process_name>.log` in a random interval between 1 and 10 seconds. 

Among these processes `spock` takes a string as start-up parameter. The message from the `spock` process depends on the start-up argument. If no argument is passed, it has a default text to log.

<p align="center" width="200">
    <img src="https://images2.imgbox.com/04/a1/Cs7vjLRm_o.png"/>
</p>

## Logs
