# Pi Network Status

This program is designed to periodically check the network status of a Raspberry Pi. Once every minute the Pi will ping telus.ca to check for a internet connection. A visual representation of the network's Up/Down percentages can be seen by going to "http://<Pi's IP Address>:8001" using any device on the same network. 

## Install

To install the program perform the following commands:
```
make install
make all
sudo reboot
```

The program will be running upon reboot.

## Uninstall
```
make uninstall
```

## Reset Saved Data
```
make clean all
```

## Debug Output
```
sudo systemctl status pi-network-status.service
sudo journalctl -u pi-network-status.service
```

## Stop Program
```
sudo systemctl stop pi-network-status.service
```
