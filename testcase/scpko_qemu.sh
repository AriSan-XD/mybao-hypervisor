ssh-keygen -f "/home/arisan/.ssh/known_hosts" -R "127.0.0.1"
scp -P 5555 *.ko root@127.0.0.1:/root
