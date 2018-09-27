#!/bin/bash

# doing funny things
name=graph
java -jar ~/Java/plantuml.jar -verbose $name.txt
xdg-open $name.png