from __future__ import with_statement
from fabric.api import *
from fabric.contrib.console import confirm

env.hosts = ['hk-ubuntu.cloudapp.net']
env.user = 'shu'

def hello(name="world"):
	print("Hello %s!" % name)

def echo():
	local("echo hello")

def ls():
	run("ls")
