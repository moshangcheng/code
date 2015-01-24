from __future__ import with_statement
from fabric.api import *
from fabric.contrib.console import confirm

env.hosts = ['hk-ubuntu.cloudapp.net']
env.user = 'shu'
env.shell = '/usr/bin/zsh -i -c'


def hadoop_version():
	run("hadoop version")

def submit():

	jar_name = "hadoop-exercise-0.0.1-SNAPSHOT.jar"
	class_name = "me.shu.hadoop.exercise.WordCount"
	input_dir = "src/test/resources/input"
	working_dir = "/home/{0}/test/hadoop/wordcount".format(env.user)

	# prepare working directory
	run("rm -rf {0}/".format(working_dir))
	run("mkdir -p {0}".format(working_dir))

	# copy jar file and input files
	local("scp -r -q target/{0} {1}@{2}:{3}".format(jar_name, env.user, env.hosts[0], working_dir))
	local("scp -r -q {0} {1}@{2}:{3}".format(input_dir, env.user, env.hosts[0], working_dir))
	
	# execute job
	run("hadoop jar {0}/{1} {2} {0}/input {0}/output".format(working_dir, jar_name, class_name)) 
