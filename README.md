# Arduino Tests and Samples

# Help

configuration file in `/home/nick/.arduino15/arduino-cli.yaml`

double press reset button to put arduino into "bootloader mode." This is
helpful if you botch a sketch upload partway through and the board doesn't show
up for new sketch upload.

## Commands:

* new sketch: `arduino-cli sketch new $SKETCH_NAME`
* compile: `arduino-cli compile --fqbn arduino:avr:uno $PATH_TO_SKETCH`
* upload: `arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno $PATH_TO_SKETCH`
* serial monitor: `arduino-cli monitor -p /dev/ttyACM0`
* unsafe library install `arduino-cli lib install --zip-path $PATH_TO_ZIP_FILE` (also see github option)
* platforms:
  * `arduino-cli core list`
  * `arduino-cli core search`
  * `arduino-cli core install $PLATFORM` (e.g. `arudino:renesas_uno`)
