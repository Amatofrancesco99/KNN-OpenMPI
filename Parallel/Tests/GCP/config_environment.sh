# the following istructions are the ones necessary to install and configure openMPI
# on my notebook
# ssh -l username -i $HOME/.ssh/id_rsa VM_IP_address

#on the vm
sudo apt update
sudo apt install gcc gpp make build-essential

wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz
gunzip -c openmpi-4.1.1.tar.gz | tar xf -
cd openmpi-4.1.1
sudo ./configure --prefix=/usr/local
sudo make all install

echo "export PATH=\$PATH:/usr/local/openmpi/bin" >>$HOME/.bashrc
echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/usr/local/openmpi/lib" \  >>$HOME/.bashrc
cd ..
sudo rm -r openmpi-4.1.1
rm openmpi-4.1.1.tar.gz

sudo ldconfig
# send ssh keys to the rempote server
#on my notebook scp $HOME/.ssh/id_rsa*  username@VM_IP_address:$HOME/
# mv id_rsa* .ssh/
