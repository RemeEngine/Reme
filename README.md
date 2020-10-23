# Reme Game Engine

A Simple C++ GameEngine

## TODO

In NO PARTICULAR ORDER, things i intent to do:

- [ ] ImGui playground / editor

- [ ] Line / Curve renderer with variable thickness, line caps and line joins

- [ ] Shader generator with custom backend for different API, for now implement OpenGL backend

- [ ] Dynamic texture atlas

- [ ] Font rendering

- [ ] Light source

- [ ] Renderer3D

- [ ] Mesh

- [ ] Material

## Configuration

### Define flags

- REME_DISABLE_ASSERT : disable `assert`

- REME_DISABLE_LOGGING : disable logging

## Road map

### 0.0.1

- [ ] EventDispatcher / EventManager

- [ ] GUI::Node event: MouseEnter, MouseLeave

- [ ] Build: 

    + DEBUG: Simple optimization, all debug symbols, log level `trace`, enable assert

    + SANDBOX: -O3 optimization, all debug symbols, log level `info`, enable assert

    + RELEASE: -O3 optimization, no debug symbols, log level `warn`, enable assert

- [ ] Examples: FlappyBird clone 
