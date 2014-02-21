# add user and cd to its home directory
FROM moshangcheng/ubuntu:base
MAINTAINER moshangcheng moshangcheng@gmail.com

# add group and user
RUN addgroup hadoop
RUN useradd -G hadoop -p hduser -s /bin/bash -m hduser

# cd to home directoryof hduser
RUN su hduser -c "cd ~ && whoami && pwd"
