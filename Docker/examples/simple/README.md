### simple Dockerfile 

`sudo docker build -t moshangcheng/hello-world .`
- print "hello world" in build
- on ArchLinux
    - [sudo edit /etc/default/grub](http://askubuntu.com/questions/417215/how-does-kernel-support-swap-limit)
    - change to `GRUB_CMDLINE_LINUX="cgroup_enable=memory swapaccount=1"`
    - then `sudo grub-mkconfig -o /boot/grub/grub.cfg` and reboot
- [ref](https://www.docker.io/learn/dockerfile/level1/)
