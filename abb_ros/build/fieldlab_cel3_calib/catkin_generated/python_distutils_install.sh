#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/jmg/abb_ros/src/fieldlab_cel3_calib"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/jmg/abb_ros/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/jmg/abb_ros/install/lib/python2.7/dist-packages:/home/jmg/abb_ros/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/jmg/abb_ros/build" \
    "/usr/bin/python" \
    "/home/jmg/abb_ros/src/fieldlab_cel3_calib/setup.py" \
    build --build-base "/home/jmg/abb_ros/build/fieldlab_cel3_calib" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/jmg/abb_ros/install" --install-scripts="/home/jmg/abb_ros/install/bin"
