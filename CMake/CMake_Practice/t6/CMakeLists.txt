# We can implement custom find_package() in directory specifid in CMAKE_MODULE_PATH
# In the implement, first we seach library and header files in our own method
# Then clean CMAKE_MODULE_PATH and call default find_package()
# After that we restore CMAKE_MODULE_PATH
# In this way, we can add a proxy for default find_package()
# Check the zorba source code for detail

PROJECT(NEWHELLO)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

ADD_SUBDIRECTORY(src)


