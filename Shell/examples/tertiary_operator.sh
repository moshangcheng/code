#!/bin/bash

# http://stackoverflow.com/questions/3953645/ternary-operator-in-bash
echo --- tow ways to simulate tertiary operator
echo $([ -e tertiary_operator.sh ] && echo "exist" || echo "not exist")
echo `[ -e tertiary_operator.sh ] && echo "exist" || echo "not exist"`
