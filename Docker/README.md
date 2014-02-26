### Dockerfile

------------------

usage:

- to remove all stopped containers

        sudo docker rm `sudo docker ps -a -q`
        
- to remove all "none" images

        sudo docker images | grep "<none>" | awk '{print $3}' | xargs sudo docker rmi

------------------

ref:

- [Docker Desktop](https://github.com/rogaha/docker-desktop)
- [Docker Private Repository](http://www.oschina.net/question/54100_137630)
- [Docker Best Practices](http://crosbymichael.com/dockerfile-best-practices.html)
- [Dockerfile for Spark and Shark](https://github.com/amplab/docker-scripts)
