# Base Ubuntu Precise 12.04 LTS image

FROM ubuntu:precise
MAINTAINER moshangcheng moshangcheng@gmail.com

# Set correct source list
RUN echo "deb http://archive.ubuntu.com/ubuntu precise main universe" > /etc/apt/sources.list

# install tools
RUN apt-get update && apt-get upgrade -y && apt-get install -y default-jdk vim git openssh-server
