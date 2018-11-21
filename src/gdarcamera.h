#ifndef GDARCAMERA_H
#define GDARCAMERA_H

#include <cstdlib>
#include <opencv2/opencv.hpp>
#include "aruco.h"
#include <Godot.hpp>
#include <Node.hpp>
#include <PoolArrays.hpp>

namespace godot {

class gdarcamera : public godot::GodotScript<Node> {
    GODOT_CLASS(gdarcamera)

private:
    cv::VideoCapture capture;
    cv::Mat frame;
    aruco::MarkerDetector mDetector;
    aruco::CameraParameters cameraParameters;
    std::vector<aruco::Marker> markers;
    
    double position[3];
    double orientation[4];
    bool markerDetected = false;
    
    float markerSize = 0.07f;
    int markerId = 14;
public:
    static void _register_methods();

    gdarcamera();
    ~gdarcamera();

    bool is_open();
    void open();
    void release();
    PoolByteArray get_picture_buffer(bool detectMarker);
    Vector3 getPosition();
    Quat getOrientation();
    bool isDetected();
    void setMarkerSize(float size);
    void setMarkerId(int id);
    
    std::vector<uchar> buffer;
};

}

#endif
