#!/bin/bash

# Script to run main program
rm pi_network_status  2> /dev/null
touch pi_network_status
chmod +x pi_network_status
echo "#!/bin/bash" >> pi_network_status
echo "echo \"Starting Pi Network Status\"" >> pi_network_status
echo "" >> pi_network_status
echo "pwd" >> pi_network_status
echo "cd $PWD" >> pi_network_status
echo "$PWD/bin/./pi_network_status" >> pi_network_status

# Startup Service
rm pi-network-status.service 2> /dev/null
touch pi-network-status.service
echo "Description = Pi Network Status keeps track of when the network is connected to the internet." >> pi-network-status.service
echo "" >> pi-network-status.service
echo "[Service]" >> pi-network-status.service
echo "Restart=always" >> pi-network-status.service
echo "RestartSec=60" >> pi-network-status.service
echo "ExecStart=$PWD/pi_network_status" >> pi-network-status.service
echo "" >> pi-network-status.service
echo "[Install]" >> pi-network-status.service
echo "WantedBy=multi-user.target" >> pi-network-status.service
