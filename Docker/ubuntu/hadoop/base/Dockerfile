# Hadoop-2.2.0 based on Ubuntu Precise 12.04 LTS image

FROM moshangcheng/ubuntu:base
MAINTAINER moshangcheng moshangcheng@gmail.com

# add group and user
RUN addgroup hadoop
RUN useradd -G hadoop -p hduser -s /bin/bash -m hduser

# download hadoop
# RUN su hduser -c "cd ~ && wget -q http://mirror.esocc.com/apache/hadoop/common/hadoop-2.2.0/hadoop-2.2.0.tar.gz"
ADD http://mirror.sdunix.com/apache/hadoop/common/hadoop-1.2.1/hadoop_1.2.1-1_x86_64.deb /home/hduser/
