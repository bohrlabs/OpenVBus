


# OpenVBus ImGui UI Starter


## Build
```
bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j
./openvbus_imgui
```

## Optional PCAP
```bash
cmake -DOPENVBUS_WITH_PCAP=ON ..
```


├─ CMakeLists.txt
├─ external/
│ └─ (empty placeholders; see notes)
├─ src/
│ ├─ main.cpp
│ ├─ glad.c
│ ├─ imgui_layer.h
│ ├─ imgui_layer.cpp
│ ├─ app_state.h
│ ├─ model.h
│ ├─ model.cpp
│ ├─ panels/
│ │ ├─ panel_bus_list.h
│ │ ├─ panel_bus_list.cpp
│ │ ├─ panel_inspector.h
│ │ ├─ panel_inspector.cpp
│ │ ├─ panel_filters.h
│ │ ├─ panel_filters.cpp
│ │ ├─ panel_packets.h
│ │ ├─ panel_packets.cpp
│ │ ├─ panel_vlan.h
│ │ ├─ panel_vlan.cpp
│ │ ├─ panel_log.h
│ │ ├─ panel_log.cpp
│ ├─ backends/
│ │ ├─ iface_base.h
│ │ ├─ iface_mock.h
│ │ ├─ iface_mock.cpp
│ │ ├─ iface_pcap.h
│ │ ├─ iface_pcap.cpp
│ └─ util/
│ ├─ ringbuffer.h
│ └─ id_gen.h
└─ README.md

