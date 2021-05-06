from pathlib import Path
import os
import sys
import getopt
import fileinput
from shutil import copyfile

ESP8266_PACKAGE_PATH = Path("packages/esp8266/hardware/esp8266/")
ESP32_PACKAGE_PATH = Path("packages/esp32/hardware/esp32/")
ARDUINO_PACKAGES_PATH = None  # Determined by user opts or platform


def update_line_file(
        file_path, str_line_to_update, str_append, comment_only=False,
        comment_str=None):
    '''
    Updates a line on a file with a replacement (preserving the original line)
    or comments it out

    :param file_path: The path to the file
    :type file_path: str
    :param str_to_update: The string which will be replaced
    :type str_line_to_update str:
    :param str_append: The string which replace the line of str_to_update
    :type str_append str:
    :param comment_only: Determines whether to replace or only comment out a
    line
    :type comment_only boolean:
    :param comment_str: Str to use for a comment if commenting
    :type comment_str str:
    :raises: :class:`FileNotFound`: File couldn't be opened

    :returns: whether the string was replaced in the file or it was commented
    out
    :rtype: boolean
    '''
    file_modified = False
    for line in fileinput.input(file_path, inplace=True):
        if line.startswith(str_line_to_update):
            if comment_only:
                line = f"{comment_str} {line}"
                file_modified = True
            else:
                line = line.rstrip()
                line = f"{line}{str_append}\n"
                file_modified = True
        sys.stdout.write(line)
    return file_modified


def confirm_overwrite(file_path):
    '''
    Confirms whether to overwrite changes otherwise exits program

    :param file_path: The path to the file
    :type file_path: str
    '''
    prompt = f"There is already a backup file at" \
             f" {file_path}; proceeding will" \
             f" overwrite this file. Do you wish to proceed?" \
             f" Input Y or N:" \
             f" "
    while True:
        response = input(prompt)
        response = response.lower()
        if response == 'n':
            print("No changes made... exiting")
            sys.exit()
        elif response == 'y':
            print("Backup will be overwritten")
            break
        else:
            print("Ensure your response is a Y or N")


def usage():
    '''
    Prints script's opt usage
    '''
    print(
          "automate_board_config.py usage:\n"
          " -h or --help: Print usage text\n"
          " -p or --packages_path: Set custom path for Arduino packages path")
    sys.exit()


def parse_opts():
    '''
    Prints script's command line options
    '''
    options, _ = getopt.gnu_getopt(
                                          sys.argv[1:],
                                          'hp:',
                                          ['help', 'packages_path'])

    for opt, arg in options:
        if opt in ('-h', '--help'):
            usage()
        elif opt in ('-p', '--packages_path'):
            global ARDUINO_PACKAGES_PATH
            ARDUINO_PACKAGES_PATH = Path(arg)


def main():
    parse_opts()
    disclaimer_prompt = \
        "This script will attempt to automatically update" \
        " your ESP8266 and/or ESP32 board files to work with Azure IoT Hub" \
        " for the repo https://github.com/Azure/azure-iot-arduino" \
        "\nPlease refer to the license agreement there." \
        "\nThis script will update all installed versions of board" \
        " libraries for ESP8266 and/or ESP32." \
        "\nDo you wish to proceed? Please answer Y or N:" \
        " "

    while True:
        response = input(disclaimer_prompt)
        response = response.lower()
        if response == 'n':
            print("No changes made... exiting")
            sys.exit()
        elif response == 'y':
            print("Proceeding")
            break
        else:
            print("Ensure your response is a Y or N")

    board_prompt = \
        "Would you like to update your ESP8266 or ESP32 board files?\n" \
        "For ESP8266 please respond: 8266\n" \
        "For ESP32 please respond: 32\n" \
        "Which board files would you like to update:" \
        " "

    board_to_update = ""
    PACKAGE_PATH = ""
    while True:
        response = input(board_prompt)
        response = response.lower()
        if response == '8266':
            board_to_update = '8266'
            PACKAGE_PATH = ESP8266_PACKAGE_PATH
            break
        elif response == '32':
            board_to_update = '32'
            PACKAGE_PATH = ESP32_PACKAGE_PATH
            break
        else:
            print("Ensure your response is either 8226 or 32")

    global ARDUINO_PACKAGES_PATH
    if ARDUINO_PACKAGES_PATH is None:
        if sys.platform == "darwin":
            ARDUINO_PACKAGES_PATH = Path(Path.home() / "Library/Arduino15")
        elif sys.platform == "linux":
            ARDUINO_PACKAGES_PATH = Path(Path.home() / ".arduino15")
        elif sys.platform == "win32":
            ARDUINO_PACKAGES_PATH = Path(
                                    Path.home() / "AppData/Local/Arduino15")
        else:
            print(f"Error: no valid board path condition for platform:"
                  f" {sys.platform}")
            sys.exit()

    print(f"Arduino path for platform {sys.platform} is:"
          f" {ARDUINO_PACKAGES_PATH}")

    # Check for and change other versions if they exist
    BOARD_PATH = Path(ARDUINO_PACKAGES_PATH / PACKAGE_PATH)
    try:
        versions = []
        with os.scandir(BOARD_PATH) as entries:
            for version in entries:
                # avoid files and hidden files
                if version.is_dir and not version.name.startswith('.'):
                    versions.append(
                        Path(BOARD_PATH / version))
        if len(versions) == 0:
            raise FileNotFoundError
    except FileNotFoundError:
        print(
            f'Error: Board files for ESP{board_to_update} not found!\n'
            f'Directory searched was: {BOARD_PATH}\n'
            f'Please ensure that the board library exists at the location'
            f', or check command line parameters to specify a'
            f' custom Arduino packages path')
        sys.exit(1)

    for path in versions:
        if PACKAGE_PATH == ESP8266_PACKAGE_PATH:
            # 8266 has specific files which 32 aren't required to change
            arduino_header_backup = Path(path / "cores/esp8266/Arduino.h.orig")
            if arduino_header_backup.exists():
                confirm_overwrite(arduino_header_backup)
            arduino_header_file = Path(path / "cores/esp8266/Arduino.h")
            if arduino_header_file.exists():
                print(f"Updating: {arduino_header_file}")
                copyfile(
                    arduino_header_file,
                    Path(path / "cores/esp8266/Arduino.h.orig"))
                print(
                    f"Backup created:"
                    f" {Path(path / 'cores/esp8266/Arduino.h.orig')}")
                get_update = update_line_file(
                    arduino_header_file, "#define round(x)",
                    str_append=None, comment_only=True,
                    comment_str="//")
                print(f"Updated: {get_update} for {arduino_header_file}")
            else:
                print(f"Could not find {arduino_header_file}")
                sys.exit(1)

        platform_txt_backup = Path(path / "platform.txt.orig")
        if platform_txt_backup.exists():
            confirm_overwrite(platform_txt_backup)
        platform_txt_file = Path(path / "platform.txt")
        if platform_txt_file.exists():
            print(f"Updating: {platform_txt_file}")
            copyfile(platform_txt_file, Path(path / "platform.txt.orig"))
            print(f"Backup created: {Path(path / 'platform.txt.orig')}")
            append_str = ""
            if PACKAGE_PATH == ESP8266_PACKAGE_PATH:
                # Ensure to include spaces for flags
                append_str = " -DDONT_USE_UPLOADTOBLOB" \
                             " -DUSE_BALTIMORE_CERT"
            elif PACKAGE_PATH == ESP32_PACKAGE_PATH:
                append_str = " -DDONT_USE_UPLOADTOBLOB"
            get_update = update_line_file(
                    platform_txt_file, "build.extra_flags=",
                    str_append=append_str)
            print(f"Updated: {get_update} for {platform_txt_file}")
        else:
            print(f"Could not find {platform_txt_file}")
            sys.exit(1)


main()
