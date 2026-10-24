# Event Camera Calibration Helper

This is a custom made calibration helper tool for PROPHESEE's event cameras, based on [OpenEB](https://github.com/prophesee-ai/openeb).

**Disclaimer:** This sofware is being built for internal use and is under construction.

## Requirements

- Docker

## Usage

### Build container

```bash
docker build -t event-calib-dev .
```

```bash
docker run --rm -it --privileged \
  -v $(pwd):/app -w /app \
  -e WAYLAND_DISPLAY=$WAYLAND_DISPLAY \
  -e XDG_RUNTIME_DIR=/tmp/xdg-runtime \
  -v $XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/xdg-runtime/$WAYLAND_DISPLAY \
  -v /dev/bus/usb:/dev/bus/usb \
  event-calib-dev bash
```

### Build app

```bash
# Release (default for normal dev)
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Debug (for gdb / stepping through code)
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug

cmake --build build -j$(nproc)
```

### Clean rebuild

```bash
rm -rf build
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
```

### Running

```bash
./build/calib_cam
```

### Debug

```bash
gdb --args ./build/calib_cam
```

### Mounting this repository on a remote machine

```bash
sudo mount -t nfs <server-machine-ip>:/home/you/event-camera-calibrator /mnt/calib-project # This must be run on the remote machine
```
