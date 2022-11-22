# Watcher
A process/application monitor and manager for Linux. 

<p align="center">
    <img src="https://images2.imgbox.com/60/08/sorizb8q_o.png" />
</p>

## Build Process
### Prerequisite 
This project is fully compatible with  [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp). Please follow the installation instruction provided in the mentioned documentation.
> This project is tested in `Arch Linux (Kernel 6.0.8-arch1-1)` with `GCC 12.2.0` and `CMake 3.24.3`

### Build with VS Code
This project can quickly be built with `CMake:build` command of VS Code. 

> If the command is not found in command palette (<kbd>Ctrl</kbd> + <kbd>Shift</kbd> + <kbd>P</kbd>), the [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) needs to be installed. Launch Quick Open with <kbd>Ctrl</kbd>+<kbd>P</kbd>, paste the following command and then press enter. 
> 
> `ext install ms-vscode.cpptools-extension-pack`

Use the `CMake: Run Without Debugging` command to run the built executable(s). You can also use the ▶️ button in the status bar at the bottom of the screen.

### Manual Build
Run the `run.sh` script to build and execute the project.

This project is version controlled with [git](https://git-scm.com/), and git does not retain the file permissions for non-binary files. Therefore, you may need to change the script's permission if you encounter a permission error.

```bash
chmod +x run.sh # to add execution permission
./run.sh # to execute the script
```

## Configuration
Watcher uses a `JSON` based configuration file to configure the applications to watch. This uses a very minimal syntax for simplicity and edge of usage. 

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
`processes` is a `JSON array` that can have multiple objects with `name`, `command`, and `args` keys. Description of the keys are the followings:

* `name`: Name of the process/application that watcher is going to use to identify it
* `command`: The command to initiate the process/application. If the application name is not included in the system path, it must be specified relative to the `<PROJECT_ROOT>/build` directory.
* `args`: An array that takes `string` arguments as startup parameters to the process/application
* `foreground` is an optional key that will mark this process/application as the foreground process. That process will be on top of all other processes/applications from a GUI perspective.

## Sample Processes
Five sample processes have been created for the watcher to demonstrate what it can do. These processes are named after five Star Trek characters. 
* Kirk
* Spock
* Uhura
* Picard
* Data

All these processes log a message to `<PROJECT_ROOT>/logs/<process_name>.log` in a random interval between 1 and 10 seconds. 

Among these processes, `spock` takes a string as a startup parameter. The message from the `spock` process depends on the startup argument. If no argument is passed, it has a default text to log.

<p align="center">
    <img src="https://media.tenor.com/af2R3VhY7ZcAAAAC/llap-spock.gif" width="350"/>
</p>

> Configuration file changes are loaded on the fly. So, you can add processes from the configuration file, and watcher will automatically start the processes.

## Logs

### Watcher Log
Watcher logs all the events that happen in the system. This log is located at `<PROJECT_ROOT>/logs/watcher.log`.

These logs are categorized into two sources: `config` and `process`, and three levels: `INFO`, `WARN`, and `ERROR`.

#### Sample Log Entries
```
[2022-11-22 15:33:01.687] [config] [info] found 4 processes to watch
[2022-11-22 15:33:01.701] [process] [error] Process uhura is not found
[2022-11-22 15:33:01.701] [process] [info] Spawned process with pid 71495 for bin/uhura
[2022-11-22 15:33:01.771] [process] [error] Process spock is not found
[2022-11-22 15:33:01.771] [config] [info] found arguments Needs of the many outweighs the needs of the few  for process spock
[2022-11-22 15:33:01.772] [process] [info] Spawned process with pid 71504 for bin/spock
[2022-11-22 15:33:01.821] [process] [error] Process kirk is not found
[2022-11-22 15:33:01.822] [process] [info] Spawned process with pid 71514 for bin/kirk
```

### Watched Process Logs
All the processes that watcher is watching log their messages to `<PROJECT_ROOT>/logs/<process_name>.log`.

## Limitations
* Due to time constraints, this project does not have unit or integration tests.
* I do not have a windows machine to test this project. I couldn't verify if this project is compatible with windows. But as all the libraries used in this project are cross-platform, it should work on windows as well if the build process is configured correctly.
* The foreground process is not implemented yet as that requires GUI dependencies which is not in the scope of this project. So, the foreground key in the configuration file is not used.

## Future Scopes
* Add unit and integration tests
* Add a GUI Monitor to the watcher to show the logs and statuses of the monitor processes
* Implement the foreground process feature for popular Desktop or Window Managers (e.g. GNOME, KDE, i3, Windows etc.)
* Verify the compatibility with Windows
* Provide a pre-built binary for the project