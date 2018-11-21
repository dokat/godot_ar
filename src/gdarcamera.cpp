#include "gdarcamera.h"

using namespace godot;

void gdarcamera::_register_methods() {
    register_method((char *) "open", &gdarcamera::open);
    register_method((char *) "release", &gdarcamera::release);
    register_method((char *) "is_open", &gdarcamera::is_open);
    register_method((char *) "get_picture_buffer", &gdarcamera::get_picture_buffer);
    register_method((char *) "getPosition", &gdarcamera::getPosition);
    register_method((char *) "getOrientation", &gdarcamera::getOrientation);
    register_method((char *) "isDetected", &gdarcamera::isDetected);
    register_method((char *) "setMarkerSize", &gdarcamera::setMarkerSize);
    register_method((char *) "setMarkerId", &gdarcamera::setMarkerId);
}

gdarcamera::gdarcamera() 
{
    cameraParameters.readFromXMLFile("camera_result.yml");

    mDetector.loadParamsFromFile("arucoConfig.yml");
}

gdarcamera::~gdarcamera() 
{
    // add your cleanup here
    release();
}


void gdarcamera::open()
{
    capture.open(-1);

    // check video is open
    //if (!capture.isOpened())
    //    throw std::runtime_error("Could not open video");

    capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
    capture.set(CV_CAP_PROP_FPS, 25);
}


 void gdarcamera::release()
{
    capture.release();
}

bool gdarcamera::is_open() {
    return capture.isOpened();
}

PoolByteArray gdarcamera::get_picture_buffer(bool detectMarker) {
    PoolByteArray pbArray;

    if (is_open()) {
        capture.retrieve(frame);

        if(detectMarker) {
            markers = mDetector.detect(frame, cameraParameters, markerSize, true);
            markerDetected = false;
            for (auto& marker : markers) {
                if (marker.id == markerId) {
                    markerDetected = true;
                    marker.OgreGetPoseParameters(position, orientation);
                }
            }
        }
        cv::imencode(".jpg", frame, buffer);
        
        for (auto const& value : buffer) {
            pbArray.append(value);
        }

        capture.grab();
    }
    return pbArray;
}

bool gdarcamera::isDetected()
{
    return markerDetected;
}

Vector3 gdarcamera::getPosition() {
    Vector3 vec;
    vec.x = -position[0];
    vec.y = position[1];
    vec.z = -position[2];
    return vec;
}

Quat gdarcamera::getOrientation() {
    Quat q;
    q.w = orientation[0];
    q.x = orientation[1];
    q.y = orientation[2];
    q.z = orientation[3];
    return q;
}

void gdarcamera::setMarkerSize(float size) {
    if (is_open() && size > 0) {
        markerSize = size;
    }
}

void gdarcamera::setMarkerId(int id) {
    if (is_open() && id > 0) {
        markerId = id;
    }
}